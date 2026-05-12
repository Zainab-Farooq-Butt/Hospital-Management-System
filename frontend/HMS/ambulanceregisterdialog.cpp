#include "AmbulanceRegisterDialog.h"
#include "../../Ambulance.h"

#include <QFormLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QMessageBox>

AmbulanceRegisterDialog::AmbulanceRegisterDialog(QWidget *parent) : QDialog(parent) {
    setWindowTitle("Register Ambulance");
    resize(380, 220);

<<<<<<< HEAD
    txtPlate     = new QLineEdit(this); txtPlate->setPlaceholderText("e.g. ABC-123");
    txtAddress   = new QLineEdit(this);
    chkAvailable = new QCheckBox("Available", this);
=======
    txtPlate       = new QLineEdit(this); txtPlate->setPlaceholderText("e.g. ABC-123");
    txtDestination = new QLineEdit(this);
    chkAvailable   = new QCheckBox("Available", this);
>>>>>>> origin/zainab
    chkAvailable->setChecked(true);

    auto *form = new QFormLayout();
    form->addRow("License Plate:", txtPlate);
<<<<<<< HEAD
    form->addRow("Address:",       txtAddress);
=======
    form->addRow("Destination:",   txtDestination);
>>>>>>> origin/zainab
    form->addRow("",               chkAvailable);

    auto *btnRegister = new QPushButton("Register", this);
    auto *btnCancel   = new QPushButton("Cancel", this);
    auto *btnRow = new QHBoxLayout();
    btnRow->addStretch(); btnRow->addWidget(btnCancel); btnRow->addWidget(btnRegister);

    auto *root = new QVBoxLayout(this);
    root->addLayout(form);
    root->addLayout(btnRow);

    connect(btnRegister, &QPushButton::clicked, this, &AmbulanceRegisterDialog::onRegister);
    connect(btnCancel,   &QPushButton::clicked, this, &QDialog::reject);
}

void AmbulanceRegisterDialog::onRegister() {
    QString plate = txtPlate->text().trimmed();
<<<<<<< HEAD
    QString addr  = txtAddress->text().trimmed();
=======
    QString dest  = txtDestination->text().trimmed();
>>>>>>> origin/zainab
    bool avail    = chkAvailable->isChecked();

    Ambulance a;
    if (!a.isValidLicensePlate(plate.toStdString())) {
<<<<<<< HEAD
        QMessageBox::warning(this, "Invalid", "Bad license plate."); return;
=======
        QMessageBox::warning(this, "Invalid", "Invalid license plate."); return;
>>>>>>> origin/zainab
    }
    if (a.licensePlateAlreadyExists(plate.toStdString(), "Ambulance.txt")) {
        QMessageBox::warning(this, "Duplicate", "License plate already registered."); return;
    }
<<<<<<< HEAD
    if (addr.isEmpty()) {
        QMessageBox::warning(this, "Invalid", "Address required."); return;
=======
    if (dest.isEmpty()) {
        QMessageBox::warning(this, "Invalid", "Destination required."); return;
>>>>>>> origin/zainab
    }

    a.setAmbulanceId(a.generateAmbulanceId());
    a.setDriverId(a.generateDriverId());
    a.setLicensePlate(plate.toStdString());
<<<<<<< HEAD
    a.setAddress(addr.toStdString());
=======
    a.setDestination(dest.toStdString());
>>>>>>> origin/zainab
    a.setAvailability(avail);
    a.saveToFile("Ambulance.txt");

    QMessageBox::information(this, "Done",
                             "Ambulance registered.\nID: " + QString::fromStdString(a.getAmbulanceId()));
    accept();
}