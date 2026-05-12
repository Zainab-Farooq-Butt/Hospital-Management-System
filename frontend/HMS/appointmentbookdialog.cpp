#include "AppointmentBookDialog.h"
#include "../../Doctor.h"
#include "../../Appointment.h"
#include "../../Person.h"

#include <QFormLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QMessageBox>
#include <QDate>
#include <fstream>
#include <string>
#include <map>

// Helper: parse hour from strings like "9AM", "9am", "09:00", "9:00 AM"
static int parseHour(const QString &s) {
    QString t = s.simplified().toUpper();
    bool isPM = t.contains("PM");
    t.remove("AM").remove("PM").remove(":").remove(" ");
    int h = t.left(t.length() >= 2 ? 2 : t.length()).toInt();
    if (h < 10 && t.length() == 1) h = t.toInt();
    if (isPM && h != 12) h += 12;
    if (!isPM && h == 12) h = 0;
    return h;
}

// Parse schedule string like "Mon-Fri 9AM-5PM" or "Monday 9am-11am"
// Returns {days string, start hour, end hour}
struct ParsedSchedule {
    QStringList days;    // e.g. ["Monday","Tuesday",...]
    int startHour = -1;
    int endHour   = -1;
    bool valid = false;
};

static ParsedSchedule parseSchedule(const QString &sched) {
    ParsedSchedule ps;
    if (sched.trimmed().isEmpty()) return ps;

    // Full day names for expansion
    static QStringList allDays = {"Monday","Tuesday","Wednesday","Thursday","Friday","Saturday","Sunday"};
    static QStringList shortDays = {"Mon","Tue","Wed","Thu","Fri","Sat","Sun"};

    // Split at first space-like boundary between days and times
    // Format expected: "Mon-Fri 9AM-5PM" or "Monday 9am-11am"
    QStringList parts = sched.split(' ', Qt::SkipEmptyParts);
    if (parts.size() < 2) { ps.days = allDays; return ps; } // fallback: all days

    QString dayPart  = parts[0];  // e.g. "Mon-Fri"
    QString timePart = parts.mid(1).join(" "); // e.g. "9AM-5PM"

    // Parse day range
    if (dayPart.contains("-")) {
        QStringList dayRange = dayPart.split("-");
        if (dayRange.size() == 2) {
            QString from = dayRange[0].trimmed();
            QString to   = dayRange[1].trimmed();
            // Find indices
            int iFrom = -1, iTo = -1;
            for (int i = 0; i < shortDays.size(); i++) {
                if (from.startsWith(shortDays[i], Qt::CaseInsensitive) ||
                    from.startsWith(allDays[i], Qt::CaseInsensitive)) iFrom = i;
                if (to.startsWith(shortDays[i], Qt::CaseInsensitive) ||
                    to.startsWith(allDays[i], Qt::CaseInsensitive)) iTo = i;
            }
            if (iFrom >= 0 && iTo >= 0) {
                for (int i = iFrom; i <= iTo; i++) ps.days << allDays[i];
            }
        }
    } else {
        // Single day or full name
        for (int i = 0; i < allDays.size(); i++) {
            if (dayPart.startsWith(shortDays[i], Qt::CaseInsensitive) ||
                dayPart.startsWith(allDays[i], Qt::CaseInsensitive)) {
                ps.days << allDays[i];
                break;
            }
        }
    }
    if (ps.days.isEmpty()) ps.days = allDays; // fallback

    // Parse time range like "9AM-5PM"
    QStringList timeRange = timePart.split("-");
    if (timeRange.size() >= 2) {
        ps.startHour = parseHour(timeRange[0]);
        ps.endHour   = parseHour(timeRange[1]);
        ps.valid = true;
    }
    return ps;
}

AppointmentBookDialog::AppointmentBookDialog(const QString &pid, QWidget *parent)
    : QDialog(parent), patientId(pid) {
    setWindowTitle("Book New Appointment");
    setMinimumWidth(460);

    lblPatient = new QLabel("<b>Patient ID:</b> " + patientId, this);

    cmbDoctor = new QComboBox(this);
    lblAvailability = new QLabel("Select a doctor to see their schedule.", this);
    lblAvailability->setStyleSheet("color: #64748b; font-style: italic; font-size: 12px; padding: 4px 0;");
    lblAvailability->setWordWrap(true);

    dateEdit = new QDateEdit(QDate::currentDate(), this);
    dateEdit->setCalendarPopup(true);
    dateEdit->setMinimumDate(QDate::currentDate());
    dateEdit->setMaximumDate(QDate::currentDate().addYears(1));
    dateEdit->setDisplayFormat("dd/MM/yyyy");

    cmbSlot = new QComboBox(this);

    txtReason = new QLineEdit(this);
    txtReason->setPlaceholderText("e.g., Routine Checkup, Fever, etc.");

    auto *form = new QFormLayout();
    form->setSpacing(12);
    form->addRow("", lblPatient);
    form->addRow("Select Doctor:", cmbDoctor);
    form->addRow("", lblAvailability);
    form->addRow("Appointment Date:", dateEdit);
    form->addRow("Time Slot:", cmbSlot);
    form->addRow("Reason for Visit:", txtReason);

    auto *btnBook = new QPushButton("Book Appointment", this);
    auto *btnCancel = new QPushButton("Cancel", this);

    auto *btnRow = new QHBoxLayout();
    btnRow->addStretch();
    btnRow->addWidget(btnCancel);
    btnRow->addWidget(btnBook);

    auto *root = new QVBoxLayout(this);
    root->setContentsMargins(20, 20, 20, 20);
    root->setSpacing(10);
    root->addLayout(form);
    root->addSpacing(15);
    root->addLayout(btnRow);

    loadDoctors();

    connect(cmbDoctor, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &AppointmentBookDialog::onDoctorChanged);
    connect(dateEdit, &QDateEdit::dateChanged,
            this, [this](const QDate&){ onDoctorChanged(cmbDoctor->currentIndex()); });
    connect(btnBook, &QPushButton::clicked, this, &AppointmentBookDialog::onBook);
    connect(btnCancel, &QPushButton::clicked, this, &QDialog::reject);

    if (!doctorList.isEmpty()) onDoctorChanged(0);
}

void AppointmentBookDialog::loadDoctors() {
    doctorList.clear();
    std::ifstream df("Doctor.txt");
    if (!df) return;

    std::string line;
    while (std::getline(df, line)) {
        if (line != "----------") continue;
        Doctor d; d.Load_From_File(df);
        // Only show available doctors
        if (d.getAvailabilityStatus() == "Unavailable" || d.getAvailabilityStatus() == "On Leave")
            continue;

        QString name = "Dr. " + QString::fromStdString(d.getDoctorId());
        std::ifstream pf("Person.txt");
        std::string pline;
        while (std::getline(pf, pline)) {
            if (pline != "----------") continue;
            Person p; p.Load_From_File(pf);
            if (p.Get_CNIC() == d.get_CNIC()) {
                name = "Dr. " + QString::fromStdString(p.Get_Name());
                break;
            }
        }
        pf.close();

        doctorList.append(DoctorInfo(
            QString::fromStdString(d.getDoctorId()),
            name,
            QString::fromStdString(d.getAvailability()),
            QString::fromStdString(d.getAvailabilityStatus())
        ));
        cmbDoctor->addItem(name + "  (" + QString::fromStdString(d.getDoctorId()) + ")");
    }
    df.close();
}

void AppointmentBookDialog::onDoctorChanged(int index) {
    if (index < 0 || index >= doctorList.size()) return;

    QString sched = doctorList[index].schedule;
    lblAvailability->setText("<b>Schedule:</b> " + sched);

    // Rebuild time slots based on parsed schedule & selected date
    cmbSlot->clear();
    ParsedSchedule ps = parseSchedule(sched);

    // Check if selected day is valid for this doctor
    QString selectedDay = dateEdit->date().toString("dddd"); // e.g. "Monday"
    bool dayOk = false;
    for (const QString &d : ps.days) {
        if (d.compare(selectedDay, Qt::CaseInsensitive) == 0) { dayOk = true; break; }
    }

    if (!dayOk) {
        lblAvailability->setText("<b>Schedule:</b> " + sched +
                                 "  ⚠️ Doctor not available on " + selectedDay);
        return;
    }

    // Generate 1-hour slots within start-end range
    if (ps.valid && ps.startHour >= 0 && ps.endHour > ps.startHour) {
        for (int h = ps.startHour; h < ps.endHour; h++) {
            QString period = (h < 12) ? "AM" : "PM";
            int displayH  = (h == 0) ? 12 : (h > 12 ? h - 12 : h);
            cmbSlot->addItem(QString("%1:00 %2").arg(displayH, 2, 10, QChar('0')).arg(period));
        }
    } else {
        // Fallback: show all standard slots if schedule parse failed
        cmbSlot->addItems({"09:00 AM","10:00 AM","11:00 AM","12:00 PM",
                           "02:00 PM","03:00 PM","04:00 PM","05:00 PM"});
    }
}

void AppointmentBookDialog::onBook() {
    int idx = cmbDoctor->currentIndex();
    if (idx < 0) { QMessageBox::warning(this, "Required", "Please select a doctor."); return; }
    if (cmbSlot->count() == 0) {
        QMessageBox::warning(this, "No Slots", "No time slots available for this doctor on the selected date.");
        return;
    }

    QString docId  = doctorList[idx].id;
    QString sched  = doctorList[idx].schedule;
    QDate   selDate = dateEdit->date();
    QString dateStr = selDate.toString("dd/MM/yyyy");
    QString dayName = selDate.toString("dddd");
    QString time    = cmbSlot->currentText();
    QString reason  = txtReason->text().trimmed();

    // 1. Validate doctor's day availability
    ParsedSchedule ps = parseSchedule(sched);
    bool dayOk = false;
    for (const QString &d : ps.days)
        if (d.compare(dayName, Qt::CaseInsensitive) == 0) { dayOk = true; break; }

    if (!dayOk) {
        QMessageBox::warning(this, "Doctor Unavailable",
                             "Dr. " + doctorList[idx].name + " is not available on " + dayName + ".\n"
                             "Their schedule is: " + sched);
        return;
    }

    // 2. Prevent double booking
    std::ifstream checkf("Appointment.txt");
    std::string cln;
    bool alreadyBooked = false;
    while (std::getline(checkf, cln)) {
        if (cln != "----------") continue;
        std::string aid, pid, did, adate, atime, areason, astat;
        std::getline(checkf, aid); std::getline(checkf, pid);
        std::getline(checkf, did); std::getline(checkf, adate);
        std::getline(checkf, atime); std::getline(checkf, areason);
        std::getline(checkf, astat);
        if (did == docId.toStdString() && adate == dateStr.toStdString() &&
            atime == time.toStdString() && astat == "Scheduled") {
            alreadyBooked = true;
            break;
        }
    }
    checkf.close();

    if (alreadyBooked) {
        QMessageBox::warning(this, "Slot Already Taken",
                             "This time slot (" + time + " on " + dateStr + ") is already booked for this doctor.\n"
                             "Please choose a different time or date.");
        return;
    }

    // 3. Save appointment
    int apptCount = 0;
    { std::ifstream cf("Appointment.txt"); std::string l;
      while (std::getline(cf, l)) if (l == "----------") apptCount++; }
    int next = apptCount + 1;
    std::string num   = std::to_string(next);
    std::string apptId = "A-" + std::string(4 - num.length(), '0') + num;

    std::ofstream out("Appointment.txt", std::ios::app);
    out << "----------\n" << apptId << "\n" << patientId.toStdString() << "\n"
        << docId.toStdString() << "\n" << dateStr.toStdString() << "\n"
        << time.toStdString() << "\n"
        << (reason.isEmpty() ? "General Checkup" : reason.toStdString()) << "\n"
        << "Scheduled\n";
    out.close();

    QMessageBox::information(this, "Booked Successfully!",
        QString("Your appointment has been confirmed.\n\n"
                "Appointment ID: %1\n"
                "Doctor: %2\n"
                "Date: %3 (%4)\n"
                "Time: %5")
            .arg(QString::fromStdString(apptId))
            .arg(doctorList[idx].name)
            .arg(dateStr).arg(dayName).arg(time));
    accept();
}