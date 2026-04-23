#include"Person.h"
#include"Patient.h"
#include"Login.h"
#include"SystemController.h"


void SystemController::showLogin() {
    string username, password,currentRole, currentUser;

    cout << "Enter username: ";
    cin >> username;

    cout << "Enter password: ";
    cin >> password;

    Login login;
    currentRole = login.authenticate(username, password);
    currentUser = username;

    cout << "Role: " << currentRole << endl;

    if (currentRole == "ADMIN") {
        adminMenu();
    }
    else if (currentRole == "DOCTOR") {
        doctorMenu();
    }
    else if (currentRole == "PATIENT") {
        patientMenu();
    }
    else if (currentRole == "STAFF") {
        staffMenu();
    }
    else {
        cout << "Invalid credentials!\n";
    }
}

void SystemController::run() {
    while (true) {
        showLogin();

        char choice;
        cout << "\nDo you want to logout? (y/n): ";
        cin >> choice;

        if (choice == 'y' || choice == 'Y') {
            cout << "Logging out...\n";
            break;
        }
    }
}

void SystemController::adminMenu() {
    int choice;
    do {
        cout << "\n========== ADMIN MENU ==========\n";
        cout << "1. Register New Patient\n";
        cout << "2. View All Patients\n";
        cout << "3. Register New User (Login Credentials)\n";
        cout << "4. Logout\n";
        cout << "================================\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
        
            Person base = Person::Get_Valid_Person_Input("Person.txt");
            ofstream pout("Person.txt", ios::app);
            base.Save_To_File(pout);
            pout.close();

            Patient p;
            string id, blood, type, contact, status;
            double h, w;

            while (true) {
                cout << "Enter Patient ID (format P-0001): ";
                cin >> id;
                if (!p.isValidPatientId(id))
                    cout << "Invalid format. Must be P-XXXX.\n";
                else if (p.patientIdAlreadyExists(id, "Patient.txt"))
                    cout << "ID already exists. Try another.\n";
                else break;
            }

            while (true) {
                cout << "Enter Blood Group (A+/A-/B+/B-/AB+/AB-/O+/O-): ";
                cin >> blood;
                if (p.isValidBloodGroup(blood)) break;
                cout << "Invalid blood group.\n";
            }

            while (true) {
                cout << "Enter Patient Type (Inpatient/Outpatient/Emergency): ";
                cin >> type;
                if (p.isValidPatientType(type)) break;
                cout << "Invalid type.\n";
            }

            while (true) {
                cout << "Enter Height (cm, 50-250): ";
                cin >> h;
                if (p.isValidHeight(h)) break;
                cout << "Invalid height.\n";
            }

            while (true) {
                cout << "Enter Weight (kg, 1-300): ";
                cin >> w;
                if (p.isValidWeight(w)) break;
                cout << "Invalid weight.\n";
            }

            cin.ignore();
            while (true) {
                cout << "Enter Emergency Contact (11 digits): ";
                cin >> contact;
                if (p.isValidContact(contact)) break;
                cout << "Invalid contact number.\n";
            }

            cin.ignore();
            while (true) {
                cout << "Enter Status (Admitted/Discharged/Under Observation): ";
                getline(cin, status);
                if (p.isValidStatus(status)) break;
                cout << "Invalid status.\n";
            }

            // after collecting all patient fields, before Save_To_File:
            p.setLinkedCNIC(base.Get_CNIC());  // link the CNIC
            p.setPatientId(id);
            p.setBloodGroup(blood);
            p.setPatientType(type);
            p.setHeight(h);
            p.setWeight(w);
            p.setEmergencyContact(contact);
            p.setPatientStatus(status);

            ofstream patout("Patient.txt", ios::app);
            p.Save_To_File(patout);
            patout.close();

            string username, password;
            cout << "Assign username: ";
            cin >> username;
            cout << "Assign password: ";
            cin >> password;
            Login::Save_Login_to_File(username, password, "PATIENT");

            cout << "Patient registered successfully!\n";
        }

        else if (choice == 2) {
            ifstream patFile("Patient.txt");
            if (!patFile) {
                cout << "No patient records found.\n";
            } else {
                int count = 0;
                string line;
                while (getline(patFile, line)) {
                    if (line != "----------") continue;
                    
                    Patient p;
                    p.Load_From_File(patFile);  // loads patient fields + CNIC
                    
                    // Now search Person.txt for matching CNIC
                    ifstream perFile("Person.txt");
                    string sep;
                    bool found = false;
                    while (getline(perFile, sep)) {
                        if (sep != "----------") continue;
                        Person temp;
                        temp.Load_From_File(perFile);
                        if (temp.Get_CNIC() == p.get_CNIC()) {
                            found = true;
                            cout << "\n--- Patient " << ++count << " ---\n";
                            temp.Display_Info();   // Person fields
                            p.displayInfo();       // Patient fields
                            break;
                        }
                    }
                    if (!found) {
                        cout << "\n--- Patient " << ++count << " --- (Person record not found)\n";
                        p.displayInfo();
                    }
                }
                if (count == 0)
                    cout << "No patients on record.\n";
            }
        }

        else if (choice == 3) {
           
            string username, password, role;
            cout << "Username: "; cin >> username;
            cout << "Password: "; cin >> password;
            cout << "Role (ADMIN/DOCTOR/STAFF/PATIENT): "; cin >> role;
            while (role != "ADMIN" && role != "DOCTOR" && role != "STAFF" && role != "PATIENT") {
                cout << "Invalid. Enter again: ";
                cin >> role;
            }
            Login::Save_Login_to_File(username, password, role);
            cout << "User registered.\n";
        }

    } while (choice != 4); 
}

    void SystemController::doctorMenu() {
        cout << "Doctor menu coming soon.\n";
    }
    
    void SystemController::patientMenu() {
        cout << "Patient menu coming soon.\n";
    }
    
    void SystemController::staffMenu() {
        cout << "Staff menu coming soon.\n";
    }
