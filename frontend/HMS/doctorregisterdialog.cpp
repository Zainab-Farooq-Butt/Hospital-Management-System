#include "DoctorRegisterDialog.h"
#include "../../Person.h"
#include "../../Doctor.h"
#include "../../Login.h"

#include <QFormLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QMessageBox>
#include <fstream>

DoctorRegisterDialog::DoctorRegisterDialog(QWidget *parent) : QDialog(parent) {
    setWindowTitle("Register Doctor");
    resize(500, 700);

    txtCnic         = new QLineEdit(this);
    txtName         = new QLineEdit(this);
    spinAge         = new QSpinBox(this); spinAge->setRange(0, 150);
    cmbGender       = new QComboBox(this); cmbGender->addItems({"Male","Female","Other"});
    txtPhone        = new QLineEdit(this);
    txtEmail        = new QLineEdit(this);
    txtAddress      = new QLineEdit(this);
    cmbSpec         = new QComboBox(this);
    cmbSpec->addItems({"Cardiology","Neurology","Orthopedics","Pediatrics",
                       "Dermatology","Oncology","Radiology","Psychiatry",
                       "General","Surgery"});
    cmbQual         = new QComboBox(this);
    cmbQual->addItems({"O Levels","Matric","A Levels","FSc","ICS",
                       "Bachelors","Masters","PhD","MBBS","MD","FCPS"});
    spinExp         = new QSpinBox(this); spinExp->setRange(0, 60);
    spinFee         = new QDoubleSpinBox(this); spinFee->setRange(0, 1000000);
    txtAvailability = new QLineEdit(this);
    txtAvailability->setPlaceholderText("e.g. Mon-Fri 9AM-5PM");
    cmbStatus       = new QComboBox(this); cmbStatus->addItems({"Available","Unavailable","On Leave"});
    txtUsername     = new QLineEdit(this);
    txtPassword     = new QLineEdit(this); txtPassword->setEchoMode(QLineEdit::Password);

    auto *form = new QFormLayout();
    form->addRow("CNIC:",            txtCnic);
    form->addRow("Name:",            txtName);
    form->addRow("Age:",             spinAge);
    form->addRow("Gender:",          cmbGender);
    form->addRow("Phone:",           txtPhone);
    form->addRow("Email:",           txtEmail);
    form->addRow("Address:",         txtAddress);
    form->addRow("Specialization:",  cmbSpec);
    form->addRow("Qualification:",   cmbQual);
    form->addRow("Experience (yrs):",spinExp);
    form->addRow("Fee:",             spinFee);
    form->addRow("Availability:",    txtAvailability);
    form->addRow("Status:",          cmbStatus);
    form->addRow("Username:",        txtUsername);
    form->addRow("Password:",        txtPassword);

    auto *btnRegister = new QPushButton("Register", this);
    auto *btnCancel   = new QPushButton("Cancel", this);
    auto *btnRow = new QHBoxLayout();
    btnRow->addStretch(); btnRow->addWidget(btnCancel); btnRow->addWidget(btnRegister);

    auto *root = new QVBoxLayout(this);
    root->addLayout(form);
    root->addLayout(btnRow);

    connect(btnRegister, &QPushButton::clicked, this, &DoctorRegisterDialog::onRegister);
    connect(btnCancel,   &QPushButton::clicked, this, &QDialog::reject);
}

void DoctorRegisterDialog::onRegister() {
    QString cnic   = txtCnic->text().trimmed();
    QString name   = txtName->text().trimmed();
    int age        = spinAge->value();
    QString gender = cmbGender->currentText();
    QString phone  = txtPhone->text().trimmed();
    QString email  = txtEmail->text().trimmed();
    QString addr   = txtAddress->text().trimmed();
    QString spec   = cmbSpec->currentText();
    QString qual   = cmbQual->currentText();
    int exp        = spinExp->value();
    double fee     = spinFee->value();
    QString avail  = txtAvailability->text().trimmed();
    QString status = cmbStatus->currentText();
    QString uname  = txtUsername->text().trimmed();
    QString pwd    = txtPassword->text();

    Person tmp;
    if (!tmp.Is_Valid_CNIC_Format(cnic.toStdString()) || name.isEmpty() ||
        !tmp.Is_Valid_Age(age) || !tmp.Is_Valid_Phone(phone.toStdString()) ||
        !tmp.Is_Valid_Email(email.toStdString()) || !tmp.Is_Valid_Address(addr.toStdString())) {
        QMessageBox::warning(this, "Invalid", "Person fields invalid."); return;
    }
    if (Person::CNIC_Already_Exists(cnic.toStdString(), "Person.txt")) {
        QMessageBox::warning(this, "Duplicate", "This CNIC is already registered."); return;
    }
    if (Person::Phone_Already_Exists(phone.toStdString(), "Person.txt")) {
        QMessageBox::warning(this, "Duplicate", "This Phone number is already registered."); return;
    }

    Doctor d;
    d.Set_Age(age);
    if (!d.isValidSpecialization(spec.toStdString()) || !d.isValidQualification(qual.toStdString()) ||
        !d.isValidExperience(exp, age) || !d.isValidFee(fee) ||
        !d.isValidAvailability(avail.toStdString()) ||
        !d.isValidAvailabilityStatus(status.toStdString())) {
        QMessageBox::warning(this, "Invalid", "Doctor fields invalid."); return;
    }
    if (uname.isEmpty() || pwd.isEmpty()) {
        QMessageBox::warning(this, "Invalid", "Username and Password required."); return;
    }

    Person base(cnic.toStdString(), name.toStdString(), age,
                gender.toStdString(), phone.toStdString(),
                email.toStdString(), addr.toStdString());
    std::ofstream pout("Person.txt", std::ios::app);
    base.Save_To_File(pout);
    pout.close();

    QString docId = QString::fromStdString(d.generateDoctorId());
    d.setDoctorId(docId.toStdString());
    d.setSpecialization(spec.toStdString());
    d.setQualification(qual.toStdString());
    d.setExperienceYears(exp);
    d.setConsultationFee(fee);
    d.setAvailability(avail.toStdString());
    d.setAvailabilityStatus(status.toStdString());
    d.setLinkedCNIC(cnic.toStdString());

    std::ofstream out("Doctor.txt", std::ios::app);
    d.Save_To_File(out);
    out.close();

    Login::Save_Login_to_File(uname.toStdString(), pwd.toStdString(),
                              "DOCTOR", cnic.toStdString());

    QMessageBox::information(this, "Success", "Doctor registered.\nDoctor ID: " + docId);
    accept();
}