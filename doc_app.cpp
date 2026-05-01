#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QObject>
#include <QString>

#include <fstream>
#include <sstream>
#include <string>

#include "Doctor.h"
#include "Appointment.h"

// ==================== DOCTOR BRIDGE ====================
class DoctorBridge : public QObject {
    Q_OBJECT
public:
    explicit DoctorBridge(QObject* parent = nullptr) : QObject(parent) {}

    Q_INVOKABLE QString addDoctor(QString doctorId, QString specialization, QString availability) {
        std::string id    = doctorId.toStdString();
        std::string spec  = specialization.toStdString();
        std::string avail = availability.toStdString();

        if (!Doctor::isValidDoctorId(id))
            return "Invalid Doctor ID. Use format D-XXXX (e.g. D-0001).";
        if (Doctor::doctorIdAlreadyExists(id, "doctors.txt"))
            return "Doctor ID already exists.";
        if (!Doctor::isValidSpecialization(spec))
            return "Invalid specialization.";
        if (!Doctor::isValidAvailability(avail))
            return "Invalid availability. Use e.g. Mon-Fri 9AM-5PM.";

        Doctor doc(id, spec, "MBBS", 0, 1000.0, avail, "Available");
        std::ofstream outfile("doctors.txt", std::ios::app);
        if (!outfile.is_open()) return "Could not save to file.";
        doc.Save_To_File(outfile);
        outfile.close();
        return "Doctor added successfully!";
    }
};

// ==================== APPOINTMENT BRIDGE ====================
class AppointmentBridge : public QObject {
    Q_OBJECT
public:
    explicit AppointmentBridge(QObject* parent = nullptr) : QObject(parent) {}

    Q_INVOKABLE QString bookAppointment(QString apptId, QString patientId, QString doctorId, QString date) {
        std::string aId = apptId.toStdString();
        std::string pId = patientId.toStdString();
        std::string dId = doctorId.toStdString();
        std::string d   = date.toStdString();
        Appointment appt;

        if (!appt.isValidAppointmentId(aId))
            return "Invalid Appointment ID. Use format A-XXXX (e.g. A-0001).";
        if (appt.appointmentIdAlreadyExists(aId, "appointments.txt"))
            return "Appointment ID already exists.";
        if (!appt.isValidDate(d))
            return "Invalid date. Use DD/MM/YYYY.";
        if (pId.empty() || dId.empty())
            return "Patient ID and Doctor ID cannot be empty.";

        Appointment newAppt(aId, pId, dId, d, "09:00", "Consultation", "Scheduled");
        newAppt.saveToFile("appointments.txt");
        return "Appointment booked successfully!";
    }

    Q_INVOKABLE QString cancelAppointment(QString apptId) {
        std::string aId = apptId.toStdString();
        std::ifstream infile("appointments.txt");
        if (!infile.is_open()) return "Could not open file.";

        std::ostringstream buffer;
        std::string id, pId, dId, d, time, rsn, stat;
        bool found = false;

        while (getline(infile, id)) {
            getline(infile, pId);
            getline(infile, dId);
            getline(infile, d);
            getline(infile, time);
            getline(infile, rsn);
            getline(infile, stat);

            if (id == aId) { found = true; stat = "Cancelled"; }

            buffer << id << "\n" << pId << "\n" << dId << "\n"
                   << d << "\n" << time << "\n" << rsn << "\n" << stat << "\n";
        }

        infile.close();
        if (!found) return "Appointment ID not found.";

        std::ofstream outfile("appointments.txt", std::ios::trunc);
        if (!outfile.is_open()) return "Could not write to file.";
        outfile << buffer.str();
        outfile.close();
        return "Appointment cancelled!";
    }
};

// ==================== MAIN ====================
int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    DoctorBridge doctorBridge;
    AppointmentBridge appointmentBridge;

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("doctorBridge", &doctorBridge);
    engine.rootContext()->setContextProperty("appointmentBridge", &appointmentBridge);
    engine.load(QUrl(QStringLiteral("qrc:/Doc_App.qml")));

    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
