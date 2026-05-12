#include "PatientUpdateDialog.h"
#include "../../Patient.h"

#include <QFormLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QMessageBox>
#include <fstream>
#include <cstdio>

PatientUpdateDialog::PatientUpdateDialog(QWidget *parent) : QDialog(parent) {
    setWindowTitle("Update Patient");
<<<<<<< HEAD
    resize(420, 200);
=======
    resize(420, 250);
>>>>>>> origin/zainab

    txtCnic = new QLineEdit(this);
    cmbField = new QComboBox(this);
    cmbField->addItems({
        "Phone Number", "Email", "Address", "Age",
        "Emergency Contact", "Patient Status",
        "Weight", "Height", "Patient Type"
    });
    txtValue = new QLineEdit(this);

    auto *form = new QFormLayout();
<<<<<<< HEAD
    form->addRow("CNIC:",       txtCnic);
    form->addRow("Field:",      cmbField);
=======
    form->addRow("Current CNIC:", txtCnic);
    form->addRow("Field to Update:", cmbField);
>>>>>>> origin/zainab
    form->addRow("New Value:",  txtValue);

    auto *btnApply  = new QPushButton("Apply", this);
    auto *btnCancel = new QPushButton("Cancel", this);
    auto *btnRow = new QHBoxLayout();
    btnRow->addStretch();
    btnRow->addWidget(btnCancel);
    btnRow->addWidget(btnApply);

    auto *root = new QVBoxLayout(this);
    root->addLayout(form);
    root->addLayout(btnRow);

    connect(btnApply,  &QPushButton::clicked, this, &PatientUpdateDialog::onApply);
    connect(btnCancel, &QPushButton::clicked, this, &QDialog::reject);
}

void PatientUpdateDialog::onApply() {
    QString cnic = txtCnic->text().trimmed();
    int idx = cmbField->currentIndex();
    QString val = txtValue->text().trimmed();

    if (cnic.isEmpty() || val.isEmpty()) {
        QMessageBox::warning(this, "Missing", "Please enter both the CNIC and the new value.");
        return;
    }

<<<<<<< HEAD
    // First, validate if the CNIC actually exists in the patient records
    if (!Person::CNIC_Already_Exists(cnic.toStdString(), "Patient.txt")) {
        QMessageBox::critical(this, "Not Found", "No patient found with the provided CNIC.");
        return;
    }

    int field = idx + 1;
=======
    if (!Person::CNIC_Already_Exists(cnic.toStdString(), "Person.txt")) {
        QMessageBox::critical(this, "Not Found", "No person found with the provided CNIC.");
        return;
    }

    if (idx >= 6 && !Person::CNIC_Already_Exists(cnic.toStdString(), "Patient.txt")) {
        QMessageBox::critical(this, "Not Found", "This person is not registered as a patient. Cannot update patient-specific fields.");
        return;
    }

>>>>>>> origin/zainab
    Patient p;
    int newAge = 0;
    double newNum = 0;

<<<<<<< HEAD
    switch (field) {
    case 1: if (!p.Is_Valid_Phone(val.toStdString()))   { QMessageBox::warning(this,"Invalid","Invalid Phone Number format."); return; } break;
    case 2: if (!p.Is_Valid_Email(val.toStdString()))   { QMessageBox::warning(this,"Invalid","Invalid Email Address format."); return; } break;
    case 3: if (!p.Is_Valid_Address(val.toStdString())) { QMessageBox::warning(this,"Invalid","Address field cannot be empty."); return; } break;
    case 4: newAge = val.toInt(); if (!p.Is_Valid_Age(newAge)) { QMessageBox::warning(this,"Invalid","Invalid Age (must be 1-120)."); return; } break;
    case 5: if (!p.isValidContact(val.toStdString())) { QMessageBox::warning(this,"Invalid","Invalid Emergency Contact Number."); return; } break;
    case 6: if (!p.isValidStatus(val.toStdString()))  { QMessageBox::warning(this,"Invalid","Invalid Status (Inpatient/Outpatient/Discharged)."); return; } break;
    case 7: newNum = val.toDouble(); if (!p.isValidWeight(newNum)) { QMessageBox::warning(this,"Invalid","Invalid Weight (must be positive)."); return; } break;
    case 8: newNum = val.toDouble(); if (!p.isValidHeight(newNum)) { QMessageBox::warning(this,"Invalid","Invalid Height (must be positive)."); return; } break;
    case 9: if (!p.isValidPatientType(val.toStdString())) { QMessageBox::warning(this,"Invalid","Invalid Patient Type."); return; } break;
    }

    if (field >= 1 && field <= 4)
        rewritePerson(cnic, field, val, newAge);
    else
        rewritePatient(cnic, field, val, newNum);
=======
    // Index mapping:
    // 0: Phone Number
    // 1: Email
    // 2: Address
    // 3: Age
    // 4: Emergency Contact
    // 5: Patient Status
    // 6: Weight
    // 7: Height
    // 8: Patient Type

    switch (idx) {
    case 0: // Phone
        if (!p.Is_Valid_Phone(val.toStdString()))   { QMessageBox::warning(this,"Invalid","Invalid Phone number."); return; } 
        if (Person::Phone_Already_Exists(val.toStdString(), "Person.txt", cnic.toStdString())) {
            QMessageBox::warning(this, "Duplicate", "This Phone number already belongs to another person."); return;
        }
        break;
    case 1: // Email
        if (!p.Is_Valid_Email(val.toStdString()))   { QMessageBox::warning(this,"Invalid","Invalid Email Address format."); return; } break;
    case 2: // Address
        if (!p.Is_Valid_Address(val.toStdString())) { QMessageBox::warning(this,"Invalid","Address field cannot be empty."); return; } break;
    case 3: // Age
        {
            newAge = val.toInt();
            if (!p.Is_Valid_Age(newAge)) {
                QMessageBox::warning(this, "Invalid", "Invalid Age (must be 1-120).");
                return;
            }
            
            // Check if new age is >= current age
            std::ifstream ageFile("Person.txt");
            std::string aln;
            int currentAge = 0;
            while (std::getline(ageFile, aln)) {
                if (aln != "----------") continue;
                std::string c, n, a;
                std::getline(ageFile, c);
                std::getline(ageFile, n);
                std::getline(ageFile, a);
                if (c == cnic.toStdString()) {
                    currentAge = std::stoi(a);
                    break;
                }
            }
            ageFile.close();
            
            if (newAge < currentAge) {
                QMessageBox::warning(this, "Invalid Age", 
                                     QString("New age (%1) cannot be less than current age (%2).")
                                     .arg(newAge).arg(currentAge));
                return;
            }
        }
        break;
    case 4: // Emergency Contact
        if (!p.isValidContact(val.toStdString())) { QMessageBox::warning(this,"Invalid","Invalid Emergency Contact Number."); return; } break;
    case 5: // Patient Status
        if (!p.isValidStatus(val.toStdString()))  { QMessageBox::warning(this,"Invalid","Invalid Status."); return; } break;
    case 6: // Weight
        newNum = val.toDouble(); if (!p.isValidWeight(newNum)) { QMessageBox::warning(this,"Invalid","Invalid Weight."); return; } break;
    case 7: // Height
        newNum = val.toDouble(); if (!p.isValidHeight(newNum)) { QMessageBox::warning(this,"Invalid","Invalid Height."); return; } break;
    case 8: // Patient Type
        if (!p.isValidPatientType(val.toStdString())) { QMessageBox::warning(this,"Invalid","Invalid Patient Type."); return; } break;
    }

    if (idx <= 3) {
        // Adjust idx for rewritePerson (1-indexed based on original logic, but rewritePerson uses its own mapping)
        // Original rewritePerson: 0:Name, 1:Phone, 2:Email, 3:Address, 4:Age
        int fieldMap[] = {1, 2, 3, 4}; 
        rewritePerson(cnic, fieldMap[idx], val, newAge);
    } else {
        // Adjust idx for rewritePatient
        // Original rewritePatient: 6:Contact, 7:Status, 8:Weight, 9:Height, 10:Type
        int fieldMap[] = {6, 7, 8, 9, 10}; 
        rewritePatient(cnic, fieldMap[idx - 4], val, newNum);
    }
>>>>>>> origin/zainab

    QMessageBox::information(this, "Updated", "Patient record has been successfully updated.");
    accept();
}

void PatientUpdateDialog::rewritePerson(const QString &targetCnic, int field, const QString &val, int newAge) {
    std::ifstream fin("Person.txt");
    std::ofstream fout("Person_temp.txt");
    std::string ln;
    while (std::getline(fin, ln)) {
        if (ln != "----------") continue;
        fout << ln << "\n";
        std::string cnic, name, age, gender, phone, email, address;
        std::getline(fin, cnic); std::getline(fin, name); std::getline(fin, age);
        std::getline(fin, gender); std::getline(fin, phone); std::getline(fin, email);
        std::getline(fin, address);
        if (cnic == targetCnic.toStdString()) {
<<<<<<< HEAD
            fout << cnic << "\n" << name << "\n";
=======
            fout << cnic << "\n";
            fout << ((field == 0) ? val.toStdString() : name) << "\n";
>>>>>>> origin/zainab
            fout << ((field == 4) ? std::to_string(newAge) : age) << "\n";
            fout << gender << "\n";
            fout << ((field == 1) ? val.toStdString() : phone)   << "\n";
            fout << ((field == 2) ? val.toStdString() : email)   << "\n";
            fout << ((field == 3) ? val.toStdString() : address) << "\n";
        } else {
<<<<<<< HEAD
            fout << cnic<<"\n"<<name<<"\n"<<age<<"\n"<<gender<<"\n"
                 << phone<<"\n"<<email<<"\n"<<address<<"\n";
=======
            fout << cnic << "\n" << name << "\n" << age << "\n" << gender << "\n"
                 << phone << "\n" << email << "\n" << address << "\n";
>>>>>>> origin/zainab
        }
    }
    fin.close(); fout.close();
    std::remove("Person.txt");
    std::rename("Person_temp.txt", "Person.txt");
}

void PatientUpdateDialog::rewritePatient(const QString &targetCnic, int field, const QString &val, double newNum) {
    std::ifstream fin("Patient.txt");
    std::ofstream fout("Patient_temp.txt");
    std::string ln;
    while (std::getline(fin, ln)) {
        if (ln != "----------") continue;
        fout << ln << "\n";
<<<<<<< HEAD
        std::string cnic, pid, blood, type, h, w, contact, status;
        std::getline(fin, cnic); std::getline(fin, pid); std::getline(fin, blood);
        std::getline(fin, type); std::getline(fin, h); std::getline(fin, w);
        std::getline(fin, contact); std::getline(fin, status);
        if (cnic == targetCnic.toStdString()) {
            fout << cnic<<"\n"<<pid<<"\n"<<blood<<"\n";
            fout << ((field == 9) ? val.toStdString() : type) << "\n";
            fout << ((field == 8) ? std::to_string(newNum) : h) << "\n";
            fout << ((field == 7) ? std::to_string(newNum) : w) << "\n";
            fout << ((field == 5) ? val.toStdString() : contact) << "\n";
            fout << ((field == 6) ? val.toStdString() : status) << "\n";
        } else {
            fout << cnic<<"\n"<<pid<<"\n"<<blood<<"\n"<<type<<"\n"
                 << h<<"\n"<<w<<"\n"<<contact<<"\n"<<status<<"\n";
=======
        std::string cnic, pid, blood, type, contact, status;
        double h, w;
        std::getline(fin, cnic); std::getline(fin, pid); std::getline(fin, blood);
        std::getline(fin, type); 
        fin >> h >> w;
        fin.ignore(1000, '\n');
        std::getline(fin, contact); std::getline(fin, status);

        if (cnic == targetCnic.toStdString()) {
            fout << cnic << "\n" << pid << "\n" << blood << "\n";
            fout << ((field == 10) ? val.toStdString() : type) << "\n";
            fout << ((field == 9) ? std::to_string(newNum) : std::to_string(h)) << "\n" 
                 << ((field == 8) ? std::to_string(newNum) : std::to_string(w)) << "\n";
            fout << ((field == 6) ? val.toStdString() : contact) << "\n";
            fout << ((field == 7) ? val.toStdString() : status) << "\n";
        } else {
            fout << cnic << "\n" << pid << "\n" << blood << "\n" << type << "\n"
                 << h << "\n" << w << "\n" << contact << "\n" << status << "\n";
>>>>>>> origin/zainab
        }
    }
    fin.close(); fout.close();
    std::remove("Patient.txt");
<<<<<<< HEAD
    std::rename("Patient_temp.txt", "Patient.txt");
=======
    if (std::rename("Patient_temp.txt", "Patient.txt") != 0) {
        // Retry logic for Windows
        std::remove("Patient.txt");
        if (std::rename("Patient_temp.txt", "Patient.txt") != 0) {
             QMessageBox::critical(nullptr, "File Error", "Failed to update Patient.txt. Ensure the file is not open in another program.");
        }
    }
>>>>>>> origin/zainab
}