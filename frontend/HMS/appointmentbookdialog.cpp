#include "AppointmentBookDialog.h"
#include "../../Doctor.h"
#include "../../Appointment.h"

#include <QFormLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QMessageBox>
#include <fstream>
#include <string>

AppointmentBookDialog::AppointmentBookDialog(const QString &pid, QWidget *parent)
    : QDialog(parent), patientId(pid) {
    setWindowTitle("Book Appointment");
    resize(420, 280);

    lblPatient  = new QLabel("Patient ID: " + patientId, this);
    txtDoctorId = new QLineEdit(this); txtDoctorId->setPlaceholderText("D-XXXX");
    txtDate     = new QLineEdit(this); txtDate->setPlaceholderText("DD/MM/YYYY");
    txtTime     = new QLineEdit(this); txtTime->setPlaceholderText("HH:MM");
    txtReason   = new QLineEdit(this);

    auto *form = new QFormLayout();
    form->addRow("",             lblPatient);
    form->addRow("Doctor ID:",   txtDoctorId);
    form->addRow("Date:",        txtDate);
    form->addRow("Time:",        txtTime);
    form->addRow("Reason:",      txtReason);

    auto *btnBook   = new QPushButton("Book", this);
    auto *btnCancel = new QPushButton("Cancel", this);
    auto *btnRow = new QHBoxLayout();
    btnRow->addStretch(); btnRow->addWidget(btnCancel); btnRow->addWidget(btnBook);

    auto *root = new QVBoxLayout(this);
    root->addLayout(form);
    root->addLayout(btnRow);

    connect(btnBook,   &QPushButton::clicked, this, &AppointmentBookDialog::onBook);
    connect(btnCancel, &QPushButton::clicked, this, &QDialog::reject);
}

void AppointmentBookDialog::onBook() {
    QString docId  = txtDoctorId->text().trimmed();
    QString date   = txtDate->text().trimmed();
    QString time   = txtTime->text().trimmed();
    QString reason = txtReason->text().trimmed();

    Doctor d;
    if (!d.isValidDoctorId(docId.toStdString())) {
        QMessageBox::warning(this, "Invalid", "Invalid Doctor ID format (D-XXXX)."); return;
    }
    if (!d.doctorIdAlreadyExists(docId.toStdString(), "Doctor.txt")) {
        QMessageBox::warning(this, "Invalid", "Doctor not found."); return;
    }
    if (date.isEmpty() || time.isEmpty()) {
        QMessageBox::warning(this, "Missing", "Date and time required."); return;
    }

    int apptCount = 0;
    {
        std::ifstream cf("Appointment.txt");
        std::string l;
        while (std::getline(cf, l)) if (l == "----------") apptCount++;
    }
    int next = apptCount + 1;
    std::string num = std::to_string(next);
    std::string apptId = "A-" + std::string(4 - num.length(), '0') + num;

    std::ofstream out("Appointment.txt", std::ios::app);
    out << "----------\n"
        << apptId << "\n"
        << patientId.toStdString() << "\n"
        << docId.toStdString() << "\n"
        << date.toStdString() << "\n"
        << time.toStdString() << "\n"
        << (reason.isEmpty() ? "General Checkup" : reason.toStdString()) << "\n"
        << "Scheduled\n";
    out.close();

    QMessageBox::information(this, "Booked",
                             "Appointment booked.\nID: " + QString::fromStdString(apptId));
    accept();
}