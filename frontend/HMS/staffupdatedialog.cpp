#include "StaffUpdateDialog.h"
#include "../../Staff.h"

#include <QFormLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QMessageBox>
#include <fstream>
#include <cstdio>

StaffUpdateDialog::StaffUpdateDialog(QWidget *parent) : QDialog(parent) {
    setWindowTitle("Update Staff");
    resize(420, 200);

    txtCnic  = new QLineEdit(this);
    cmbField = new QComboBox(this);
    cmbField->addItems({
        "Phone Number",       // 1 -> Person
        "Email",              // 2 -> Person
        "Address",            // 3 -> Person
        "Age",                // 4 -> Person
        "Department",         // 5 -> Staff
        "Job Title",          // 6 -> Staff
        "Shift",              // 7 -> Staff
        "Salary",             // 8 -> Staff
        "Joining Date",       // 9 -> Staff
        "Employment Status"   // 10 -> Staff
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

    connect(btnApply,  &QPushButton::clicked, this, &StaffUpdateDialog::onApply);
    connect(btnCancel, &QPushButton::clicked, this, &QDialog::reject);
}

void StaffUpdateDialog::onApply() {
    QString cnic = txtCnic->text().trimmed();
    int field = cmbField->currentIndex() + 1;
    QString val = txtValue->text().trimmed();

    if (cnic.isEmpty() || val.isEmpty()) {
        QMessageBox::warning(this, "Missing", "Enter CNIC and new value.");
        return;
    }

    Staff s;
    int newAge = 0;
    double newSalary = 0;

    switch (field) {
        case 1: if (!s.Is_Valid_Phone(val.toStdString()))   { QMessageBox::warning(this,"Invalid","Bad phone"); return; } break;
        case 2: if (!s.Is_Valid_Email(val.toStdString()))   { QMessageBox::warning(this,"Invalid","Bad email"); return; } break;
        case 3: if (!s.Is_Valid_Address(val.toStdString())) { QMessageBox::warning(this,"Invalid","Bad address"); return; } break;
        case 4: newAge = val.toInt(); if (!s.Is_Valid_Age(newAge)) { QMessageBox::warning(this,"Invalid","Bad age"); return; } break;
        case 5: if (!s.isValidDepartment(val.toStdString())) { QMessageBox::warning(this,"Invalid","Bad department"); return; } break;
        case 6: if (!s.isValidJobTitle(val.toStdString()))   { QMessageBox::warning(this,"Invalid","Bad job title"); return; } break;
        case 7: if (!s.isValidShift(val.toStdString()))      { QMessageBox::warning(this,"Invalid","Bad shift"); return; } break;
        case 8: newSalary = val.toDouble(); if (!s.isValidSalary(newSalary)) { QMessageBox::warning(this,"Invalid","Bad salary"); return; } break;
        case 9: if (!s.isValidJoiningDate(val.toStdString())) { QMessageBox::warning(this,"Invalid","Bad date"); return; } break;
        case 10: if (!s.isValidEmploymentStatus(val.toStdString())) { QMessageBox::warning(this,"Invalid","Bad status"); return; } break;
    }

    if (field >= 1 && field <= 4)
        rewritePerson(cnic, field, val, newAge);
    else
        rewriteStaff(cnic, field, val, newSalary);

    QMessageBox::information(this, "Updated", "Staff record updated.");
    accept();
}

void StaffUpdateDialog::rewritePerson(const QString &targetCnic, int field, const QString &val, int newAge) {
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

void StaffUpdateDialog::rewriteStaff(const QString &targetCnic, int field, const QString &val, double newSalary) {
    std::ifstream fin("Staff.txt");
    std::ofstream fout("Staff_temp.txt");
    std::string ln;
    while (std::getline(fin, ln)) {
        if (ln != "----------") continue;
        fout << ln << "\n";
        std::string cnic, sid, dept, job, shift, salary, joinDate, status;
        std::getline(fin, cnic);     std::getline(fin, sid);
        std::getline(fin, dept);     std::getline(fin, job);
        std::getline(fin, shift);    std::getline(fin, salary);
        std::getline(fin, joinDate); std::getline(fin, status);
        if (cnic == targetCnic.toStdString()) {
            fout << cnic << "\n" << sid << "\n";
            fout << ((field == 5)  ? val.toStdString() : dept)     << "\n";
            fout << ((field == 6)  ? val.toStdString() : job)      << "\n";
            fout << ((field == 7)  ? val.toStdString() : shift)    << "\n";
            fout << ((field == 8)  ? std::to_string(newSalary) : salary) << "\n";
            fout << ((field == 9)  ? val.toStdString() : joinDate) << "\n";
            fout << ((field == 10) ? val.toStdString() : status)   << "\n";
        } else {
            fout << cnic<<"\n"<<sid<<"\n"<<dept<<"\n"<<job<<"\n"
                 << shift<<"\n"<<salary<<"\n"<<joinDate<<"\n"<<status<<"\n";
        }
    }
    fin.close(); fout.close();
    std::remove("Staff.txt");
    std::rename("Staff_temp.txt", "Staff.txt");
}