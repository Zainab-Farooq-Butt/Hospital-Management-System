#include "DoctorUpdateDialog.h"
#include "../../Doctor.h"

#include <QFormLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QMessageBox>
#include <fstream>
#include <cstdio>

DoctorUpdateDialog::DoctorUpdateDialog(QWidget *parent) : QDialog(parent) {
    setWindowTitle("Update Doctor");
    resize(420, 200);

    txtCnic  = new QLineEdit(this);
    cmbField = new QComboBox(this);
    cmbField->addItems({
        "Phone Number",        // 1 -> Person
        "Email",               // 2 -> Person
        "Address",             // 3 -> Person
        "Age",                 // 4 -> Person
        "Specialization",      // 5 -> Doctor
        "Qualification",       // 6 -> Doctor
        "Experience (years)",  // 7 -> Doctor
        "Consultation Fee",    // 8 -> Doctor
        "Availability",        // 9 -> Doctor
        "Availability Status"  // 10 -> Doctor
    });
    txtValue = new QLineEdit(this);

    auto *form = new QFormLayout();
    form->addRow("CNIC:",      txtCnic);
    form->addRow("Field:",     cmbField);
    form->addRow("New Value:", txtValue);

    auto *btnApply  = new QPushButton("Apply", this);
    auto *btnCancel = new QPushButton("Cancel", this);
    auto *btnRow = new QHBoxLayout();
    btnRow->addStretch(); btnRow->addWidget(btnCancel); btnRow->addWidget(btnApply);

    auto *root = new QVBoxLayout(this);
    root->addLayout(form);
    root->addLayout(btnRow);

    connect(btnApply,  &QPushButton::clicked, this, &DoctorUpdateDialog::onApply);
    connect(btnCancel, &QPushButton::clicked, this, &QDialog::reject);
}

void DoctorUpdateDialog::onApply() {
    QString cnic = txtCnic->text().trimmed();
    int field = cmbField->currentIndex() + 1;
    QString val = txtValue->text().trimmed();

    if (cnic.isEmpty() || val.isEmpty()) {
        QMessageBox::warning(this, "Missing", "Enter CNIC and new value.");
        return;
    }

    Doctor d;
    int newAge = 0, newExp = 0;
    double newFee = 0;

    switch (field) {
        case 1: if (!d.Is_Valid_Phone(val.toStdString()))   { QMessageBox::warning(this,"Invalid","Bad phone"); return; } break;
        case 2: if (!d.Is_Valid_Email(val.toStdString()))   { QMessageBox::warning(this,"Invalid","Bad email"); return; } break;
        case 3: if (!d.Is_Valid_Address(val.toStdString())) { QMessageBox::warning(this,"Invalid","Bad address"); return; } break;
        case 4: newAge = val.toInt(); if (!d.Is_Valid_Age(newAge)) { QMessageBox::warning(this,"Invalid","Bad age"); return; } break;
        case 5: if (!d.isValidSpecialization(val.toStdString())) { QMessageBox::warning(this,"Invalid","Bad specialization"); return; } break;
        case 6: if (!d.isValidQualification(val.toStdString()))  { QMessageBox::warning(this,"Invalid","Bad qualification"); return; } break;
        case 7: newExp = val.toInt(); if (!d.isValidExperience(newExp, newAge > 0 ? newAge : 30)) { QMessageBox::warning(this,"Invalid","Bad experience"); return; } break;
        case 8: newFee = val.toDouble(); if (!d.isValidFee(newFee)) { QMessageBox::warning(this,"Invalid","Bad fee"); return; } break;
        case 9: /* Availability format check - skip for now, backend accepts any non-empty */ if (val.isEmpty()) { QMessageBox::warning(this,"Invalid","Empty availability"); return; } break;
        case 10: if (!d.isValidAvailabilityStatus(val.toStdString())) { QMessageBox::warning(this,"Invalid","Bad status"); return; } break;
    }

    if (field >= 1 && field <= 4)
        rewritePerson(cnic, field, val, newAge);
    else
        rewriteDoctor(cnic, field, val, newExp, newFee);

    QMessageBox::information(this, "Updated", "Doctor record updated.");
    accept();
}

void DoctorUpdateDialog::rewritePerson(const QString &targetCnic, int field, const QString &val, int newAge) {
    std::ifstream fin("Person.txt");
    std::ofstream fout("Person_temp.txt");
    std::string ln;
    while (std::getline(fin, ln)) {
        if (ln != "----------") continue;
        fout << ln << "\n";
        std::string cnic, name, age, gender, phone, email, address;
        std::getline(fin, cnic);  std::getline(fin, name);
        std::getline(fin, age);   std::getline(fin, gender);
        std::getline(fin, phone); std::getline(fin, email);
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

void DoctorUpdateDialog::rewriteDoctor(const QString &targetCnic, int field, const QString &val, int newExp, double newFee) {
    std::ifstream fin("Doctor.txt");
    std::ofstream fout("Doctor_temp.txt");
    std::string ln;
    while (std::getline(fin, ln)) {
        if (ln != "----------") continue;
        fout << ln << "\n";
        std::string cnic, did, spec, qual, exp, fee, avail, status;
        std::getline(fin, cnic);  std::getline(fin, did);
        std::getline(fin, spec);  std::getline(fin, qual);
        std::getline(fin, exp);   std::getline(fin, fee);
        std::getline(fin, avail); std::getline(fin, status);
        if (cnic == targetCnic.toStdString()) {
            fout << cnic << "\n" << did << "\n";
            fout << ((field == 5)  ? val.toStdString() : spec)   << "\n";
            fout << ((field == 6)  ? val.toStdString() : qual)   << "\n";
            fout << ((field == 7)  ? std::to_string(newExp) : exp) << "\n";
            fout << ((field == 8)  ? std::to_string(newFee) : fee) << "\n";
            fout << ((field == 9)  ? val.toStdString() : avail)  << "\n";
            fout << ((field == 10) ? val.toStdString() : status) << "\n";
        } else {
            fout << cnic<<"\n"<<did<<"\n"<<spec<<"\n"<<qual<<"\n"
                 << exp<<"\n"<<fee<<"\n"<<avail<<"\n"<<status<<"\n";
        }
    }
    fin.close(); fout.close();
    std::remove("Doctor.txt");
    std::rename("Doctor_temp.txt", "Doctor.txt");
}