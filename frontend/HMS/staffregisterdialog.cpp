#include "StaffRegisterDialog.h"
#include "../../Person.h"
#include "../../Staff.h"

#include <QFormLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QMessageBox>
#include <fstream>

StaffRegisterDialog::StaffRegisterDialog(QWidget *parent) : QDialog(parent) {
    setWindowTitle("Register Staff");
    resize(500, 600);

    txtCnic       = new QLineEdit(this);
    txtName       = new QLineEdit(this);
    spinAge       = new QSpinBox(this); spinAge->setRange(0, 150);
    cmbGender     = new QComboBox(this); cmbGender->addItems({"Male","Female","Other"});
    txtPhone      = new QLineEdit(this);
    txtEmail      = new QLineEdit(this);
    txtAddress    = new QLineEdit(this);
    txtDepartment = new QLineEdit(this);
    txtJobTitle   = new QLineEdit(this);
    txtShift      = new QLineEdit(this);
    spinSalary    = new QDoubleSpinBox(this); spinSalary->setRange(0, 10000000);
    txtJoinDate   = new QLineEdit(this);
    cmbStatus     = new QComboBox(this); cmbStatus->addItems({"Active","On Leave","Terminated"});

    auto *form = new QFormLayout();
    form->addRow("CNIC:",       txtCnic);
    form->addRow("Name:",       txtName);
    form->addRow("Age:",        spinAge);
    form->addRow("Gender:",     cmbGender);
    form->addRow("Phone:",      txtPhone);
    form->addRow("Email:",      txtEmail);
    form->addRow("Address:",    txtAddress);
    form->addRow("Department:", txtDepartment);
    form->addRow("Job Title:",  txtJobTitle);
    form->addRow("Shift:",      txtShift);
    form->addRow("Salary:",     spinSalary);
    form->addRow("Join Date:",  txtJoinDate);
    form->addRow("Status:",     cmbStatus);

    auto *btnRegister = new QPushButton("Register", this);
    auto *btnCancel   = new QPushButton("Cancel", this);
    auto *btnRow = new QHBoxLayout();
    btnRow->addStretch(); btnRow->addWidget(btnCancel); btnRow->addWidget(btnRegister);

    auto *root = new QVBoxLayout(this);
    root->addLayout(form);
    root->addLayout(btnRow);

    connect(btnRegister, &QPushButton::clicked, this, &StaffRegisterDialog::onRegister);
    connect(btnCancel,   &QPushButton::clicked, this, &QDialog::reject);
}

void StaffRegisterDialog::onRegister() {
    QString cnic   = txtCnic->text().trimmed();
    QString name   = txtName->text().trimmed();
    int age        = spinAge->value();
    QString gender = cmbGender->currentText();
    QString phone  = txtPhone->text().trimmed();
    QString email  = txtEmail->text().trimmed();
    QString addr   = txtAddress->text().trimmed();
    QString dept   = txtDepartment->text().trimmed();
    QString job    = txtJobTitle->text().trimmed();
    QString shift  = txtShift->text().trimmed();
    double  salary = spinSalary->value();
    QString date   = txtJoinDate->text().trimmed();
    QString status = cmbStatus->currentText();

    Person tmp;
    if (!tmp.Is_Valid_CNIC_Format(cnic.toStdString())  || name.isEmpty() ||
        !tmp.Is_Valid_Age(age)                  || !tmp.Is_Valid_Phone(phone.toStdString()) ||
        !tmp.Is_Valid_Email(email.toStdString())|| !tmp.Is_Valid_Address(addr.toStdString())) {
        QMessageBox::warning(this, "Invalid", "Person fields invalid."); return;
    }
    if (Person::CNIC_Already_Exists(cnic.toStdString(), "Person.txt")) {
        QMessageBox::warning(this, "Duplicate", "This CNIC is already registered."); return;
    }
    if (Person::Phone_Already_Exists(phone.toStdString(), "Person.txt")) {
        QMessageBox::warning(this, "Duplicate", "This Phone number is already registered."); return;
    }

    Staff s;
    if (!s.isValidDepartment(dept.toStdString()) || !s.isValidJobTitle(job.toStdString()) ||
        !s.isValidShift(shift.toStdString())     || !s.isValidSalary(salary) ||
        !s.isValidJoiningDate(date.toStdString())|| !s.isValidEmploymentStatus(status.toStdString())) {
        QMessageBox::warning(this, "Invalid", "Staff fields invalid."); return;
    }

    Person base(cnic.toStdString(), name.toStdString(), age,
                gender.toStdString(), phone.toStdString(),
                email.toStdString(), addr.toStdString());
    std::ofstream pout("Person.txt", std::ios::app);
    base.Save_To_File(pout);
    pout.close();

    QString staffId = QString::fromStdString(s.generateStaffId());
    s.setLinkedCNIC(cnic.toStdString());
    s.setStaffId(staffId.toStdString());
    s.setDepartment(dept.toStdString());
    s.setJobTitle(job.toStdString());
    s.setShift(shift.toStdString());
    s.setSalary(salary);
    s.setJoiningDate(date.toStdString());
    s.setEmploymentStatus(status.toStdString());

    std::ofstream out("Staff.txt", std::ios::app);
    s.Save_To_File(out);
    out.close();

    QMessageBox::information(this, "Success", "Staff registered.\nStaff ID: " + staffId);
    accept();
}