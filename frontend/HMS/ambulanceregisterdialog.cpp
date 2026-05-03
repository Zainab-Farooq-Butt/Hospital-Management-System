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

    txtPlate     = new QLineEdit(this); txtPlate->setPlaceholderText("e.g. ABC-123");
    txtAddress   = new QLineEdit(this);
    chkAvailable = new QCheckBox("Available", this);
    chkAvailable->setChecked(true);

    auto *form = new QFormLayout();
    form->addRow("License Plate:", txtPlate);
    form->addRow("Address:",       txtAddress);
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
    QString addr  = txtAddress->text().trimmed();
    bool avail    = chkAvailable->isChecked();

    Ambulance a;
    if (!a.isValidLicensePlate(plate.toStdString())) {
        QMessageBox::warning(this, "Invalid", "Bad license plate."); return;
    }
    if (a.licensePlateAlreadyExists(plate.toStdString(), "Ambulance.txt")) {
        QMessageBox::warning(this, "Duplicate", "License plate already registered."); return;
    }
    if (addr.isEmpty()) {
        QMessageBox::warning(this, "Invalid", "Address required."); return;
    }

    a.setAmbulanceId(a.generateAmbulanceId());
    a.setDriverId(a.generateDriverId());
    a.setLicensePlate(plate.toStdString());
    a.setAddress(addr.toStdString());
    a.setAvailability(avail);
    a.saveToFile("Ambulance.txt");

    QMessageBox::information(this, "Done",
                             "Ambulance registered.\nID: " + QString::fromStdString(a.getAmbulanceId()));
    accept();
}