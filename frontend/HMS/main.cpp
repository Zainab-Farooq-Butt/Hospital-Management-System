#include <QApplication>
#include "loginwindow.h"
#include "../../Patient.h"
#include "../../Doctor.h"
#include "../../Staff.h"
#include "../../Appointment.h"
#include "../../MedicalRecords.h"
#include "../../Billing.h"
#include "../../Ambulance.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    Patient::loadCounterFromFile("Patient.txt");
    Doctor::loadCounterFromFile("Doctor.txt");
    Staff::loadCounterFromFile("Staff.txt");
    Appointment::loadCounterFromFile("Appointment.txt");
    MedicalRecords::loadCounterFromFile("MedicalRecords.txt");
    Billing::loadCounterFromFile("Billing.txt");
    Ambulance::loadCounterFromFile("Ambulance.txt");

    LoginWindow w;
    w.show();
    return app.exec();
}