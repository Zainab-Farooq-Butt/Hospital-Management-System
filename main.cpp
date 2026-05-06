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
#include "Room.h"
#include "Ambulance.h"

int main() {
    Patient::loadCounterFromFile("Patient.txt");
    Doctor::loadCounterFromFile("Doctor.txt");
    Staff::loadCounterFromFile("Staff.txt");
    Appointment::loadCounterFromFile("Appointment.txt");
    MedicalRecords::loadCounterFromFile("MedicalRecords.txt");
    Billing::loadCounterFromFile("Billing.txt");
    Ambulance::loadCounterFromFile("Ambulance.txt");

    // add just this block temporarily at the very top
    //{
    //    cout << "=== BEFORE ===" << endl;
    //    ifstream before("Room.txt");
    //    string line;
    //    int count = 0;
    //    while(getline(before, line)) {
    //       cout << line << endl;
    //        if(++count > 20) break;
    //    }
    //    before.close();
    //
    //    Room r;
    //    r.updatePatientID("R-0029", "P-0004");

    //    cout << "=== AFTER ===" << endl;
    //    ifstream after("Room.txt");
    //    count = 0;
    //    while(getline(after, line)) {
    //        cout << line << endl;
    //        if(++count > 20) break;
    //    }
    //    after.close();
    //    return 0; // stop here so nothing else runs
    //}
    
    SystemController sc;
    sc.run();
    return 0;
}
