#include "Person.h"
#include "Patient.h"
#include "Login.h"
#include "Staff.h"
#include "Doctor.h"
#include "Appointment.h"
#include "SystemController.h"
#include "Billing.h"
#include "Room.h"
#include "Pharmacy.h"
#include "Medicine.h"
#include "Prescription.h"
#include "Ambulance.h"




void SystemController::showLogin() {
    string username, password, currentRole, currentUser;

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
        doctorMenu(currentUser);
    }
    else if (currentRole == "PATIENT") {
        patientMenu(currentUser);
    }
    else {
        cout << "Invalid credentials!\n";
    }
}

void SystemController::run() {
    while (true) {
        showLogin();

        // char choice;
        // cout << "\nDo you want to logout? (y/n): ";
        // cin >> choice;

        // if (choice == 'y' || choice == 'Y') {
        //     cout << "Logging out...\n";
        //     break;
        // }
    }
}

void SystemController::adminMenu() {

    Pharmacy pharmacy;
    pharmacy.loadInventory();
    pharmacy.loadPrescriptions();
    int choice;
    do {
        cout << "\n========== ADMIN MENU ==========\n";
        cout << "1.  Register New Patient\n";
        cout << "2.  View All Patients\n";
        cout << "3.  Update Patient Information\n";
        cout << "4.  View Patient Medical Records\n";
        cout << "5.  Register Staff Member\n";
        cout << "6.  View All Staff\n";
        cout << "7.  Update Staff Information\n";
        cout << "8.  Register New Doctor\n";
        cout << "9.  View All Doctors\n";
        cout << "10. Update Doctor Information\n";
        cout << "11. View Doctor Appointments\n";
        cout << "12. Register New Admin\n";
        cout << "13. Update Username/Password\n";
        cout << "14. Show Patient Bill\n";
        cout << "15. Show All Patient Bills\n";
        cout << "16. Set Patient Bill\n";
        cout << "17. Update Patient Bill\n";
        cout << "18. Discharge Patient\n";
        cout << "19. Assign Room to Patient\n";
        cout << "20. View Pharmacy Inventory\n";
        cout << "21. Add Medicine to Inventory\n";
        cout << "22. Issue Prescription to Patient\n";
        cout << "23. Search Patient Pharmacy Records\n";
        cout << "24. View Low Stock Medicines\n";
        cout << "25. View All Prescriptions\n";
        cout << "26. Restock Medicine\n";
        cout << "27. Register Ambulance\n";
        cout << "28. View All Ambulances\n";
        cout << "29. Update Ambulance Details\n";
        cout << "30. Logout\n";
        cout << "================================\n";
        cout << "Enter choice: ";
        cin >> choice;
 
        // REGISTER NEW PATIENT
        if (choice == 1) {
            Person base = Person::Get_Valid_Person_Input("Person.txt");
            ofstream pout("Person.txt", ios::app);
            base.Save_To_File(pout);
            pout.close();

            Patient p;
            string id, blood, type, contact, status;
            double h, w;

            id=p.generatePatientId();

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
            if(type == "inpatient") {
                string room;
                cout << "Enter Room Type: ";
                cin.ignore();
                getline(cin, room);  // ✅ fixes the "private room" space bug
                Room r;
                while(true) {
                    if(!r.isValidType(room)) {
                        cout << "Invalid Room Type. Try Again: ";
                        getline(cin, room);
                    }
                    else break;
                }
                bool avail = r.displayAvailableRoomsByType(room);
                if(!avail) {
                    cout << "No " << room << " rooms available. Cannot register inpatient without a room." << endl;
                    break;  // inpatient MUST have a room
                }
                string rid;
                cout << "Enter Room ID: ";
                cin >> rid;
                while(true) {
                    if(!r.isValidID(rid)) {
                        cout << "Invalid Format. Try Again: ";
                        cin >> rid;
                    }
                    else break;
                }
                while(!r.Check_occupied_by_roomID(rid,room)) {
                    cout << "Room not available. Enter another Room ID: ";
                    cin >> rid;
                }
                r.updatePatientID(rid, id);
                r.updateOccupancy(rid, 1);
                string date;
                cout << "Enter Admission Date: ";
                cin >> date;
                while(true) {
                    if(!r.isValidAdmitted(date)) {
                        cout << "Enter a Valid Date: ";
                        cin >> date;
                    }
                    else break;
                }
                r.updateDateAdmitted(rid, date);
            }
            else if(type == "emergency") {
                char choice;
                cout << "Assign a room to this emergency patient? (y/n): ";
                cin >> choice;
            
                if(choice == 'y' || choice == 'Y') {
                    string room;
                    cout << "Enter Room Type: ";
                    cin.ignore();
                    getline(cin, room);
                    Room r;
                    while(true) {
                        if(!r.isValidType(room)) {
                            cout << "Invalid Room Type. Try Again: ";
                            getline(cin, room);
                        }
                        else break;
                    }
                    bool avail = r.displayAvailableRoomsByType(room);
                    if(!avail) {
                        cout << "No " << room << " rooms available. Patient will be registered without a room." << endl;
                        // ✅ no break here — emergency can continue without room
                    }
                    else {
                        string rid;
                        cout << "Enter Room ID: ";
                        cin >> rid;
                        while(true) {
                            if(!r.isValidID(rid)) {
                                cout << "Invalid Format. Try Again: ";
                                cin >> rid;
                            }
                            else break;
                        }
                        while(!r.Check_occupied_by_roomID(rid,room)) {
                            cout << "Room not available. Enter another Room ID: ";
                            cin >> rid;
                        }
                        r.updatePatientID(rid, id);
                        r.updateOccupancy(rid, 1);
                        string date;
                        cout << "Enter Admission Date: ";
                        cin >> date;
                        while(true) {
                            if(!r.isValidAdmitted(date)) {
                                cout << "Enter a Valid Date: ";
                                cin >> date;
                            }
                            else break;
                        }
                        r.updateDateAdmitted(rid, date);
                    }
                }
                else {
                    cout << "Emergency patient registered without room assignment." << endl;
                    // ✅ perfectly valid
                }
            }
            else {
                // outpatient — no room at all
                cout << "Outpatient registered. No room assigned." << endl;
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

            if(type=="inpatient"){
                status="admitted";
            }
            else if(type=="outpatient"){
                status="not admitted";
            }
            else if(type=="emergency" && (choice='y' || choice=='Y')){
                status="admitted";
            }
            else{
                status="not admitted";
            }

            p.setLinkedCNIC(base.Get_CNIC());
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
            Login::Save_Login_to_File(username, password, "PATIENT", base.Get_CNIC());

            cout << "Patient registered successfully!\n";
        }

        // VIEW ALL PATIENTS
        else if (choice == 2) {
            ifstream patFile("Patient.txt");
            if (!patFile) {
                cout << "No patient records found.\n";
            }
            else {
                int count = 0;
                string line;
                while (getline(patFile, line)) {
                    if (line != "----------") continue;

                    Patient p;
                    p.Load_From_File(patFile);

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
                            temp.Display_Info();
                            p.displayInfo();
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

        // UPDATE PATIENT INFORMATION
        else if (choice == 3) {
            Patient p;
            string target_Id;
            cout << "Enter Patient CNIC to update : ";
            cin >> target_Id;
            bool id_found = false;

            ifstream infile("Patient.txt", ios::in);
            if (!infile) {
                cout << "No Patient Records Found!" << endl;
            }
            else {
                string line;
                while (getline(infile, line)) {
                    if (line == target_Id) {
                        id_found = true;
                    }
                }
                infile.close();

                if (id_found == false) {
                    cout << "Invalid CNIC!";
                }
            }

            if (id_found == true) {
                int field;
                cout << "\nWhat would you like to update?\n";
                cout << "--- Person Fields ---\n";
                cout << "1. Phone Number\n";
                cout << "2. Email\n";
                cout << "3. Address\n";
                cout << "4. Age\n";
                cout << "--- Patient Fields ---\n";
                cout << "5. Emergency Contact\n";
                cout << "6. Patient Status\n";
                cout << "7. Weight\n";
                cout << "8. Height\n";
                cout << "9. Patient Type\n";
                cout << "0. Cancel\n";
                cout << "Enter choice: ";
                cin >> field;

                bool personChanged = false;
                bool patientChanged = false;

                string new_phone = "", new_email = "", new_addr = "";
                int new_age = 0;
                string new_contact = "", new_status = "", new_type = "";
                double new_weight = 0, new_height = 0;

                if (field == 1) {
                    while (true) {
                        cout << "Enter new Phone Number: ";
                        cin >> new_phone;
                        if (p.Is_Valid_Phone(new_phone)) break;
                        cout << "Invalid Phone Number.\n";
                    }
                    p.Set_Phone_Num(new_phone);
                    personChanged = true;
                }
                else if (field == 2) {
                    while (true) {
                        cout << "Enter new Email: ";
                        cin >> new_email;
                        if (p.Is_Valid_Email(new_email)) break;
                        cout << "Invalid Email.\n";
                    }
                    p.Set_Email(new_email);
                    personChanged = true;
                }
                else if (field == 3) {
                    while (true) {
                        cout << "Enter new Address: ";
                        cin >> new_addr;
                        if (p.Is_Valid_Address(new_addr)) break;
                        cout << "Invalid Address.\n";
                    }
                    p.Set_Address(new_addr);
                    personChanged = true;
                }
                else if (field == 4) {
                    while (true) {
                        cout << "Enter new Age: ";
                        cin >> new_age;
                        if (p.Is_Valid_Age(new_age)) break;
                        cout << "Invalid Age.\n";
                    }
                    p.Set_Age(new_age);
                    personChanged = true;
                }
                else if (field == 5) {
                    while (true) {
                        cout << "Enter new emergency contact (11 digits): ";
                        cin >> new_contact;
                        if (p.isValidContact(new_contact)) break;
                        cout << "Invalid contact.\n";
                    }
                    p.setEmergencyContact(new_contact);
                    patientChanged = true;
                }
                else if (field == 6) {
                    cin.ignore();
                    while (true) {
                        cout << "Enter new status (Admitted/Discharged/Under Observation): ";
                        getline(cin, new_status);
                        if (p.isValidStatus(new_status)) break;
                        cout << "Invalid status.\n";
                    }
                    p.setPatientStatus(new_status);
                    patientChanged = true;
                }
                else if (field == 7) {
                    while (true) {
                        cout << "Enter new weight (kg, 1-300): ";
                        cin >> new_weight;
                        if (p.isValidWeight(new_weight)) break;
                        cout << "Invalid weight.\n";
                    }
                    p.setWeight(new_weight);
                    patientChanged = true;
                }
                else if (field == 8) {
                    while (true) {
                        cout << "Enter new height (cm, 50-250): ";
                        cin >> new_height;
                        if (p.isValidHeight(new_height)) break;
                        cout << "Invalid height.\n";
                    }
                    p.setHeight(new_height);
                    patientChanged = true;
                }
                else if (field == 9) {
                    while (true) {
                        cout << "Enter new patient type (Inpatient/Outpatient/Emergency): ";
                        cin >> new_type;
                        if (p.isValidPatientType(new_type)) break;
                        cout << "Invalid type.\n";
                    }
                    p.setPatientType(new_type);
                    patientChanged = true;
                }
                else {
                    cout << "Cancelled.\n"; continue;
                }

                if (personChanged) {
                    ifstream fin("Person.txt");
                    ofstream fout("Person_temp.txt");
                    string ln;

                    while (getline(fin, ln)) {
                        if (ln == "----------") {
                            fout << ln << "\n";

                            string cnic, name, age, gender, phone, email, address;
                            getline(fin, cnic);
                            getline(fin, name);
                            getline(fin, age);
                            getline(fin, gender);
                            getline(fin, phone);
                            getline(fin, email);
                            getline(fin, address);

                            if (cnic == target_Id) {
                                fout << cnic << "\n";
                                fout << name << "\n";

                                if (field == 4)
                                    fout << new_age << "\n";
                                else
                                    fout << age << "\n";

                                fout << gender << "\n";

                                if (field == 1)
                                    fout << new_phone << "\n";
                                else
                                    fout << phone << "\n";

                                if (field == 2)
                                    fout << new_email << "\n";
                                else
                                    fout << email << "\n";

                                if (field == 3)
                                    fout << new_addr << "\n";
                                else
                                    fout << address << "\n";
                            }
                            else {
                                fout << cnic    << "\n";
                                fout << name    << "\n";
                                fout << age     << "\n";
                                fout << gender  << "\n";
                                fout << phone   << "\n";
                                fout << email   << "\n";
                                fout << address << "\n";
                            }
                        }
                    }

                    fin.close();
                    fout.close();
                    remove("Person.txt");
                    rename("Person_temp.txt", "Person.txt");
                }

                if (patientChanged) {
                    ifstream fin("Patient.txt");
                    ofstream fout("Patient_temp.txt");
                    string ln;

                    while (getline(fin, ln)) {
                        if (ln == "----------") {
                            fout << ln << "\n";

                            string cnic, patientId, bloodGroup, patientType, height, weight, contact, status;
                            getline(fin, cnic);
                            getline(fin, patientId);
                            getline(fin, bloodGroup);
                            getline(fin, patientType);
                            getline(fin, height);
                            getline(fin, weight);
                            getline(fin, contact);
                            getline(fin, status);

                            if (cnic == target_Id) {
                                fout << cnic       << "\n";
                                fout << patientId  << "\n";
                                fout << bloodGroup << "\n";

                                if (field == 9)
                                    fout << new_type << "\n";
                                else
                                    fout << patientType << "\n";

                                if (field == 8)
                                    fout << new_height << "\n";
                                else
                                    fout << height << "\n";

                                if (field == 7)
                                    fout << new_weight << "\n";
                                else
                                    fout << weight << "\n";

                                if (field == 5)
                                    fout << new_contact << "\n";
                                else
                                    fout << contact << "\n";

                                if (field == 6)
                                    fout << new_status << "\n";
                                else
                                    fout << status << "\n";
                            }
                            else {
                                fout << cnic        << "\n";
                                fout << patientId   << "\n";
                                fout << bloodGroup  << "\n";
                                fout << patientType << "\n";
                                fout << height      << "\n";
                                fout << weight      << "\n";
                                fout << contact     << "\n";
                                fout << status      << "\n";
                            }
                        }
                    }

                    fin.close();
                    fout.close();
                    remove("Patient.txt");
                    rename("Patient_temp.txt", "Patient.txt");
                }

                cout << "Record updated successfully!\n";
            }
        }

        // VIEW PATIENT MEDICAL RECORDS
        else if (choice == 4) {
            string patient_id;
            Patient p;

            while (true) {
                cout << "Enter Patient ID (format P-0001): ";
                cin >> patient_id;
                if (!p.isValidPatientId(patient_id))
                    cout << "Invalid format. Must be P-XXXX.\n";
                else break;
            }

            ifstream infile("MedicalRecords.txt");
            if (!infile) {
                cout << "No medical records found.\n";
            }
            else {
                string line;
                bool found = false;
                int visitNum = 1;

                cout << "\n========== Medical History for Patient " << patient_id << " ==========\n";

                while (getline(infile, line)) {
                    if (line != "----------") continue;

                    string recId, patId, docId, diagnosis, medicine, dosage, date;
                    getline(infile, recId);
                    getline(infile, patId);
                    getline(infile, docId);
                    getline(infile, diagnosis);
                    getline(infile, medicine);
                    getline(infile, dosage);
                    getline(infile, date);

                    if (patId == patient_id) {
                        found = true;
                        cout << "\n--- Visit " << visitNum++ << " ---\n";
                        cout << "Record ID  : " << recId     << "\n";
                        cout << "Doctor ID  : " << docId     << "\n";
                        cout << "Diagnosis  : " << diagnosis << "\n";
                        cout << "Medicine   : " << medicine  << "\n";
                        cout << "Dosage     : " << dosage    << "\n";
                        cout << "Date       : " << date      << "\n";
                    }
                }

                if (!found)
                    cout << "No records found for Patient ID: " << patient_id << "\n";
                else
                    cout << "\n=====================================================\n";
            }
        }

        // REGISTER STAFF MEMBER
        else if (choice == 5) {
            Person base = Person::Get_Valid_Person_Input("Person.txt");
            ofstream pout("Person.txt", ios::app);
            base.Save_To_File(pout);
            pout.close();

            Staff s;
            string id, dept, job, shift, date, status;
            double salary;

            id=s.generateStaffId();

            while (true) {
                cout << "Enter Department: ";
                cin >> dept;
                if (s.isValidDepartment(dept)) break;
                cout << "Invalid Department.\n";
            }

            cin.ignore();
            while (true) {
                cout << "Enter Job Title: ";
                cin >> job;
                if (s.isValidJobTitle(job)) break;
                cout << "Invalid Job Title.\n";
            }

            while (true) {
                cout << "Enter Shift: ";
                cin >> shift;
                if (s.isValidShift(shift)) break;
                cout << "Invalid Shift.\n";
            }

            cin.ignore();
            while (true) {
                cout << "Enter Salary: ";
                cin >> salary;
                if (s.isValidSalary(salary)) break;
                cout << "Invalid salary.\n";
            }

            cin.ignore();
            while (true) {
                cout << "Enter Joining date (date/month/year): ";
                cin >> date;
                if (s.isValidJoiningDate(date)) break;
                cout << "Invalid Date.\n";
            }

            while (true) {
                cout << "Enter Employment Status (Active /On Leave/Terminated ): ";
                cin >> status;
                if (s.isValidEmploymentStatus(status)) break;
                cout << "Invalid status.\n";
            }

            s.setLinkedCNIC(base.Get_CNIC());
            s.setStaffId(id);
            s.setDepartment(dept);
            s.setJobTitle(job);
            s.setShift(shift);
            s.setSalary(salary);
            s.setJoiningDate(date);
            s.setEmploymentStatus(status);

            ofstream staffout("Staff.txt", ios::app);
            s.Save_To_File(staffout);
            staffout.close();
            cout << "Staff registered successfully!\n";
        }

        // VIEW ALL STAFF
        else if (choice == 6) {
            ifstream staffFile("Staff.txt");
            if (!staffFile) {
                cout << "No Staff records found.\n";
            }
            else {
                int count = 0;
                string line;
                while (getline(staffFile, line)) {
                    if (line != "----------") continue;

                    Staff s;
                    s.Load_From_File(staffFile);

                    ifstream perFile("Person.txt");
                    string sep;
                    bool found = false;
                    while (getline(perFile, sep)) {
                        if (sep != "----------") continue;
                        Person temp;
                        temp.Load_From_File(perFile);
                        if (temp.Get_CNIC() == s.get_CNIC()) {
                            found = true;
                            cout << "\n--- Staff " << ++count << " ---\n";
                            temp.Display_Info();
                            s.displayInfo();
                            break;
                        }
                    }
                    if (!found) {
                        cout << "\n--- Staff " << ++count << " --- (Staff record not found)\n";
                        s.displayInfo();
                    }
                }
                if (count == 0)
                    cout << "No Staff on record.\n";
            }
        }

        // UPDATE STAFF INFORMATION
        else if (choice == 7) {
            Staff s;
            string target_Id;
            cout << "Enter Staff CNIC to update : ";
            cin >> target_Id;
            bool id_found = false;

            ifstream infile("Staff.txt", ios::in);
            if (!infile) {
                cout << "No Staff Records Found!" << endl;
            }
            else {
                string line;
                while (getline(infile, line)) {
                    if (line == target_Id) {
                        id_found = true;
                    }
                }
                infile.close();

                if (id_found == false) {
                    cout << "Invalid CNIC!";
                }
                else {
                    int field;
                    cout << "\nWhat would you like to update?\n";
                    cout << "--- Person Fields ---\n";
                    cout << "1. Phone Number\n";
                    cout << "2. Email\n";
                    cout << "3. Address\n";
                    cout << "4. Age\n";
                    cout << "--- Staff Fields ---\n";
                    cout << "5. Department\n";
                    cout << "6. Job Title\n";
                    cout << "7. Shift\n";
                    cout << "8. Salary\n";
                    cout << "9. Employment Status\n";
                    cout << "10. Is Paid\n";
                    cout << "0. Cancel\n";
                    cout << "Enter choice: ";
                    cin >> field;

                    bool personChanged = false;
                    bool staffChanged = false;

                    string new_phone = "", new_email = "", new_addr = "";
                    int new_age = 0;
                    string new_dept = "", new_job = "", new_shift = "", new_status = "", new_paid = "";
                    double new_salary = 0;

                    if (field == 1) {
                        while (true) {
                            cout << "Enter new Phone Number: ";
                            cin >> new_phone;
                            if (s.Is_Valid_Phone(new_phone)) break;
                            cout << "Invalid Phone Number.\n";
                        }
                        s.Set_Phone_Num(new_phone);
                        personChanged = true;
                    }
                    else if (field == 2) {
                        while (true) {
                            cout << "Enter new Email: ";
                            cin >> new_email;
                            if (s.Is_Valid_Email(new_email)) break;
                            cout << "Invalid Email.\n";
                        }
                        s.Set_Email(new_email);
                        personChanged = true;
                    }
                    else if (field == 3) {
                        while (true) {
                            cout << "Enter new Address: ";
                            cin >> new_addr;
                            if (s.Is_Valid_Address(new_addr)) break;
                            cout << "Invalid Address.\n";
                        }
                        s.Set_Address(new_addr);
                        personChanged = true;
                    }
                    else if (field == 4) {
                        while (true) {
                            cout << "Enter new Age: ";
                            cin >> new_age;
                            if (s.Is_Valid_Age(new_age)) break;
                            cout << "Invalid Age.\n";
                        }
                        s.Set_Age(new_age);
                        personChanged = true;
                    }
                    else if (field == 5) {
                        while (true) {
                            cout << "Enter new Department: ";
                            cin >> new_dept;
                            if (s.isValidDepartment(new_dept)) break;
                            cout << "Invalid Department.\n";
                        }
                        s.setDepartment(new_dept);
                        staffChanged = true;
                    }
                    else if (field == 6) {
                        while (true) {
                            cout << "Enter new Job Title: ";
                            cin >> new_job;
                            if (s.isValidJobTitle(new_job)) break;
                            cout << "Invalid Job Title.\n";
                        }
                        s.setJobTitle(new_job);
                        staffChanged = true;
                    }
                    else if (field == 7) {
                        while (true) {
                            cout << "Enter new Shift: ";
                            cin >> new_shift;
                            if (s.isValidShift(new_shift)) break;
                            cout << "Invalid Shift.\n";
                        }
                        s.setShift(new_shift);
                        staffChanged = true;
                    }
                    else if (field == 8) {
                        while (true) {
                            cout << "Enter new Salary: ";
                            cin >> new_salary;
                            if (s.isValidSalary(new_salary)) break;
                            cout << "Invalid salary.\n";
                        }
                        s.setSalary(new_salary);
                        staffChanged = true;
                    }
                    else if (field == 9) {
                        while (true) {
                            cout << "Enter new Employment Status: ";
                            cin >> new_status;
                            if (s.isValidEmploymentStatus(new_status)) break;
                            cout << "Invalid Employment Status.\n";
                        }
                        s.setEmploymentStatus(new_status);
                        staffChanged = true;
                    }
                    else if (field == 10) {
                        while (true) {
                            cout << "Enter new salary status: ";
                            cin >> new_paid;
                            if (s.isValidPaid(new_paid)) break;
                            cout << "Invalid Status.\n";
                        }
                        s.Set_Is_Paid(new_paid);
                        staffChanged = true;
                    }
                    else {
                        cout << "Cancelled.\n"; continue;
                    }

                    if (personChanged) {
                        ifstream fin("Person.txt");
                        ofstream fout("Person_temp.txt");
                        string ln;

                        while (getline(fin, ln)) {
                            if (ln == "----------") {
                                fout << ln << "\n";

                                string cnic, name, age, gender, phone, email, address;
                                getline(fin, cnic);
                                getline(fin, name);
                                getline(fin, age);
                                getline(fin, gender);
                                getline(fin, phone);
                                getline(fin, email);
                                getline(fin, address);

                                if (cnic == target_Id) {
                                    fout << cnic << "\n";
                                    fout << name << "\n";

                                    if (field == 4)
                                        fout << new_age << "\n";
                                    else
                                        fout << age << "\n";

                                    fout << gender << "\n";

                                    if (field == 1)
                                        fout << new_phone << "\n";
                                    else
                                        fout << phone << "\n";

                                    if (field == 2)
                                        fout << new_email << "\n";
                                    else
                                        fout << email << "\n";

                                    if (field == 3)
                                        fout << new_addr << "\n";
                                    else
                                        fout << address << "\n";
                                }
                                else {
                                    fout << cnic    << "\n";
                                    fout << name    << "\n";
                                    fout << age     << "\n";
                                    fout << gender  << "\n";
                                    fout << phone   << "\n";
                                    fout << email   << "\n";
                                    fout << address << "\n";
                                }
                            }
                        }

                        fin.close();
                        fout.close();
                        remove("Person.txt");
                        rename("Person_temp.txt", "Person.txt");
                    }

                    if (staffChanged) {
                        ifstream fin("Staff.txt");
                        ofstream fout("Staff_temp.txt");
                        string ln;

                        while (getline(fin, ln)) {
                            if (ln == "----------") {
                                fout << ln << "\n";

                                string cnic, staffid, dept, job, shift, salary, date, status, paid;
                                getline(fin, cnic);
                                getline(fin, staffid);
                                getline(fin, dept);
                                getline(fin, job);
                                getline(fin, shift);
                                getline(fin, salary);
                                getline(fin, date);
                                getline(fin, status);
                                getline(fin, paid);

                                if (cnic == target_Id) {
                                    fout << cnic    << "\n";
                                    fout << staffid << "\n";

                                    if (field == 5)
                                        fout << new_dept << "\n";
                                    else
                                        fout << dept << "\n";

                                    if (field == 6)
                                        fout << new_job << "\n";
                                    else
                                        fout << job << "\n";

                                    if (field == 7)
                                        fout << new_shift << "\n";
                                    else
                                        fout << shift << "\n";

                                    if (field == 8)
                                        fout << new_salary << "\n";
                                    else
                                        fout << salary << "\n";

                                    fout << date << "\n";

                                    if (field == 9)
                                        fout << new_status << "\n";
                                    else
                                        fout << status << "\n";

                                    if (field == 10)
                                        fout << new_paid << "\n";
                                    else
                                        fout << paid << "\n";
                                }
                                else {
                                    fout << cnic    << "\n";
                                    fout << staffid << "\n";
                                    fout << dept    << "\n";
                                    fout << job     << "\n";
                                    fout << shift   << "\n";
                                    fout << salary  << "\n";
                                    fout << date    << "\n";
                                    fout << status  << "\n";
                                    fout << paid    << "\n";
                                }
                            }
                        }

                        fin.close();
                        fout.close();
                        remove("Staff.txt");
                        rename("Staff_temp.txt", "Staff.txt");
                    }
                    if (staffChanged || personChanged) {
                        cout << "Record Updated Successfully!" << endl;
                    }
                }
            }
        }

        // REGISTER NEW DOCTOR
        else if (choice == 8) {
            Person base = Person::Get_Valid_Person_Input("Person.txt");
            ofstream pout("Person.txt", ios::app);
            base.Save_To_File(pout);
            pout.close();
            
            Doctor d;
            d = d.Get_Valid_Doctor_Input("Doctor.txt", base.Get_CNIC());
            d.setLinkedCNIC(base.Get_CNIC());
            
            ofstream docout("Doctor.txt", ios::app);
            d.Save_To_File(docout);
            docout.close();

            string username, password;
            cout << "Assign username: ";
            cin >> username;
            cout << "Assign password: ";
            cin >> password;
            Login::Save_Login_to_File(username, password, "DOCTOR", base.Get_CNIC());

            cout << "Doctor registered successfully!\n";
        }

        // VIEW ALL DOCTORS
        else if (choice == 9) {
            ifstream docFile("Doctor.txt");
            if (!docFile) {
                cout << "No Doctor records found.\n";
            }
            else {
                int count = 0;
                string line;
                while (getline(docFile, line)) {
                    if (line != "----------") continue;

                    Doctor d;
                    d.Load_From_File(docFile);

                    ifstream perFile("Person.txt");
                    string sep;
                    bool found = false;
                    while (getline(perFile, sep)) {
                        if (sep != "----------") continue;
                        Person temp;
                        temp.Load_From_File(perFile);
                        if (temp.Get_CNIC() == d.get_CNIC()) {
                            found = true;
                            cout << "\n--- Doctor " << ++count << " ---\n";
                            temp.Display_Info();
                            d.Display_Info();
                            break;
                        }
                    }
                    perFile.close();

                    if (!found) {
                        cout << "\n--- Doctor " << ++count << " --- (Person record not found)\n";
                        d.Display_Info();
                    }
                }
                if (count == 0)
                    cout << "No doctors on record.\n";
            }
        }

        // UPDATE DOCTOR INFORMATION
        else if (choice == 10) {
            Doctor d;
            string target_Id;
            cout << "Enter Doctor CNIC to update: ";
            cin >> target_Id;
            bool id_found = false;

            ifstream infile("Doctor.txt", ios::in);
            if (!infile) {
                cout << "No Doctor Records Found!" << endl;
            }
            else {
                string line;
                while (getline(infile, line)) {
                    if (line == target_Id) {
                        id_found = true;
                    }
                }
                infile.close();

                if (id_found == false) {
                    cout << "Invalid CNIC!\n";
                }
                else {
                    int field;
                    cout << "\nWhat would you like to update?\n";
                    cout << "--- Person Fields ---\n";
                    cout << "1. Phone Number\n";
                    cout << "2. Email\n";
                    cout << "3. Address\n";
                    cout << "4. Age\n";
                    cout << "--- Doctor Fields ---\n";
                    cout << "5. Specialization\n";
                    cout << "6. Qualification\n";
                    cout << "7. Experience Years\n";
                    cout << "8. Consultation Fee\n";
                    cout << "9. Availability\n";
                    cout << "10. Availability Status\n";
                    cout << "0. Cancel\n";
                    cout << "Enter choice: ";
                    cin >> field;

                    bool personChanged = false;
                    bool doctorChanged = false;

                    string new_phone = "", new_email = "", new_addr = "";
                    int new_age = 0, new_exp = 0;
                    string new_spec = "", new_qual = "", new_avail = "", new_status = "";
                    double new_fee = 0;

                    if (field == 1) {
                        while (true) {
                            cout << "Enter new Phone Number: ";
                            cin >> new_phone;
                            if (d.Is_Valid_Phone(new_phone)) break;
                            cout << "Invalid Phone Number.\n";
                        }
                        personChanged = true;
                    }
                    else if (field == 2) {
                        while (true) {
                            cout << "Enter new Email: ";
                            cin >> new_email;
                            if (d.Is_Valid_Email(new_email)) break;
                            cout << "Invalid Email.\n";
                        }
                        personChanged = true;
                    }
                    else if (field == 3) {
                        while (true) {
                            cout << "Enter new Address: ";
                            cin >> new_addr;
                            if (d.Is_Valid_Address(new_addr)) break;
                            cout << "Invalid Address.\n";
                        }
                        personChanged = true;
                    }
                    else if (field == 4) {
                        while (true) {
                            cout << "Enter new Age: ";
                            cin >> new_age;
                            if (d.Is_Valid_Age(new_age)) break;
                            cout << "Invalid Age.\n";
                        }
                        personChanged = true;
                    }
                    else if (field == 5) {
                        while (true) {
                            cout << "Enter new Specialization: ";
                            cin >> new_spec;
                            if (d.isValidSpecialization(new_spec)) break;
                            cout << "Invalid Specialization.\n";
                        }
                        doctorChanged = true;
                    }
                    else if (field == 6) {
                        while (true) {
                            cout << "Enter new Qualification: ";
                            cin >> new_qual;
                            if (d.isValidQualification(new_qual)) break;
                            cout << "Invalid Qualification.\n";
                        }
                        doctorChanged = true;
                    }
                    else if (field == 7) {
                        int new_age = d.getAgeFromPersonFile(target_Id);
                        if (new_age == -1) new_age = 25;  // fallback
                        while (true) {
                            cout << "Enter Experience Years: ";
                            cin >> new_exp;
                            if (d.isValidExperience(new_exp, new_age)) break;
                            cout << "Invalid Experience. Max allowed for age " << new_age << ": " << (new_age - 23) << " yrs.\n";
                        }
                        doctorChanged = true;
                    }
                    else if (field == 8) {
                        while (true) {
                            cout << "Enter new Consultation Fee: ";
                            cin >> new_fee;
                            if (d.isValidFee(new_fee)) break;
                            cout << "Invalid Fee.\n";
                        }
                        doctorChanged = true;
                    }
                    else if (field == 9) {
                        cin.ignore();
                        while (true) {
                            cout << "Enter new Availability (e.g. Mon-Fri 9AM-5PM): ";
                            getline(cin, new_avail);
                            if (!new_avail.empty()) break;
                            cout << "Invalid Availability.\n";
                        }
                        doctorChanged = true;
                    }
                    else if (field == 10) {
                        while (true) {
                            cout << "Enter new Availability Status (Available/Unavailable/On Leave): ";
                            cin >> new_status;
                            if (d.isValidAvailabilityStatus(new_status)) break;
                            cout << "Invalid Status.\n";
                        }
                        doctorChanged = true;
                    }
                    else {
                        cout << "Cancelled.\n"; continue;
                    }

                    if (personChanged) {
                        ifstream fin("Person.txt");
                        ofstream fout("Person_temp.txt");
                        string ln;

                        while (getline(fin, ln)) {
                            if (ln == "----------") {
                                fout << ln << "\n";

                                string cnic, name, age, gender, phone, email, address;
                                getline(fin, cnic);
                                getline(fin, name);
                                getline(fin, age);
                                getline(fin, gender);
                                getline(fin, phone);
                                getline(fin, email);
                                getline(fin, address);

                                if (cnic == target_Id) {
                                    fout << cnic << "\n";
                                    fout << name << "\n";

                                    if (field == 4)
                                        fout << new_age << "\n";
                                    else
                                        fout << age << "\n";

                                    fout << gender << "\n";

                                    if (field == 1)
                                        fout << new_phone << "\n";
                                    else
                                        fout << phone << "\n";

                                    if (field == 2)
                                        fout << new_email << "\n";
                                    else
                                        fout << email << "\n";

                                    if (field == 3)
                                        fout << new_addr << "\n";
                                    else
                                        fout << address << "\n";
                                }
                                else {
                                    fout << cnic    << "\n";
                                    fout << name    << "\n";
                                    fout << age     << "\n";
                                    fout << gender  << "\n";
                                    fout << phone   << "\n";
                                    fout << email   << "\n";
                                    fout << address << "\n";
                                }
                            }
                        }

                        fin.close();
                        fout.close();
                        remove("Person.txt");
                        rename("Person_temp.txt", "Person.txt");
                    }

                    if (doctorChanged) {
                        ifstream fin("Doctor.txt");
                        ofstream fout("Doctor_temp.txt");
                        string ln;

                        while (getline(fin, ln)) {
                            if (ln == "----------") {
                                fout << ln << "\n";

                                string cnic, docId, spec, qual, exp, fee, avail, status;
                                getline(fin, cnic);
                                getline(fin, docId);
                                getline(fin, spec);
                                getline(fin, qual);
                                getline(fin, exp);
                                getline(fin, fee);
                                getline(fin, avail);
                                getline(fin, status);

                                if (cnic == target_Id) {
                                    fout << cnic  << "\n";
                                    fout << docId << "\n";

                                    if (field == 5)
                                        fout << new_spec << "\n";
                                    else
                                        fout << spec << "\n";

                                    if (field == 6)
                                        fout << new_qual << "\n";
                                    else
                                        fout << qual << "\n";

                                    if (field == 7)
                                        fout << new_exp << "\n";
                                    else
                                        fout << exp << "\n";

                                    if (field == 8)
                                        fout << new_fee << "\n";
                                    else
                                        fout << fee << "\n";

                                    if (field == 9)
                                        fout << new_avail << "\n";
                                    else
                                        fout << avail << "\n";

                                    if (field == 10)
                                        fout << new_status << "\n";
                                    else
                                        fout << status << "\n";
                                }
                                else {
                                    fout << cnic   << "\n";
                                    fout << docId  << "\n";
                                    fout << spec   << "\n";
                                    fout << qual   << "\n";
                                    fout << exp    << "\n";
                                    fout << fee    << "\n";
                                    fout << avail  << "\n";
                                    fout << status << "\n";
                                }
                            }
                        }

                        fin.close();
                        fout.close();
                        remove("Doctor.txt");
                        rename("Doctor_temp.txt", "Doctor.txt");
                    }

                    cout << "Record updated successfully!\n";
                }
            }
        }

        // VIEW DOCTOR APPOINTMENTS
// VIEW DOCTOR APPOINTMENTS
else if (choice == 11) {
    string docId;
    cout << "Enter Doctor ID: ";
    cin >> docId;

    ifstream infile("Appointment.txt");
    if (!infile) {
        cout << "No appointments found.\n";
    }
    else {
        string line;
        bool found = false;
        int count = 0;

        cout << "\n========== Appointments for Doctor " << docId << " ==========\n";

        while (getline(infile, line)) {
            if (line != "-----------") continue;

            string appId, patId, dId, date, time, reason, status;
            getline(infile, appId);
            getline(infile, patId);
            getline(infile, dId);
            getline(infile, date);
            getline(infile, time);
            getline(infile, reason);
            getline(infile, status);

            if (dId == docId) {
                found = true;
                cout << "\n--- Appointment " << ++count << " ---\n";
                cout << "Appointment ID : " << appId  << "\n";
                cout << "Patient ID     : " << patId  << "\n";
                cout << "Date           : " << date   << "\n";
                cout << "Time           : " << time   << "\n";
                cout << "Reason         : " << reason << "\n";
                cout << "Status         : " << status << "\n";
            }
        }

        if (found == false)
            cout << "No appointments found for Doctor ID: " << docId << "\n";
        else
            cout << "\n=====================================================\n";
    }
}
        // REGISTER NEW USER
        else if (choice == 12) {
            Person base = Person::Get_Valid_Person_Input("Person.txt");
            ofstream pout("Person.txt", ios::app);
            base.Save_To_File(pout);
            pout.close();
            string cnic;
            cnic=base.Get_CNIC();

            string username, password;
            cout << "Username: "; cin >> username;
            cout << "Password: "; cin >> password;

            Login::Save_Login_to_File(username, password,"ADMIN",cnic);
            cout << "User registered.\n";

        }

        // UPDATE USERNAME/PASSWORD
        else if (choice == 13) {

            string current_cnic, new_username, new_password;
            int updateChoice;
        
            cout << "What do you want to update:\n";
            cout << "1. Username\n";
            cout << "2. Password\n";
            cout << "Enter Choice: ";
            cin >> updateChoice;
        
            cout << "Enter CNIC: ";
            cin >> current_cnic;
        
            bool found = false;
        
            ifstream fin("Users.txt");
            ofstream fout("Users_temp.txt");
        
            string ln;
        
            while (getline(fin, ln)) {
        
                if (ln == "----------") {
        
                    string cnic, username, password, role;
        
                    getline(fin, cnic);
                    getline(fin, username);
                    getline(fin, password);
                    getline(fin, role);
        
                    if (cnic == current_cnic) {
                        found = true;
        
                        cout << "User found.\n";
        
                        if (updateChoice == 1) {
                            cout << "Enter New Username: ";
                            cin >> new_username;
                            username = new_username;
                        }
                        else if (updateChoice == 2) {
                            cout << "Enter New Password: ";
                            cin >> new_password;
                            password = new_password;
                        }
                        else {
                            cout << "Invalid choice.\n";
                        }
                    }
        
                    // write back (updated or unchanged)
                    fout << "----------\n";
                    fout << cnic << "\n";
                    fout << username << "\n";
                    fout << password << "\n";
                    fout << role << "\n";
                }
            }
        
            fin.close();
            fout.close();
        
            remove("Users.txt");
            rename("Users_temp.txt", "Users.txt");
        
            if (found)
                cout << "Record updated successfully!\n";
            else
                cout << "CNIC not found!\n";
        }
        else if(choice==14){
            string patientID;
            while (true){
                cout<<"Enter Patient ID: ";
                cin>>patientID;
                Patient p;
                if(p.isValidPatientId(patientID) && p.patientIdAlreadyExists(patientID,"Patient.txt")){
                    break;
                }
                else{
                    if(!p.isValidPatientId(patientID)){
                        cout<<"Invalid Patient ID (Format: P-0001 )";
                        break;
                    }
                    else{
                        cout<<"Patient ID does not Exist";
                        break;
                    }
                }
            }
            Billing b;
            b.displayHeader();
            b.searchByPatientId(patientID);
        }
        else if (choice == 15) {
            Billing b;
            b.displayAllPatientBills();
        }
        
        else if(choice==16){
            string patientID;
            cout<<"Enter Patient ID: ";
            cin>>patientID;
            Patient p;
            if(p.isValidPatientId(patientID) && p.patientIdAlreadyExists(patientID,"Patient.txt")){
                Billing b;
                b.setBilling("ADMIN",patientID);
            }
            else{
                if(!p.isValidPatientId(patientID)){
                    cout<<"Invalid Patient ID (Format: P-0001 )";
                }
                else{
                    cout<<"Patient ID does not Exist";
                }
            }
        }
        else if(choice==17){
            string patientID;
            cout<<"Enter Patient ID: ";
            cin>>patientID;
            Patient p;
            if(p.isValidPatientId(patientID) && p.patientIdAlreadyExists(patientID,"Patient.txt")){
                Billing b;
                b.displayHeader();
                b.updateStatus("ADMIN",patientID);
            }
            else{
                if(!p.isValidPatientId(patientID)){
                    cout<<"Invalid Patient ID (Format: P-0001 )";
                }
                else{
                    cout<<"Patient ID does not Exist";
                }
            }
        }
        else if(choice==18){
            string patientID;
            cout<<"Enter Patient ID: ";
            cin>>patientID;
            Patient p;
            if (!p.isValidPatientId(patientID)) {
                cout << "Invalid ID";
                return;
            }
            
            if (!p.patientIdAlreadyExists(patientID,"Patient.txt")) {
                cout << "Does not exist";
                return;
            }
            
            Room r;
            
            string ad_date = r.getAdmissionDate(patientID);
            
            if (ad_date == "") {
                cout << "Patient not in room";
                return;
            }
            
            string date;
            cout << "Enter Discharge Date: ";
            cin >> date;
            
            while (!r.isValidDischarged(date, ad_date)) {
                cout << "Enter Valid Date: ";
                cin >> date;
            }
            
            r.patient_discharged(patientID, date);
        }
        
        else if(choice==19){

            string patientID;
            cout<<"Enter Patient ID: ";
            cin>>patientID;
            Patient p;
            if(p.isValidPatientId(patientID) && p.patientIdAlreadyExists(patientID,"Patient.txt")){
                string room;
                cout << "Enter Room Type: ";
                cin.ignore();
                getline(cin, room);  
                Room r;
                while(true) {
                    if(!r.isValidType(room)) {
                        cout << "Invalid Room Type. Try Again: ";
                        getline(cin, room);
                    }
                    else break;
                }
                bool avail = r.displayAvailableRoomsByType(room);
                if(!avail) {
                    cout << "No " << room << " rooms available. Cannot register inpatient without a room." << endl;
                    break;  // inpatient MUST have a room
                }
                string rid;
                cout << "Enter Room ID: ";
                cin >> rid;
                while(true) {
                    if(!r.isValidID(rid)) {
                        cout << "Invalid Format. Try Again: ";
                        cin >> rid;
                    }
                    else break;
                }
                while(!r.Check_occupied_by_roomID(rid,room)) {
                    cout << "Room not available. Enter another Room ID: ";
                    cin >> rid;
                }
                r.updatePatientID(rid, patientID);
                r.updateOccupancy(rid, 1);
                string date;
                cout << "Enter Admission Date: ";
                cin >> date;
                while(true) {
                    if(!r.isValidAdmitted(date)) {
                        cout << "Enter a Valid Date: ";
                        cin >> date;
                    }
                    else break;
                }
                r.updateDateAdmitted(rid, date);
            }
            else{
                if(!p.isValidPatientId(patientID)){
                    cout<<"Invalid Patient ID (Format: P-0001 )";
                }
                else{
                    cout<<"Patient ID does not Exist";
                }
            }
        }
        else if (choice == 20) {
            //Pharmacy pharmacy;
            //pharmacy.loadInventory();
            pharmacy.display();
        }
        
        else if (choice == 21) {
            string name, dosage;
            int stock;
            double price;
        
            cout << "Enter Medicine Name: ";
            cin.ignore();
            getline(cin, name);
        
            // check if medicine already exists before anything else
            if (pharmacy.medicineAlreadyExists(name)) {
                cout << name << " already exists in inventory. Use Restock Medicine to update stock." << endl;
            }
            else {
                cout << "Enter Dosage (e.g. 500mg or 10ml): ";
                getline(cin, dosage);
                cout << "Enter Stock Quantity: ";
                cin >> stock;
                cout << "Enter Price: ";
                cin >> price;
        
                Medicine m;
                if (!m.isValidName(name)) {
                    cout << "Invalid Medicine Name." << endl;
                }
                else if (!m.isValidDosage(dosage)) {
                    cout << "Invalid Dosage (format: number + mg or ml)." << endl;
                }
                else if (!m.isValidQuantity(stock)) {
                    cout << "Invalid Stock Quantity." << endl;
                }
                else if (!m.isValidPrice(price)) {
                    cout << "Invalid Price." << endl;
                }
                else {
                    m.setName(name);
                    m.setDosage(dosage);
                    m.setStock(stock);
                    m.setPrice(price);
                    pharmacy.AddMedicine(&m);
                    pharmacy.saveInventory();
                    cout << "Medicine added successfully." << endl;
                }
            }
        }
        
        else if (choice == 22) {
            string patientID, medName;
            int qty;
            //Pharmacy pharmacy;
        
            cout << "Enter Patient ID: ";
            cin >> patientID;
        
            Patient p;
            if (!p.isValidPatientId(patientID)) {
                cout << "Invalid Patient ID (Format: P-0001)" << endl;
            }
            else if (!p.patientIdAlreadyExists(patientID, "Patient.txt")) {
                cout << "Patient ID does not exist." << endl;
            }
            else {
                cin.ignore();
                cout << "Enter Medicine Name: ";
                getline(cin, medName);
                cout << "Enter Quantity: ";
                cin >> qty;
        
                if (qty <= 0) {
                    cout << "Invalid quantity." << endl;
                }
                else {
                    pharmacy.prescriptionIssue(patientID, medName, qty);
                }
            }
        }
        
        else if (choice == 23) {
            string patientID;
            cout << "Enter Patient ID: ";
            cin >> patientID;
            //Pharmacy pharmacy;
        
            Patient p;
            if (!p.isValidPatientId(patientID)) {
                cout << "Invalid Patient ID (Format: P-0001)" << endl;
            }
            else if (!p.patientIdAlreadyExists(patientID, "Patient.txt")) {
                cout << "Patient ID does not exist." << endl;
            }
            else {
                p.setPatientId(patientID);
                pharmacy.loadPrescriptions();
                pharmacy.searchPatient(p);
            }
        }
        else if (choice == 24) {
            //Pharmacy pharmacy;
            //pharmacy.loadInventory();
            pharmacy.displayLowStock();
        }
        
        else if (choice == 25) {
            //Pharmacy pharmacy;
            pharmacy.loadPrescriptions();
            pharmacy.displayAllPrescriptions();
        }
        
        else if (choice == 26) {
            string medName;
            int qty;
            //Pharmacy pharmacy;
        
            cout << "Enter Medicine Name: ";
            cin.ignore();
            getline(cin, medName);
            cout << "Enter Quantity to Add: ";
            cin >> qty;
        
            if (qty <= 0) {
                cout << "Invalid quantity." << endl;
            }
            else {
                //pharmacy.loadInventory();
                pharmacy.updateStock(medName, qty);
            }
        }
        else if (choice == 27) {
            Ambulance a;
            string aID = a.generateAmbulanceId();
            string driverID = a.generateDriverId();
            string plate, addr;
            bool avail;

            while (true) {
                cout << "Enter License Plate (format ABC-123): ";
                cin >> plate;
                for (char& c : plate) 
                    c = toupper(c);
                if (!a.isValidLicensePlate(plate))
                    cout << "Invalid License Plate.\n";
                else if (a.licensePlateAlreadyExists(plate, "Ambulance.txt"))
                    cout << "License plate already exists. Try another.\n";
                else break;
            }

            int availChoice;
            cout << "Is Ambulance Available? (1 = Yes, 0 = No): ";
            cin >> availChoice;
            avail = (availChoice == 1);

            if (availChoice == 0) {
                cout << "Enter Destination Address: ";
                cin.ignore();
                getline(cin, addr);
            }
            else {
                addr = "None";
            }

            a.setAmbulanceId(aID);
            a.setDriverId(driverID);
            a.setLicensePlate(plate);
            a.setAddress(addr);
            a.setAvailability(avail);

            a.saveToFile("Ambulance.txt");
            cout << "Ambulance registered successfully!\n";
        }
        
        else if (choice==28){
            Ambulance a;
            a.displayAllAmbulances("Ambulance.txt");
        }

        else if(choice==29){
            string targetId;
            cout<<"Enter Ambulance ID to update format(A-0001): ";
            cin>>targetId;
            Ambulance a;
            if (!a.ambulanceIdAlreadyExists(targetId, "Ambulance.txt")) {
                cout << "Ambulance ID not found!\n";
            }
            else{
                int field;
                cout << "\nWhat would you like to update?\n";
                cout << "1. Destination Address\n";
                cout << "2. Availability\n";
                cout << "0. Cancel\n";
                cout << "Enter choice: ";
                cin >> field;
                string new_driver="",new_plate="",new_addr="";
                bool new_avail=false;

                if (field == 1) {
                    cin.ignore();
                    cout << "Enter new Address: ";
                    getline(cin, new_addr);
                }
                else if (field == 2) {
                    bool currentAvail = false;
                    ifstream checkFile("Ambulance.txt");
                    string ln;
                    while (getline(checkFile, ln)) {
                        if (ln != "----------")
                            continue;
                        Ambulance temp;
                        temp.loadFromFile(checkFile);
                        if (temp.getAmbulanceId() == targetId) {
                        currentAvail = temp.getAvailability();
                        break;
                        }
                    }
                    checkFile.close();

                    int availChoice;
                    cout << "Is Ambulance Available? (1 = Yes, 0 = No): ";
                    cin >> availChoice;

                    if (currentAvail == false && availChoice == 1) {
                        new_addr = "None";
                    }
                    else if (currentAvail == true && availChoice == 0) {
                        cin.ignore();
                        cout << "Enter new Destination Address: ";
                        getline(cin, new_addr);
                    }

                    new_avail = (availChoice == 1);
                }
                else {
                    cout << "Cancelled.\n";
                }

                ifstream fin("Ambulance.txt");
                ofstream fout("Ambulance_temp.txt");
                string ln;
                
                while (getline(fin, ln)) {
                    if (ln != "----------") continue;
                    fout << "----------\n";
                    
                    string aid, avail, did, plate, addr;
                    getline(fin, aid);
                    getline(fin, avail);
                    getline(fin, did);
                    getline(fin, plate);
                    getline(fin, addr);
                    
                    if (aid == targetId) {
                        fout << aid << "\n";
                        fout << (field == 1 || field == 2 ? to_string(new_avail) : avail) << "\n";
                        fout << did   << "\n";    
                        fout << plate << "\n"; 
                        fout << (field == 1 || field == 2 ? new_addr : addr) << "\n";
                    }
                    else {
                        fout << aid   << "\n";
                        fout << avail << "\n";
                        fout << did   << "\n";
                        fout << plate << "\n";
                        fout << addr  << "\n";
                    }
                }
                
                fin.close();
                fout.close();
                if (remove("Ambulance.txt") != 0) {
                    cout << "Error deleting file!\n";
                }
                if (rename("Ambulance_temp.txt", "Ambulance.txt") != 0) {
                    cout << "Error renaming file!\n";
                }
                //remove("Ambulance.txt");
                //rename("Ambulance_temp.txt", "Ambulance.txt");
                
                cout << "Ambulance updated successfully!\n";
            }
        }













        
















    } while (choice != 30);
    char c;
    cout << "\nDo you want to logout? (y/n): ";
    cin >> c;

    if (c == 'n' || c == 'N') {
        adminMenu(); // go back to menu
    }
}














































void SystemController::patientMenu(string username) {

    Pharmacy pharmacy;
    pharmacy.loadInventory();
    pharmacy.loadPrescriptions();

    string loggedCNIC = "";

    {
        ifstream userFile("Users.txt");
        string ln;

        while (getline(userFile, ln)) {
            if (ln == "----------") {
                string cnic, uname, pass, role;
                getline(userFile, cnic);
                getline(userFile, uname);
                getline(userFile, pass);
                getline(userFile, role);

                if (uname == username) {
                    loggedCNIC = cnic;
                    break;
                }
            }
        }
        userFile.close();
    }

    if (loggedCNIC == "") {
        cout << "User CNIC not found. Login data corrupted.\n";
        return;
    }

    int choice;

    do {
        cout << "\n========== PATIENT MENU ==========\n";
        cout << "1. View Personal Information\n";
        cout << "2. View Medical Records\n";
        cout << "3. Book New Appointment\n";
        cout << "4. Cancel Appointment\n";
        cout << "5. View Bill\n";
        cout << "6. Update Username/Password\n";
        cout << "7. Show Patient Pharmacy Records\n";
        cout << "8. Request Ambulance\n";
        cout << "9. Logout\n";
        cout << "================================\n";
        cout << "Enter choice: ";
        cin >> choice;

        // ==========================================
        // 1. VIEW PERSONAL INFORMATION
        // ==========================================
        if (choice == 1) {
            {
                ifstream fin("Person.txt");
                string ln;

                while (getline(fin, ln)) {
                    if (ln != "----------") continue;

                    string cnic, name, age, gender, phone, email, address;
                    getline(fin, cnic);
                    getline(fin, name);
                    getline(fin, age);
                    getline(fin, gender);
                    getline(fin, phone);
                    getline(fin, email);
                    getline(fin, address);

                    if (cnic == loggedCNIC) {
                        cout << "\n--- Personal Info ---\n";
                        cout << "CNIC    : " << cnic    << "\n";
                        cout << "Name    : " << name    << "\n";
                        cout << "Age     : " << age     << "\n";
                        cout << "Gender  : " << gender  << "\n";
                        cout << "Phone   : " << phone   << "\n";
                        cout << "Email   : " << email   << "\n";
                        cout << "Address : " << address << "\n";
                    }
                }
                fin.close();
            }
            {
                ifstream fin2("Patient.txt");
                string ln2;

                while (getline(fin2, ln2)) {
                    if (ln2 != "----------") continue;

                    string cnic, patientId, bloodGroup, patientType, height, weight, contact, status;
                    getline(fin2, cnic);
                    getline(fin2, patientId);
                    getline(fin2, bloodGroup);
                    getline(fin2, patientType);
                    getline(fin2, height);
                    getline(fin2, weight);
                    getline(fin2, contact);
                    getline(fin2, status);

                    if (cnic == loggedCNIC) {
                        cout << "\n--- Patient Info ---\n";
                        cout << "Patient ID  : " << patientId   << "\n";
                        cout << "Blood Group : " << bloodGroup  << "\n";
                        cout << "Type        : " << patientType << "\n";
                        cout << "Height      : " << height      << "\n";
                        cout << "Weight      : " << weight      << "\n";
                        cout << "Contact     : " << contact     << "\n";
                        cout << "Status      : " << status      << "\n";
                    }
                }
                fin2.close();
            }
        }

        // ==========================================
        // 2. VIEW MEDICAL RECORDS
        // ==========================================
        else if (choice == 2) {
            {
                string patient_id = "";

                {
                    ifstream pfile("Patient.txt");
                    string ln;

                    while (getline(pfile, ln)) {
                        if (ln != "----------") continue;

                        string cnic, pid, blood, type, height, weight, contact, status;
                        getline(pfile, cnic);
                        getline(pfile, pid);
                        getline(pfile, blood);
                        getline(pfile, type);
                        getline(pfile, height);
                        getline(pfile, weight);
                        getline(pfile, contact);
                        getline(pfile, status);

                        if (cnic == loggedCNIC) {
                            patient_id = pid;
                            break;
                        }
                    }
                    pfile.close();
                }

                if (patient_id == "") {
                    cout << "No patient record found for your account.\n";
                }
                else {
                    ifstream infile("MedicalRecords.txt");
                    if (!infile) {
                        cout << "No medical records found.\n";
                    }
                    else {
                        string ln;
                        bool found = false;
                        int visitNum = 1;

                        cout << "\n========== Your Medical History ==========\n";

                        while (getline(infile, ln)) {
                            if (ln != "----------") continue;

                            string recId, patId, docId, diagnosis, treatment, cost, recDate;
                            getline(infile, recId);
                            getline(infile, patId);
                            getline(infile, docId);
                            getline(infile, diagnosis);
                            getline(infile, treatment);
                            getline(infile, cost);
                            getline(infile, recDate);

                            if (patId == patient_id) {
                                found = true;
                                cout << "\n--- Visit " << visitNum++ << " ---\n";
                                cout << "Record ID  : " << recId     << "\n";
                                cout << "Doctor ID  : " << docId     << "\n";
                                cout << "Diagnosis  : " << diagnosis << "\n";
                                cout << "Treatment  : " << treatment << "\n";
                                cout << "Cost       : " << cost      << "\n";
                                cout << "Date       : " << recDate   << "\n";
                            }
                        }
                        infile.close();

                        if (!found)
                            cout << "No medical records found.\n";
                        else
                            cout << "\n=========================================\n";
                    }
                }
            }
        }

        // ==========================================
        // 3. BOOK NEW APPOINTMENT
        // ==========================================
        else if (choice == 3) {
            {
                string patient_id = "";

                {
                    ifstream pfile("Patient.txt");
                    string ln;

                    while (getline(pfile, ln)) {
                        if (ln != "----------") continue;

                        string cnic, pid, blood, type, height, weight, contact, status;
                        getline(pfile, cnic);
                        getline(pfile, pid);
                        getline(pfile, blood);
                        getline(pfile, type);
                        getline(pfile, height);
                        getline(pfile, weight);
                        getline(pfile, contact);
                        getline(pfile, status);

                        if (cnic == loggedCNIC) {
                            patient_id = pid;
                            break;
                        }
                    }
                    pfile.close();
                }

                if (patient_id == "") {
                    cout << "No patient record found for your account.\n";
                }
                else {

                    // STEP 2: Validate Doctor ID
                    string doctor_id;
                    Doctor d;
                    bool valid_doc=false;

                    while (true) {
                        cout << "Enter Doctor ID (format D-0001): ";
                        cin >> doctor_id;

                        if (!d.isValidDoctorId(doctor_id))
                            cout << "Invalid format. Must be D-XXXX.\n";
                        else if (!d.doctorIdAlreadyExists(doctor_id, "Doctor.txt")){
                            cout << "Doctor does not exist.\n";
                            break;
                        }
                        else
                        valid_doc=true;
                            break;
                    }
                    if(!valid_doc){
                        continue;
                    }

                    // STEP 3: Enter Date
                    string apptDate;
                    Appointment a;
                    cin.ignore();
                    while (true) {
                        cout << "Enter Date (DD/MM/YYYY): ";
                        getline(cin, apptDate);
                        if (!apptDate.empty()) break;
                        cout << "Date cannot be empty.\n";
                        if(!a.dateIsNotAPastDate(apptDate)) break ;
                        cout<<"Appointment cant be booked on a past day\n";
                    }

                    // STEP 4: Read Doctor Availability & Status
                    string availability = "";
                    string docStatus    = "";

                    {
                        ifstream dfile("Doctor.txt");
                        string ln;

                        while (getline(dfile, ln)) {
                            if (ln != "----------") continue;

                            string cnic, did, spec, qual, exp, fee, avail, stat;
                            getline(dfile, cnic);
                            getline(dfile, did);
                            getline(dfile, spec);
                            getline(dfile, qual);
                            getline(dfile, exp);
                            getline(dfile, fee);
                            getline(dfile, avail);
                            getline(dfile, stat);

                            if (did == doctor_id) {
                                availability = avail;
                                docStatus    = stat;
                                break;
                            }
                        }
                        dfile.close();
                    }

                    // normalize docStatus to lowercase
                    for (char& c : docStatus) c = tolower(c);

                    if (docStatus != "available") {
                        cout << "Doctor is currently not available (Status: " << docStatus << ").\n";
                    }
                    else {

                        // STEP 5: Parse Time Range
                        int spacePos     = availability.find(" ");
                        string dayPart   = availability.substr(0, spacePos);
                        string rangePart = availability.substr(spacePos + 1);
                        int dashPos      = rangePart.find("-");
                        string startStr  = rangePart.substr(0, dashPos);
                        string endStr    = rangePart.substr(dashPos + 1);

                        // STEP 5.5: Verify date falls on doctor's available day
                        bool dayMatches  = false;
                        string enteredDay = "";

                        {
                            int dd, mm, yyyy;
                            sscanf(apptDate.c_str(), "%d/%d/%d", &dd, &mm, &yyyy);

                            int m = mm, y = yyyy;
                            if (m < 3) { m += 12; y--; }
                            int k = y % 100;
                            int j = y / 100;
                            int h = (dd + (13 * (m + 1)) / 5 + k + k / 4 + j / 4 + 5 * j) % 7;

                            // 0=Sat, 1=Sun, 2=Mon, 3=Tue, 4=Wed, 5=Thu, 6=Fri
                            string days[] = {"Saturday", "Sunday", "Monday", "Tuesday",
                                             "Wednesday", "Thursday", "Friday","Mon","Tue","Wed","Thurs","Fri","Sat","Sun"};
                            enteredDay = days[h];

                            string enteredDayLower = enteredDay;
                            string availDayLower   = dayPart;
                            for (char& c : enteredDayLower) c = tolower(c);
                            for (char& c : availDayLower)   c = tolower(c);

                            dayMatches = (enteredDayLower == availDayLower);
                        }

                        if (!dayMatches) {
                            cout << "Doctor is only available on " << dayPart << "s. "
                                 << apptDate << " is a " << enteredDay << ".\n";
                        }
                        else {

                            auto convertTo24 = [](string t) -> int {
                                string numStr = "";
                                for (char c : t) {
                                    if (isdigit(c)) numStr += c;
                                    else break;
                                }
                                int hour = stoi(numStr);
                                if (t.find("PM") != string::npos && hour != 12) hour += 12;
                                if (t.find("AM") != string::npos && hour == 12) hour = 0;
                                return hour;
                            };

                            int startHour = convertTo24(startStr);
                            int endHour   = convertTo24(endStr);

                            // STEP 6: Load Booked Slots
                            string booked[100];
                            int bookedCount = 0;

                            {
                                ifstream apFile("Appointment.txt");
                                string ln;

                                while (getline(apFile, ln)) {
                                    if (ln != "----------") continue;

                                    string apptId, pid, did, aDate, aTime, reason, stat;
                                    getline(apFile, apptId);
                                    getline(apFile, pid);
                                    getline(apFile, did);
                                    getline(apFile, aDate);
                                    getline(apFile, aTime);
                                    getline(apFile, reason);
                                    getline(apFile, stat);

                                    for (char& c : stat) c = tolower(c);

                                    if (did == doctor_id && aDate == apptDate && stat == "scheduled") {
                                        booked[bookedCount++] = aTime;
                                    }
                                }
                                apFile.close();
                            }

                            // STEP 7: Show Available Slots
                            string slots[50];
                            int availCount = 0;

                            cout << "\nAvailable Slots on " << apptDate << " (" << enteredDay
                                 << ") for Doctor " << doctor_id
                                 << " (" << startStr << "-" << endStr << "):\n";
                            cout << "--------------------------------------------\n";

                            for (int h = startHour; h < endHour; h++) {
                                string slot = to_string(h) + ":00";
                                bool taken  = false;

                                for (int i = 0; i < bookedCount; i++) {
                                    if (booked[i] == slot) { taken = true; break; }
                                }

                                if (!taken) {
                                    cout << availCount + 1 << ". " << slot << "\n";
                                    slots[availCount++] = slot;
                                }
                            }
                            cout << "--------------------------------------------\n";

                            if (availCount == 0) {
                                cout << "No available slots for this doctor on " << apptDate << ".\n";
                            }
                            else {

                                // STEP 8: Select Slot
                                int slotChoice;
                                while (true) {
                                    cout << "Select a slot (1-" << availCount << "): ";
                                    cin >> slotChoice;
                                    if (slotChoice >= 1 && slotChoice <= availCount) break;
                                    cout << "Invalid selection. Try again.\n";
                                }

                                string selectedTime = slots[slotChoice - 1];

                                // STEP 9: Enter Reason
                                string reason;
                                cin.ignore();
                                cout << "Enter Reason for Visit: ";
                                getline(cin, reason);
                                if (reason.empty()) reason = "General Checkup";

                                // STEP 10: Generate Appointment ID
                                int apptCount = 0;
                                {
                                    ifstream countFile("Appointment.txt");
                                    string cln;
                                    while (getline(countFile, cln)) {
                                        if (cln == "----------") apptCount++;
                                    }
                                    countFile.close();
                                }

                                int nextNum   = apptCount + 1;
                                string numStr = to_string(nextNum);
                                string apptId = "A-" + string(4 - numStr.length(), '0') + numStr;

                                // STEP 11: Save to Appointment.txt
                                ofstream outFile("Appointment.txt", ios::app);
                                outFile << "----------\n";
                                outFile << apptId       << "\n";
                                outFile << patient_id   << "\n";
                                outFile << doctor_id    << "\n";
                                outFile << apptDate     << "\n";
                                outFile << selectedTime << "\n";
                                outFile << reason       << "\n";
                                outFile << "Scheduled"  << "\n";
                                outFile.close();

                                cout << "\n============================================\n";
                                cout << " Appointment Booked Successfully!\n";
                                cout << " Appointment ID : " << apptId       << "\n";
                                cout << " Doctor         : " << doctor_id    << "\n";
                                cout << " Date           : " << apptDate     << "\n";
                                cout << " Day            : " << enteredDay   << "\n";
                                cout << " Time           : " << selectedTime << "\n";
                                cout << " Reason         : " << reason       << "\n";
                                cout << " Status         : Scheduled\n";
                                cout << "============================================\n";
                            }
                        }
                    }
                }
            }
        }

        // ==========================================
        // 4. CANCEL APPOINTMENT
        // ==========================================
        else if (choice == 4) {
            {
                string patient_id = "";

                {
                    ifstream pfile("Patient.txt");
                    string ln;

                    while (getline(pfile, ln)) {
                        if (ln != "----------") continue;

                        string cnic, pid, blood, type, height, weight, contact, status;
                        getline(pfile, cnic);
                        getline(pfile, pid);
                        getline(pfile, blood);
                        getline(pfile, type);
                        getline(pfile, height);
                        getline(pfile, weight);
                        getline(pfile, contact);
                        getline(pfile, status);

                        if (cnic == loggedCNIC) {
                            patient_id = pid;
                            break;
                        }
                    }
                    pfile.close();
                }

                if (patient_id == "") {
                    cout << "No patient record found for your account.\n";
                }
                else {

                    cout << "\n========== Your Scheduled Appointments ==========\n";

                    string apptIds[50];
                    int apptCount = 0;

                    {
                        ifstream apFile("Appointment.txt");
                        string ln;

                        while (getline(apFile, ln)) {
                            if (ln != "----------") continue;

                            string apptId, pid, did, aDate, aTime, reason, stat;
                            getline(apFile, apptId);
                            getline(apFile, pid);
                            getline(apFile, did);
                            getline(apFile, aDate);
                            getline(apFile, aTime);
                            getline(apFile, reason);
                            getline(apFile, stat);

                            for (char& c : stat) c = tolower(c);

                            if (pid == patient_id && stat == "scheduled") {
                                cout << apptCount + 1 << ". "
                                     << "ID: "     << apptId << " | "
                                     << "Doctor: " << did    << " | "
                                     << "Date: "   << aDate  << " | "
                                     << "Time: "   << aTime  << " | "
                                     << "Reason: " << reason << "\n";
                                apptIds[apptCount++] = apptId;
                            }
                        }
                        apFile.close();
                    }

                    if (apptCount == 0) {
                        cout << "No scheduled appointments found.\n";
                    }
                    else {
                        cout << "-------------------------------------------------\n";

                        int cancelChoice;
                        while (true) {
                            cout << "Select appointment to cancel (1-" << apptCount << "): ";
                            cin >> cancelChoice;
                            if (cancelChoice >= 1 && cancelChoice <= apptCount) break;
                            cout << "Invalid selection. Try again.\n";
                        }

                        string targetId = apptIds[cancelChoice - 1];

                        ifstream fin("Appointment.txt");
                        ofstream fout("Appointment_temp.txt");
                        string ln;

                        while (getline(fin, ln)) {
                            if (ln != "----------") continue;

                            string apptId, pid, did, aDate, aTime, reason, stat;
                            getline(fin, apptId);
                            getline(fin, pid);
                            getline(fin, did);
                            getline(fin, aDate);
                            getline(fin, aTime);
                            getline(fin, reason);
                            getline(fin, stat);

                            fout << "----------\n";
                            fout << apptId << "\n";
                            fout << pid    << "\n";
                            fout << did    << "\n";
                            fout << aDate  << "\n";
                            fout << aTime  << "\n";
                            fout << reason << "\n";

                            if (apptId == targetId)
                                fout << "Cancelled\n";
                            else
                                fout << stat << "\n";
                        }

                        fin.close();
                        fout.close();

                        remove("Appointment.txt");
                        rename("Appointment_temp.txt", "Appointment.txt");

                        cout << "\nAppointment " << targetId << " cancelled successfully.\n";
                    }
                }
            }
        }
        else if(choice==5){
            Patient p;
            string pid;
            pid=p.ID_from_CNIC(loggedCNIC);
            Billing b;
            b.displayHeader();
            bool found=b.searchByPatientId(pid);
            if(!found){
                cout<<"No bills found for your account"<<endl;
            }
        }

        // ==========================================
        // 5. UPDATE USERNAME/PASSWORD
        // ==========================================
        else if (choice == 6) {
            {
                int updateChoice;
                cout << "What do you want to update:\n";
                cout << "1. Username\n";
                cout << "2. Password\n";
                cout << "Enter Choice: ";
                cin >> updateChoice;

                string current_cnic;
                cout << "Enter CNIC: ";
                cin >> current_cnic;

                string new_username = "";
                string new_password = "";
                bool found = false;

                ifstream fin("Users.txt");
                ofstream fout("Users_temp.txt");
                string ln;

                while (getline(fin, ln)) {
                    if (ln != "----------") continue;

                    string cnic, uname, password, role;
                    getline(fin, cnic);
                    getline(fin, uname);
                    getline(fin, password);
                    getline(fin, role);

                    if (cnic == current_cnic) {
                        found = true;
                        cout << "User found.\n";

                        if (updateChoice == 1) {
                            cout << "Enter New Username: ";
                            cin >> new_username;
                            uname = new_username;
                        }
                        else if (updateChoice == 2) {
                            cout << "Enter New Password: ";
                            cin >> new_password;
                            password = new_password;
                        }
                        else {
                            cout << "Invalid choice.\n";
                        }
                    }

                    fout << "----------\n";
                    fout << cnic     << "\n";
                    fout << uname    << "\n";
                    fout << password << "\n";
                    fout << role     << "\n";
                }

                fin.close();
                fout.close();

                remove("Users.txt");
                rename("Users_temp.txt", "Users.txt");

                if (found)
                    cout << "Record updated successfully!\n";
                else
                    cout << "CNIC not found!\n";
            }
        }
        else if (choice == 7) {
            Patient p;
            string pid;
            pid=p.ID_from_CNIC(loggedCNIC);
            p.setPatientId(pid);
            //Pharmacy pharmacy;
            pharmacy.loadPrescriptions();
            pharmacy.searchPatient(p);
            
        }
        else if(choice==8){
                Ambulance a;
                ifstream infile("Ambulance.txt");
                if (!infile.is_open()) {
                    cout << "No ambulance records found.\n";
                }
                else{
                    string line;
                    string availIds[50];
                    int availCount=0;
                    while(getline(infile,line)){
                        if(line!="----------")
                        continue;
                        Ambulance temp;
                        temp.loadFromFile(infile);
                        if (temp.getAvailability()) {
                            availIds[availCount++] = temp.getAmbulanceId();
                        }
                    }
                    infile.close();
                    if(availCount==0){
                        cout<<"No ambulances currently available!\n";
                    }
                    else{
                        cout << "\n========== Available Ambulances ==========\n";
                        for(int i=0;i<availCount;i++){
                            cout<<i+1<<". "<<availIds[i]<<"\n";
                        }
                        int choice;
                        while(true){
                            cout << "Select ambulance (1-" << availCount << "): ";
                            cin >> choice;
                            if (choice >= 1 && choice <= availCount) break;
                            cout << "Invalid selection.\n";
                            
                        }
                        string selectedId = availIds[choice - 1];
                        string destination;
                        cin.ignore();
                        cout << "Enter your destination address: ";
                        getline(cin, destination);
                        ifstream fin("Ambulance.txt");
                        ofstream fout("Ambulance_temp.txt");
                        string ln;
                        while (getline(fin, ln)) {
                            if (ln != "----------") continue;
                            fout << "----------\n";
                            
                            string aid, avail, did, plate, addr;
                            getline(fin, aid);
                            getline(fin, avail);
                            getline(fin, did);
                            getline(fin, plate);
                            getline(fin, addr);
                            
                            fout << aid << "\n";
                            if (aid == selectedId) {
                                fout << "0\n";  
                                fout << did << "\n";
                                fout << plate << "\n";
                                fout << destination << "\n";  
                            }
                            else {
                                fout << avail << "\n";
                                fout << did   << "\n";
                                fout << plate << "\n";
                                fout << addr  << "\n";
                            }
                        }
                        fin.close();
                        fout.close();
                        remove("Ambulance.txt");
                        rename("Ambulance_temp.txt", "Ambulance.txt");
                        
                        cout << "\n========== Ambulance Requested ==========\n";
                        cout << "Ambulance ID : " << selectedId << "\n";
                        cout << "Status       : On its way!\n";
                        cout << "=========================================\n";
                    }
                }
            }

    } while (choice != 9);
}

void SystemController::doctorMenu(string username) {

    string loggedCNIC = "";

    {
        ifstream userFile("Users.txt");
        string ln;

        while (getline(userFile, ln)) {
            if (ln == "----------") {
                string cnic, uname, pass, role;
                getline(userFile, cnic);
                getline(userFile, uname);
                getline(userFile, pass);
                getline(userFile, role);

                if (uname == username) {
                    loggedCNIC = cnic;
                    break;
                }
            }
        }
        userFile.close();
    }

    if (loggedCNIC == "") {
        cout << "User CNIC not found. Login data corrupted.\n";
        return;
    }

    // Get Doctor ID from CNIC once at login
    string doctor_id = "";
    {
        ifstream dfile("Doctor.txt");
        string ln;

        while (getline(dfile, ln)) {
            if (ln != "----------") continue;

            string cnic, did, spec, qual, exp, fee, avail, stat;
            getline(dfile, cnic);
            getline(dfile, did);
            getline(dfile, spec);
            getline(dfile, qual);
            getline(dfile, exp);
            getline(dfile, fee);
            getline(dfile, avail);
            getline(dfile, stat);

            if (cnic == loggedCNIC) {
                doctor_id = did;
                break;
            }
        }
        dfile.close();
    }

    if (doctor_id == "") {
        cout << "Doctor record not found. Data corrupted.\n";
        return;
    }

    int choice;

    do {
        cout << "\n========== DOCTOR MENU ==========\n";
        cout << "1. View Personal Information\n";
        cout << "2. View Patient Medical Records\n";
        cout << "3. Add New Medical Record\n";
        cout << "4. Show All Appointments\n";
        cout << "5. Cancel Appointment\n";
        cout << "6. Update Username/Password\n";
        cout << "7. Logout\n";
        cout << "================================\n";
        cout << "Enter choice: ";
        cin >> choice;

        // ==========================================
        // 1. VIEW PERSONAL INFORMATION
        // ==========================================
        if (choice == 1) {
            {
                ifstream fin("Person.txt");
                string ln;

                while (getline(fin, ln)) {
                    if (ln != "----------") continue;

                    string cnic, name, age, gender, phone, email, address;
                    getline(fin, cnic);
                    getline(fin, name);
                    getline(fin, age);
                    getline(fin, gender);
                    getline(fin, phone);
                    getline(fin, email);
                    getline(fin, address);

                    if (cnic == loggedCNIC) {
                        cout << "\n--- Personal Info ---\n";
                        cout << "CNIC    : " << cnic    << "\n";
                        cout << "Name    : " << name    << "\n";
                        cout << "Age     : " << age     << "\n";
                        cout << "Gender  : " << gender  << "\n";
                        cout << "Phone   : " << phone   << "\n";
                        cout << "Email   : " << email   << "\n";
                        cout << "Address : " << address << "\n";
                    }
                }
                fin.close();
            }
            {
                ifstream dfile("Doctor.txt");
                string ln;

                while (getline(dfile, ln)) {
                    if (ln != "----------") continue;

                    string cnic, did, spec, qual, exp, fee, avail, stat;
                    getline(dfile, cnic);
                    getline(dfile, did);
                    getline(dfile, spec);
                    getline(dfile, qual);
                    getline(dfile, exp);
                    getline(dfile, fee);
                    getline(dfile, avail);
                    getline(dfile, stat);

                    if (cnic == loggedCNIC) {
                        cout << "\n--- Doctor Info ---\n";
                        cout << "Doctor ID      : " << did   << "\n";
                        cout << "Specialization : " << spec  << "\n";
                        cout << "Qualification  : " << qual  << "\n";
                        cout << "Experience     : " << exp   << " years\n";
                        cout << "Fee            : " << fee   << "\n";
                        cout << "Availability   : " << avail << "\n";
                        cout << "Status         : " << stat  << "\n";
                    }
                }
                dfile.close();
            }
        }

        // ==========================================
        // 2. VIEW PATIENT MEDICAL RECORDS
        // ==========================================
        else if (choice == 2) {
            {
                string target_pid;
                cout << "Enter Patient ID (format P-0001): ";
                cin >> target_pid;

                ifstream infile("MedicalRecords.txt");
                if (!infile) {
                    cout << "No medical records found.\n";
                }
                else {
                    string ln;
                    bool found = false;
                    int visitNum = 1;

                    cout << "\n========== Medical History for " << target_pid << " ==========\n";

                    while (getline(infile, ln)) {
                        if (ln != "----------") continue;

                        string recId, patId, docId, diagnosis, treatment, cost, recDate;
                        getline(infile, recId);
                        getline(infile, patId);
                        getline(infile, docId);
                        getline(infile, diagnosis);
                        getline(infile, treatment);
                        getline(infile, cost);
                        getline(infile, recDate);

                        if (patId == target_pid) {
                            found = true;
                            cout << "\n--- Visit " << visitNum++ << " ---\n";
                            cout << "Record ID  : " << recId     << "\n";
                            cout << "Doctor ID  : " << docId     << "\n";
                            cout << "Diagnosis  : " << diagnosis << "\n";
                            cout << "Treatment  : " << treatment << "\n";
                            cout << "Cost       : " << cost      << "\n";
                            cout << "Date       : " << recDate   << "\n";
                        }
                    }
                    infile.close();

                    if (!found)
                        cout << "No records found for Patient ID: " << target_pid << "\n";
                    else
                        cout << "\n=====================================================\n";
                }
            }
        }

        // ==========================================
        // 3. ADD NEW MEDICAL RECORD
        // ==========================================
        else if (choice == 3) {
            {
                // Get Patient ID
                string target_pid;
                cout << "Enter Patient ID (format P-0001): ";
                cin >> target_pid;

                // Check patient exists
                bool patientExists = false;
                {
                    ifstream pfile("Patient.txt");
                    string ln;

                    while (getline(pfile, ln)) {
                        if (ln != "----------") continue;

                        string cnic, pid, blood, type, height, weight, contact, status;
                        getline(pfile, cnic);
                        getline(pfile, pid);
                        getline(pfile, blood);
                        getline(pfile, type);
                        getline(pfile, height);
                        getline(pfile, weight);
                        getline(pfile, contact);
                        getline(pfile, status);

                        if (pid == target_pid) {
                            patientExists = true;
                            break;
                        }
                    }
                    pfile.close();
                }

                if (!patientExists) {
                    cout << "Patient ID not found.\n";
                }
                else {

                    // Generate Record ID
                    int recCount = 0;
                    {
                        ifstream countFile("MedicalRecords.txt");
                        string cln;
                        while (getline(countFile, cln)) {
                            if (cln == "----------") recCount++;
                        }
                        countFile.close();
                    }

                    int nextNum   = recCount + 1;
                    string numStr = to_string(nextNum);
                    string recId  = "R-" + string(4 - numStr.length(), '0') + numStr;

                    // Get record details
                    string diagnosis, treatment, cost, recDate;

                    cin.ignore();
                    cout << "Enter Diagnosis: ";
                    getline(cin, diagnosis);

                    cout << "Enter Treatment: ";
                    getline(cin, treatment);

                    cout << "Enter Cost: ";
                    getline(cin, cost);

                    cout << "Enter Date (DD/MM/YYYY): ";
                    getline(cin, recDate);

                    // Save to MedicalRecords.txt
                    ofstream outFile("MedicalRecords.txt", ios::app);
                    outFile << "----------\n";
                    outFile << recId      << "\n";
                    outFile << target_pid << "\n";
                    outFile << doctor_id  << "\n";
                    outFile << diagnosis  << "\n";
                    outFile << treatment  << "\n";
                    outFile << cost       << "\n";
                    outFile << recDate    << "\n";
                    outFile.close();

                    cout << "\n============================================\n";
                    cout << " Medical Record Added Successfully!\n";
                    cout << " Record ID  : " << recId      << "\n";
                    cout << " Patient ID : " << target_pid << "\n";
                    cout << " Doctor ID  : " << doctor_id  << "\n";
                    cout << " Diagnosis  : " << diagnosis  << "\n";
                    cout << " Treatment  : " << treatment  << "\n";
                    cout << " Cost       : " << cost       << "\n";
                    cout << " Date       : " << recDate    << "\n";
                    cout << "============================================\n";
                }
            }
        }

        // ==========================================
        // 4. SHOW ALL APPOINTMENTS
        // ==========================================
        else if (choice == 4) {
            {
                ifstream apFile("Appointment.txt");
                if (!apFile) {
                    cout << "No appointments found.\n";
                }
                else {
                    string ln;
                    bool found = false;
                    int count  = 0;

                    cout << "\n========== Your Appointments ==========\n";

                    while (getline(apFile, ln)) {
                        if (ln != "----------") continue;

                        string apptId, pid, did, aDate, aTime, reason, stat;
                        getline(apFile, apptId);
                        getline(apFile, pid);
                        getline(apFile, did);
                        getline(apFile, aDate);
                        getline(apFile, aTime);
                        getline(apFile, reason);
                        getline(apFile, stat);

                        if (did == doctor_id) {
                            found = true;
                            cout << "\n--- Appointment " << ++count << " ---\n";
                            cout << "Appointment ID : " << apptId << "\n";
                            cout << "Patient ID     : " << pid    << "\n";
                            cout << "Date           : " << aDate  << "\n";
                            cout << "Time           : " << aTime  << "\n";
                            cout << "Reason         : " << reason << "\n";
                            cout << "Status         : " << stat   << "\n";
                        }
                    }
                    apFile.close();

                    if (!found)
                        cout << "No appointments found.\n";
                    else
                        cout << "\n========================================\n";
                }
            }
        }

        // ==========================================
        // 5. CANCEL APPOINTMENT
        // ==========================================
        else if (choice == 5) {
            {
                // Show doctor's scheduled appointments
                cout << "\n========== Your Scheduled Appointments ==========\n";

                string apptIds[50];
                int apptCount = 0;

                {
                    ifstream apFile("Appointment.txt");
                    string ln;

                    while (getline(apFile, ln)) {
                        if (ln != "----------") continue;

                        string apptId, pid, did, aDate, aTime, reason, stat;
                        getline(apFile, apptId);
                        getline(apFile, pid);
                        getline(apFile, did);
                        getline(apFile, aDate);
                        getline(apFile, aTime);
                        getline(apFile, reason);
                        getline(apFile, stat);

                        for (char& c : stat) c = tolower(c);

                        if (did == doctor_id && stat == "scheduled") {
                            cout << apptCount + 1 << ". "
                                 << "ID: "      << apptId << " | "
                                 << "Patient: " << pid    << " | "
                                 << "Date: "    << aDate  << " | "
                                 << "Time: "    << aTime  << " | "
                                 << "Reason: "  << reason << "\n";
                            apptIds[apptCount++] = apptId;
                        }
                    }
                    apFile.close();
                }

                if (apptCount == 0) {
                    cout << "No scheduled appointments found.\n";
                }
                else {
                    cout << "-------------------------------------------------\n";

                    int cancelChoice;
                    while (true) {
                        cout << "Select appointment to cancel (1-" << apptCount << "): ";
                        cin >> cancelChoice;
                        if (cancelChoice >= 1 && cancelChoice <= apptCount) break;
                        cout << "Invalid selection. Try again.\n";
                    }

                    string targetId = apptIds[cancelChoice - 1];

                    ifstream fin("Appointment.txt");
                    ofstream fout("Appointment_temp.txt");
                    string ln;

                    while (getline(fin, ln)) {
                        if (ln != "----------") continue;

                        string apptId, pid, did, aDate, aTime, reason, stat;
                        getline(fin, apptId);
                        getline(fin, pid);
                        getline(fin, did);
                        getline(fin, aDate);
                        getline(fin, aTime);
                        getline(fin, reason);
                        getline(fin, stat);

                        fout << "----------\n";
                        fout << apptId << "\n";
                        fout << pid    << "\n";
                        fout << did    << "\n";
                        fout << aDate  << "\n";
                        fout << aTime  << "\n";
                        fout << reason << "\n";

                        if (apptId == targetId)
                            fout << "Cancelled\n";
                        else
                            fout << stat << "\n";
                    }

                    fin.close();
                    fout.close();

                    remove("Appointment.txt");
                    rename("Appointment_temp.txt", "Appointment.txt");

                    cout << "\nAppointment " << targetId << " cancelled successfully.\n";
                }
            }
        }

        // ==========================================
        // 6. UPDATE USERNAME/PASSWORD
        // ==========================================
        else if (choice == 6) {
            {
                int updateChoice;
                cout << "What do you want to update:\n";
                cout << "1. Username\n";
                cout << "2. Password\n";
                cout << "Enter Choice: ";
                cin >> updateChoice;

                string current_cnic;
                cout << "Enter CNIC: ";
                cin >> current_cnic;

                string new_username = "";
                string new_password = "";
                bool found = false;

                ifstream fin("Users.txt");
                ofstream fout("Users_temp.txt");
                string ln;

                while (getline(fin, ln)) {
                    if (ln != "----------") continue;

                    string cnic, uname, password, role;
                    getline(fin, cnic);
                    getline(fin, uname);
                    getline(fin, password);
                    getline(fin, role);

                    if (cnic == current_cnic) {
                        found = true;
                        cout << "User found.\n";

                        if (updateChoice == 1) {
                            cout << "Enter New Username: ";
                            cin >> new_username;
                            uname = new_username;
                        }
                        else if (updateChoice == 2) {
                            cout << "Enter New Password: ";
                            cin >> new_password;
                            password = new_password;
                        }
                        else {
                            cout << "Invalid choice.\n";
                        }
                    }

                    fout << "----------\n";
                    fout << cnic     << "\n";
                    fout << uname    << "\n";
                    fout << password << "\n";
                    fout << role     << "\n";
                }

                fin.close();
                fout.close();

                remove("Users.txt");
                rename("Users_temp.txt", "Users.txt");

                if (found)
                    cout << "Record updated successfully!\n";
                else
                    cout << "CNIC not found!\n";
            }
        }
        

    } while (choice != 7);
    char c;
    cout << "\nDo you want to logout? (y/n): ";
    cin >> c;

    if (c == 'n' || c == 'N') {
        doctorMenu(username); // go back to menu
    }
}