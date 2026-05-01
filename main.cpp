// #include "Person.h"
// #include "Login.h"
// #include "RBAC.h"

// void registerNewPerson() {
//     Person p;
//     p=p.Get_Valid_Person_Input("Person.txt");
//     ofstream outfile("Person.txt", ios::app);
//     p.Save_To_File(outfile);
//     outfile.close();
   

//     string username, password, role;
//     cout << "Assign username: ";
//     cin >> username;
//     cout << "Assign password: "; 
//     cin >> password;
//     cout<<"Assign Role (CAPS): ";
//     cin>>role;
//     while (role != "ADMIN" && role != "DOCTOR" && role != "STAFF" && role != "PATIENT") {
//         cout << "Invalid role. Enter again: ";
//         cin >> role;
//     }
//     Login::Save_Login_to_File(username, password, role);
// }

#include "SystemController.h"
#include "Patient.h"
#include "Doctor.h"
#include "Staff.h"
#include "Appointment.h"
#include "MedicalRecords.h"
#include "Billing.h"

int main() {
    Patient::loadCounterFromFile("Patient.txt");
    Doctor::loadCounterFromFile("Doctor.txt");
    Staff::loadCounterFromFile("Staff.txt");
    Appointment::loadCounterFromFile("Appointment.txt");
    MedicalRecords::loadCounterFromFile("MedicalRecords.txt");
    Billing::loadCounterFromFile("Billing.txt");
    SystemController sc;
    sc.run();
    return 0;
}
