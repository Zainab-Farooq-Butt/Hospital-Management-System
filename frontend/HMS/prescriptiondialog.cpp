#include "PrescriptionDialog.h"
#include "../../Pharmacy.h"
#include "../../Patient.h"

#include <QFormLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QMessageBox>
#include <sstream>
#include <iostream>

PrescriptionDialog::PrescriptionDialog(QWidget *parent) : QDialog(parent) {
    setWindowTitle("Issue Prescription");
    resize(380, 220);

    txtPatientId = new QLineEdit(this);
    txtMedicine  = new QLineEdit(this);
    spinQty      = new QSpinBox(this); spinQty->setRange(1, 10000);

    auto *form = new QFormLayout();
    form->addRow("Patient ID:", txtPatientId);
    form->addRow("Medicine:",   txtMedicine);
    form->addRow("Quantity:",   spinQty);

    auto *btnIssue  = new QPushButton("Issue", this);
    auto *btnCancel = new QPushButton("Cancel", this);
    auto *btnRow = new QHBoxLayout();
    btnRow->addStretch(); btnRow->addWidget(btnCancel); btnRow->addWidget(btnIssue);

    auto *root = new QVBoxLayout(this);
    root->addLayout(form);
    root->addLayout(btnRow);

    connect(btnIssue,  &QPushButton::clicked, this, &PrescriptionDialog::onIssue);
    connect(btnCancel, &QPushButton::clicked, this, &QDialog::reject);
}

void PrescriptionDialog::onIssue() {
    QString pid  = txtPatientId->text().trimmed();
    QString name = txtMedicine->text().trimmed();
    int qty      = spinQty->value();

    Patient p;
    if (!p.isValidPatientId(pid.toStdString()) ||
        !p.patientIdAlreadyExists(pid.toStdString(), "Patient.txt")) {
        QMessageBox::warning(this, "Invalid", "Invalid Patient ID."); return;
    }
    if (qty <= 0) {
        QMessageBox::warning(this, "Invalid", "Quantity must be > 0."); return;
    }

    Pharmacy ph;
    ph.loadInventory();
    ph.loadPrescriptions();

    std::stringstream buf;
    std::streambuf *old = std::cout.rdbuf(buf.rdbuf());
    ph.prescriptionIssue(pid.toStdString(), name.toStdString(), qty);
    std::cout.rdbuf(old);

    QMessageBox::information(this, "Result", QString::fromStdString(buf.str()));
    accept();
}