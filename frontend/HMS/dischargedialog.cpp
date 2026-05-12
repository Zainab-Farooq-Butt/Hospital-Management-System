#include "DischargeDialog.h"
#include "../../Patient.h"
#include "../../Room.h"

#include <QFormLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QMessageBox>

DischargeDialog::DischargeDialog(QWidget *parent) : QDialog(parent) {
    setWindowTitle("Discharge Patient");
    resize(380, 180);

    txtPatientId     = new QLineEdit(this);
    txtDischargeDate = new QLineEdit(this); txtDischargeDate->setPlaceholderText("DD/MM/YYYY");

    auto *form = new QFormLayout();
    form->addRow("Patient ID:",     txtPatientId);
    form->addRow("Discharge Date:", txtDischargeDate);

    auto *btnDischarge = new QPushButton("Discharge", this);
    auto *btnCancel    = new QPushButton("Cancel", this);
    auto *btnRow = new QHBoxLayout();
    btnRow->addStretch(); btnRow->addWidget(btnCancel); btnRow->addWidget(btnDischarge);

    auto *root = new QVBoxLayout(this);
    root->addLayout(form);
    root->addLayout(btnRow);

    connect(btnDischarge, &QPushButton::clicked, this, &DischargeDialog::onDischarge);
    connect(btnCancel,    &QPushButton::clicked, this, &QDialog::reject);
}

void DischargeDialog::onDischarge() {
    QString pid  = txtPatientId->text().trimmed();
    QString date = txtDischargeDate->text().trimmed();

    Patient p;
    if (!p.isValidPatientId(pid.toStdString()) ||
        !p.patientIdAlreadyExists(pid.toStdString(), "Patient.txt")) {
<<<<<<< HEAD
        QMessageBox::warning(this, "Invalid", "Bad Patient ID."); return;
=======
        QMessageBox::warning(this, "Invalid", "Invalid Patient ID."); return;
>>>>>>> origin/zainab
    }
    Room r;
    std::string ad_date = r.getAdmissionDate(pid.toStdString());
    if (ad_date.empty()) {
        QMessageBox::warning(this, "Not admitted", "Patient not in any room."); return;
    }
    if (!r.isValidDischarged(date.toStdString(), ad_date)) {
        QMessageBox::warning(this, "Invalid", "Discharge date invalid."); return;
    }
    r.patient_discharged(pid.toStdString(), date.toStdString());
    QMessageBox::information(this, "Done", "Patient discharged.");
    accept();
}