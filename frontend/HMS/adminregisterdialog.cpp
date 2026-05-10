#include "AdminRegisterDialog.h"
#include "../../Person.h"
#include "../../Login.h"

#include <QFormLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QMessageBox>
#include <fstream>

AdminRegisterDialog::AdminRegisterDialog(QWidget *parent) : QDialog(parent) {
    setWindowTitle("Register New Admin");
    resize(450, 550);

    auto *form = new QFormLayout();

    txtCnic     = new QLineEdit(this);
    txtName     = new QLineEdit(this);
    spinAge     = new QSpinBox(this); spinAge->setRange(0, 150);
    cmbGender   = new QComboBox(this); cmbGender->addItems({"Male","Female","Other"});
    txtPhone    = new QLineEdit(this);
    txtEmail    = new QLineEdit(this);
    txtAddress  = new QLineEdit(this);
    txtUsername = new QLineEdit(this);
    txtPassword = new QLineEdit(this); txtPassword->setEchoMode(QLineEdit::Password);

    form->addRow("CNIC:",       txtCnic);
    form->addRow("Name:",       txtName);
    form->addRow("Age:",        spinAge);
    form->addRow("Gender:",     cmbGender);
    form->addRow("Phone:",      txtPhone);
    form->addRow("Email:",      txtEmail);
    form->addRow("Address:",    txtAddress);
    form->addRow("Username:",   txtUsername);
    form->addRow("Password:",   txtPassword);

    auto *btnRegister = new QPushButton("Register Admin", this);
    auto *btnCancel   = new QPushButton("Cancel", this);
    auto *btnRow = new QHBoxLayout();
    btnRow->addStretch();
    btnRow->addWidget(btnCancel);
    btnRow->addWidget(btnRegister);

    auto *root = new QVBoxLayout(this);
    root->addLayout(form);
    root->addLayout(btnRow);

    connect(btnRegister, &QPushButton::clicked, this, &AdminRegisterDialog::onRegister);
    connect(btnCancel,   &QPushButton::clicked, this, &QDialog::reject);
}

void AdminRegisterDialog::onRegister() {
    QString cnic   = txtCnic->text().trimmed();
    QString name   = txtName->text().trimmed();
    int     age    = spinAge->value();
    QString gender = cmbGender->currentText();
    QString phone  = txtPhone->text().trimmed();
    QString email  = txtEmail->text().trimmed();
    QString address = txtAddress->text().trimmed();
    QString uname  = txtUsername->text().trimmed();
    QString pwd    = txtPassword->text();

    Person tmp;
    if (!tmp.Is_Valid_CNIC_Format(cnic.toStdString()))    { QMessageBox::warning(this,"Invalid","Invalid CNIC."); return; }
    if (Person::CNIC_Already_Exists(cnic.toStdString(), "Person.txt")) { QMessageBox::warning(this,"Duplicate","This CNIC is already registered."); return; }
    if (name.isEmpty())    { QMessageBox::warning(this,"Invalid","Invalid Name."); return; }
    if (!tmp.Is_Valid_Age(age))                    { QMessageBox::warning(this,"Invalid","Invalid Age."); return; }
    if (!tmp.Is_Valid_Phone(phone.toStdString()))  { QMessageBox::warning(this,"Invalid","Invalid Phone number."); return; }
    if (Person::Phone_Already_Exists(phone.toStdString(), "Person.txt")) { QMessageBox::warning(this,"Duplicate","This Phone number is already registered."); return; }
    if (!tmp.Is_Valid_Email(email.toStdString()))  { QMessageBox::warning(this,"Invalid","Invalid Email."); return; }
    if (address.isEmpty())                         { QMessageBox::warning(this,"Invalid","Invalid Address."); return; }
    if (uname.isEmpty() || pwd.isEmpty())          { QMessageBox::warning(this,"Invalid","Username and Password required."); return; }

    // Save Person info
    Person base(cnic.toStdString(), name.toStdString(), age,
                gender.toStdString(), phone.toStdString(),
                email.toStdString(), address.toStdString());

    std::ofstream pout("Person.txt", std::ios::app);
    base.Save_To_File(pout);
    pout.close();

    // Save Login info as ADMIN
    Login::Save_Login_to_File(uname.toStdString(), pwd.toStdString(),
                              "ADMIN", cnic.toStdString());

    QMessageBox::information(this, "Success", "New Admin registered successfully.");
    accept();
}
