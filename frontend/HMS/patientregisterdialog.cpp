#include "PatientRegisterDialog.h"
#include "../../Person.h"
#include "../../Patient.h"
#include "../../Login.h"

#include <QFormLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QMessageBox>
#include <QLabel>
#include <fstream>

PatientRegisterDialog::PatientRegisterDialog(QWidget *parent) : QDialog(parent) {
    setWindowTitle("Register New Patient");
    resize(500, 700);

    auto *form = new QFormLayout();

    txtCnic     = new QLineEdit(this);
    txtName     = new QLineEdit(this);
    spinAge     = new QSpinBox(this); spinAge->setRange(0, 150);
    cmbGender   = new QComboBox(this); cmbGender->addItems({"Male","Female","Other"});
    txtPhone    = new QLineEdit(this);
    txtEmail    = new QLineEdit(this);
    txtAddress  = new QPlainTextEdit(this); txtAddress->setMaximumHeight(60);
    cmbBlood    = new QComboBox(this); cmbBlood->addItems({"A+","A-","B+","B-","AB+","AB-","O+","O-"});
    cmbType     = new QComboBox(this); cmbType->addItems({"Inpatient","Outpatient","Emergency"});
    spinHeight  = new QDoubleSpinBox(this); spinHeight->setRange(0, 300); spinHeight->setSuffix(" cm");
    spinWeight  = new QDoubleSpinBox(this); spinWeight->setRange(0, 500); spinWeight->setSuffix(" kg");
    txtContact  = new QLineEdit(this);
    txtUsername = new QLineEdit(this);
    txtPassword = new QLineEdit(this); txtPassword->setEchoMode(QLineEdit::Password);

    form->addRow("CNIC:",              txtCnic);
    form->addRow("Name:",              txtName);
    form->addRow("Age:",               spinAge);
    form->addRow("Gender:",            cmbGender);
    form->addRow("Phone:",             txtPhone);
    form->addRow("Email:",             txtEmail);
    form->addRow("Address:",           txtAddress);
    form->addRow("Blood Group:",       cmbBlood);
    form->addRow("Patient Type:",      cmbType);
    form->addRow("Height:",            spinHeight);
    form->addRow("Weight:",            spinWeight);
    form->addRow("Emergency Contact:", txtContact);
    form->addRow("Username:",          txtUsername);
    form->addRow("Password:",          txtPassword);

    auto *btnRegister = new QPushButton("Register", this);
    auto *btnCancel   = new QPushButton("Cancel", this);
    auto *btnRow = new QHBoxLayout();
    btnRow->addStretch();
    btnRow->addWidget(btnCancel);
    btnRow->addWidget(btnRegister);

    auto *root = new QVBoxLayout(this);
    root->addLayout(form);
    root->addLayout(btnRow);

    connect(btnRegister, &QPushButton::clicked, this, &PatientRegisterDialog::onRegister);
    connect(btnCancel,   &QPushButton::clicked, this, &QDialog::reject);
}

void PatientRegisterDialog::onRegister() {
    QString cnic    = txtCnic->text().trimmed();
    QString name    = txtName->text().trimmed();
    int     age     = spinAge->value();
    QString gender  = cmbGender->currentText();
    QString phone   = txtPhone->text().trimmed();
    QString email   = txtEmail->text().trimmed();
    QString address = txtAddress->toPlainText().trimmed();
    QString blood   = cmbBlood->currentText();
    QString type    = cmbType->currentText();
    double  height  = spinHeight->value();
    double  weight  = spinWeight->value();
    QString contact = txtContact->text().trimmed();
    QString uname   = txtUsername->text().trimmed();
    QString pwd     = txtPassword->text();

    Person tmp;
    if (!tmp.Is_Valid_CNIC(cnic.toStdString()))    { QMessageBox::warning(this,"Invalid","Bad CNIC."); return; }
    if (!tmp.Is_Valid_Name(name.toStdString()))    { QMessageBox::warning(this,"Invalid","Bad Name."); return; }
    if (!tmp.Is_Valid_Age(age))                    { QMessageBox::warning(this,"Invalid","Bad Age."); return; }
    if (!tmp.Is_Valid_Phone(phone.toStdString()))  { QMessageBox::warning(this,"Invalid","Bad Phone."); return; }
    if (!tmp.Is_Valid_Email(email.toStdString()))  { QMessageBox::warning(this,"Invalid","Bad Email."); return; }
    if (!tmp.Is_Valid_Address(address.toStdString())){ QMessageBox::warning(this,"Invalid","Bad Address."); return; }

    Patient p;
    if (!p.isValidContact(contact.toStdString()))  { QMessageBox::warning(this,"Invalid","Bad Emergency Contact."); return; }
    if (!p.isValidHeight(height) || !p.isValidWeight(weight)) {
        QMessageBox::warning(this, "Invalid", "Bad Height or Weight."); return;
    }
    if (uname.isEmpty() || pwd.isEmpty()) {
        QMessageBox::warning(this, "Invalid", "Username and Password required."); return;
    }

    Person base(cnic.toStdString(), name.toStdString(), age,
                gender.toStdString(), phone.toStdString(),
                email.toStdString(), address.toStdString());

    std::ofstream pout("Person.txt", std::ios::app);
    base.Save_To_File(pout);
    pout.close();

    QString patId = QString::fromStdString(p.generatePatientId());
    QString status = (type.toLower() == "inpatient") ? "admitted" : "not admitted";

    p.setLinkedCNIC(cnic.toStdString());
    p.setPatientId(patId.toStdString());
    p.setBloodGroup(blood.toStdString());
    p.setPatientType(type.toLower().toStdString());
    p.setHeight(height);
    p.setWeight(weight);
    p.setEmergencyContact(contact.toStdString());
    p.setPatientStatus(status.toStdString());

    std::ofstream patout("Patient.txt", std::ios::app);
    p.Save_To_File(patout);
    patout.close();

    Login::Save_Login_to_File(uname.toStdString(), pwd.toStdString(),
                              "PATIENT", cnic.toStdString());

    QMessageBox::information(this, "Success",
                             "Patient registered.\nPatient ID: " + patId);
    accept();
}