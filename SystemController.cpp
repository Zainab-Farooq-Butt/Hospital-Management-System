#include"Person.h"
#include"Patient.h"
#include"Login.h"
#include"Staff.h"
#include "Doctor.h"
#include "Appointment.h"
#include"SystemController.h"


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
        doctorMenu();
    }
    else if (currentRole == "PATIENT") {
        patientMenu();
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
        cout << "12. Register New User\n";
        cout << "13. Update Username/Password\n";
        cout << "14. Logout\n";
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
            Login::Save_Login_to_File(username, password, "PATIENT");

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

            while (true) {
                cout << "Enter Staff ID (format S-0001): ";
                cin >> id;
                if (!s.isValidStaffId(id))
                    cout << "Invalid format. Must be S-XXXX.\n";
                else if (s.staffIdAlreadyExists(id, "Staff.txt"))
                    cout << "ID already exists. Try another.\n";
                else break;
            }

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
                cout << "Enter Employment Status (Active / InActive): ";
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
            string id, spec, qual, avail, status;
            int exp;
            double fee;

            while (true) {
                cout << "Enter Doctor ID (format D-0001): ";
                cin >> id;
                if (!d.isValidDoctorId(id))
                    cout << "Invalid format. Must be D-XXXX.\n";
                else if (d.doctorIdAlreadyExists(id, "Doctor.txt"))
                    cout << "ID already exists. Try another.\n";
                else break;
            }

            while (true) {
                cout << "Enter Specialization: ";
                cin >> spec;
                if (d.isValidSpecialization(spec)) break;
                cout << "Invalid Specialization.\n";
            }

            while (true) {
                cout << "Enter Qualification: ";
                cin >> qual;
                if (d.isValidQualification(qual)) break;
                cout << "Invalid Qualification.\n";
            }

            while (true) {
                cout << "Enter Years of Experience: ";
                cin >> exp;
                if (d.isValidExperience(exp)) break;
                cout << "Invalid Experience.\n";
            }

            while (true) {
                cout << "Enter Consultation Fee: ";
                cin >> fee;
                if (d.isValidFee(fee)) break;
                cout << "Invalid Fee.\n";
            }

            cin.ignore();
            while (true) {
                cout << "Enter Availability (e.g. Mon-Fri 9AM-5PM): ";
                getline(cin, avail);
                if (!avail.empty()) break;
                cout << "Invalid Availability.\n";
            }

            while (true) {
                cout << "Enter Availability Status (Available/Unavailable/On Leave): ";
                cin >> status;
                if (d.isValidAvailabilityStatus(status)) break;
                cout << "Invalid Status.\n";
            }

            d.setLinkedCNIC(base.Get_CNIC());
            d.setDoctorId(id);
            d.setSpecialization(spec);
            d.setQualification(qual);
            d.setExperienceYears(exp);
            d.setConsultationFee(fee);
            d.setAvailability(avail);
            d.setAvailabilityStatus(status);

            ofstream docout("Doctor.txt", ios::app);
            d.Save_To_File(docout);
            docout.close();

            string username, password;
            cout << "Assign username: ";
            cin >> username;
            cout << "Assign password: ";
            cin >> password;
            Login::Save_Login_to_File(username, password, "DOCTOR");

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
                        while (true) {
                            cout << "Enter new Experience Years: ";
                            cin >> new_exp;
                            if (d.isValidExperience(new_exp)) break;
                            cout << "Invalid Experience.\n";
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

        // UPDATE USERNAME/PASSWORD
        else if (choice == 13) {
            string username = "", current_username = "", password = "", new_username = "", new_password = "", role = "";
            int updateChoice = 0;

            cout << "What do you want to update: " << endl;
            cout << "1. Username\n";
            cout << "2. Password\n";
            cout << "Enter Choice: ";
            cin >> updateChoice;

            cout << "Enter Current Username: ";
            cin >> current_username;

            bool user_exists = false;
            ifstream infile("Users.txt");
            string line;
            while (getline(infile, line)) {
                if (line == current_username) {
                    user_exists = true;
                    break;
                }
            }
            infile.close();

            if (user_exists == false) {
                cout << "Wrong Username Entered!\n";
            }
            else {
                if (updateChoice == 1) {
                    cout << "Enter New Username: ";
                    cin >> new_username;
                }
                else if (updateChoice == 2) {
                    cout << "Enter New Password: ";
                    cin >> new_password;
                }

                ifstream fin("Users.txt");
                ofstream fout("Users_temp.txt");
                string ln;

                while (getline(fin, ln)) {
                    if (ln == "----------") {
                        fout << ln << "\n";

                        getline(fin, username);
                        getline(fin, password);
                        getline(fin, role);

                        if (username == current_username) {
                            if (updateChoice == 1)
                                fout << new_username << "\n";
                            else
                                fout << username << "\n";

                            if (updateChoice == 2)
                                fout << new_password << "\n";
                            else
                                fout << password << "\n";

                            fout << role << "\n";
                        }
                        else {
                            fout << username << "\n";
                            fout << password << "\n";
                            fout << role     << "\n";
                        }
                    }
                }

                fin.close();
                fout.close();
                remove("Users.txt");
                rename("Users_temp.txt", "Users.txt");

                cout << "Record updated successfully!\n";
            }
        }

    } while (choice != 14);
}

void SystemController::doctorMenu() {
    cout << "Doctor menu coming soon.\n";
}

void SystemController::patientMenu() {
    cout << "Patient menu coming soon.\n";
}

