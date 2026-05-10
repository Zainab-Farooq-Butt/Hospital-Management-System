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
    resize(420, 250);

    txtCnic = new QLineEdit(this);
    cmbField = new QComboBox(this);
    cmbField->addItems({
        "Name", "Phone Number", "Email", "Address", "Age",
        "CNIC", "Emergency Contact", "Patient Status",
        "Weight", "Height", "Patient Type"
    });
    txtValue = new QLineEdit(this);

    auto *form = new QFormLayout();
    form->addRow("Current CNIC:", txtCnic);
    form->addRow("Field to Update:", cmbField);
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

    if (!Person::CNIC_Already_Exists(cnic.toStdString(), "Person.txt")) {
        QMessageBox::critical(this, "Not Found", "No person found with the provided CNIC.");
        return;
    }

    if (idx >= 6 && !Person::CNIC_Already_Exists(cnic.toStdString(), "Patient.txt")) {
        QMessageBox::critical(this, "Not Found", "This person is not registered as a patient. Cannot update patient-specific fields.");
        return;
    }

    Patient p;
    int newAge = 0;
    double newNum = 0;

    switch (idx) {
    case 0: // Name
        if (val.isEmpty()) { QMessageBox::warning(this,"Invalid","Name cannot be empty."); return; }
        break;
    case 1: // Phone
        if (!p.Is_Valid_Phone(val.toStdString()))   { QMessageBox::warning(this,"Invalid","Invalid Phone number."); return; } 
        if (Person::Phone_Already_Exists(val.toStdString(), "Person.txt", cnic.toStdString())) {
            QMessageBox::warning(this, "Duplicate", "This Phone number already belongs to another person."); return;
        }
        break;
    case 2: // Email
        if (!p.Is_Valid_Email(val.toStdString()))   { QMessageBox::warning(this,"Invalid","Invalid Email Address format."); return; } break;
    case 3: // Address
        if (!p.Is_Valid_Address(val.toStdString())) { QMessageBox::warning(this,"Invalid","Address field cannot be empty."); return; } break;
    case 4: // Age
        newAge = val.toInt(); if (!p.Is_Valid_Age(newAge)) { QMessageBox::warning(this,"Invalid","Invalid Age (must be 1-120)."); return; } break;
    case 5: // CNIC
        if (!Person::Is_Valid_CNIC_Format(val.toStdString())) { QMessageBox::warning(this,"Invalid","Invalid CNIC format."); return; }
        if (Person::CNIC_Already_Exists(val.toStdString(), "Person.txt")) { QMessageBox::warning(this,"Duplicate","New CNIC already exists."); return; }
        break;
    case 6: // Emergency Contact
        if (!p.isValidContact(val.toStdString())) { QMessageBox::warning(this,"Invalid","Invalid Emergency Contact Number."); return; } break;
    case 7: // Patient Status
        if (!p.isValidStatus(val.toStdString()))  { QMessageBox::warning(this,"Invalid","Invalid Status."); return; } break;
    case 8: // Weight
        newNum = val.toDouble(); if (!p.isValidWeight(newNum)) { QMessageBox::warning(this,"Invalid","Invalid Weight."); return; } break;
    case 9: // Height
        newNum = val.toDouble(); if (!p.isValidHeight(newNum)) { QMessageBox::warning(this,"Invalid","Invalid Height."); return; } break;
    case 10: // Patient Type
        if (!p.isValidPatientType(val.toStdString())) { QMessageBox::warning(this,"Invalid","Invalid Patient Type."); return; } break;
    }

    if (idx == 5) { // Global CNIC update
        Person::Update_CNIC_Everywhere(cnic.toStdString(), val.toStdString());
    } else if (idx <= 4) {
        rewritePerson(cnic, idx, val, newAge);
    } else {
        rewritePatient(cnic, idx, val, newNum);
    }

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
            fout << cnic << "\n";
            fout << ((field == 0) ? val.toStdString() : name) << "\n";
            fout << ((field == 4) ? std::to_string(newAge) : age) << "\n";
            fout << gender << "\n";
            fout << ((field == 1) ? val.toStdString() : phone)   << "\n";
            fout << ((field == 2) ? val.toStdString() : email)   << "\n";
            fout << ((field == 3) ? val.toStdString() : address) << "\n";
        } else {
            fout << cnic << "\n" << name << "\n" << age << "\n" << gender << "\n"
                 << phone << "\n" << email << "\n" << address << "\n";
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
            fout << ((field == 9) ? std::to_string(newNum) : std::to_string(h)) << " " 
                 << ((field == 8) ? std::to_string(newNum) : std::to_string(w)) << "\n";
            fout << ((field == 6) ? val.toStdString() : contact) << "\n";
            fout << ((field == 7) ? val.toStdString() : status) << "\n";
        } else {
            fout << cnic << "\n" << pid << "\n" << blood << "\n" << type << "\n"
                 << h << " " << w << "\n" << contact << "\n" << status << "\n";
        }
    }
    fin.close(); fout.close();
    std::remove("Patient.txt");
    if (std::rename("Patient_temp.txt", "Patient.txt") != 0) {
        std::remove("Patient.txt");
        std::rename("Patient_temp.txt", "Patient.txt");
    }
}