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
    resize(420, 200);

    txtCnic = new QLineEdit(this);
    cmbField = new QComboBox(this);
    cmbField->addItems({
        "Phone Number", "Email", "Address", "Age",
        "Emergency Contact", "Patient Status",
        "Weight", "Height", "Patient Type"
    });
    txtValue = new QLineEdit(this);

    auto *form = new QFormLayout();
    form->addRow("CNIC:",       txtCnic);
    form->addRow("Field:",      cmbField);
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
        QMessageBox::warning(this, "Missing", "Enter CNIC and new value.");
        return;
    }

    int field = idx + 1;
    Patient p;
    int newAge = 0;
    double newNum = 0;

    switch (field) {
    case 1: if (!p.Is_Valid_Phone(val.toStdString()))   { QMessageBox::warning(this,"Invalid","Bad phone"); return; } break;
    case 2: if (!p.Is_Valid_Email(val.toStdString()))   { QMessageBox::warning(this,"Invalid","Bad email"); return; } break;
    case 3: if (!p.Is_Valid_Address(val.toStdString())) { QMessageBox::warning(this,"Invalid","Bad address"); return; } break;
    case 4: newAge = val.toInt(); if (!p.Is_Valid_Age(newAge)) { QMessageBox::warning(this,"Invalid","Bad age"); return; } break;
    case 5: if (!p.isValidContact(val.toStdString())) { QMessageBox::warning(this,"Invalid","Bad contact"); return; } break;
    case 6: if (!p.isValidStatus(val.toStdString()))  { QMessageBox::warning(this,"Invalid","Bad status"); return; } break;
    case 7: newNum = val.toDouble(); if (!p.isValidWeight(newNum)) { QMessageBox::warning(this,"Invalid","Bad weight"); return; } break;
    case 8: newNum = val.toDouble(); if (!p.isValidHeight(newNum)) { QMessageBox::warning(this,"Invalid","Bad height"); return; } break;
    case 9: if (!p.isValidPatientType(val.toStdString())) { QMessageBox::warning(this,"Invalid","Bad type"); return; } break;
    }

    if (field >= 1 && field <= 4)
        rewritePerson(cnic, field, val, newAge);
    else
        rewritePatient(cnic, field, val, newNum);

    QMessageBox::information(this, "Updated", "Record updated.");
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
            fout << cnic << "\n" << name << "\n";
            fout << ((field == 4) ? std::to_string(newAge) : age) << "\n";
            fout << gender << "\n";
            fout << ((field == 1) ? val.toStdString() : phone)   << "\n";
            fout << ((field == 2) ? val.toStdString() : email)   << "\n";
            fout << ((field == 3) ? val.toStdString() : address) << "\n";
        } else {
            fout << cnic<<"\n"<<name<<"\n"<<age<<"\n"<<gender<<"\n"
                 << phone<<"\n"<<email<<"\n"<<address<<"\n";
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
        }
    }
    fin.close(); fout.close();
    std::remove("Patient.txt");
    std::rename("Patient_temp.txt", "Patient.txt");
}