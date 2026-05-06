#include "MedicalRecordAddDialog.h"
#include "../../Patient.h"

#include <QFormLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QMessageBox>
#include <fstream>

MedicalRecordAddDialog::MedicalRecordAddDialog(const QString &did, QWidget *parent)
    : QDialog(parent), doctorId(did) {
    setWindowTitle("Add Medical Record");
    resize(450, 280);

    lblDoctor    = new QLabel("Doctor ID: " + doctorId, this);
    txtPatientId = new QLineEdit(this);
    txtDiagnosis = new QLineEdit(this);
    txtTreatment = new QLineEdit(this);
    txtCost      = new QLineEdit(this);
    txtDate      = new QLineEdit(this); txtDate->setPlaceholderText("DD/MM/YYYY");

    auto *form = new QFormLayout();
    form->addRow("",            lblDoctor);
    form->addRow("Patient ID:", txtPatientId);
    form->addRow("Diagnosis:",  txtDiagnosis);
    form->addRow("Treatment:",  txtTreatment);
    form->addRow("Cost:",       txtCost);
    form->addRow("Date:",       txtDate);

    auto *btnSave   = new QPushButton("Save", this);
    auto *btnCancel = new QPushButton("Cancel", this);
    auto *btnRow = new QHBoxLayout();
    btnRow->addStretch(); btnRow->addWidget(btnCancel); btnRow->addWidget(btnSave);

    auto *root = new QVBoxLayout(this);
    root->addLayout(form);
    root->addLayout(btnRow);

    connect(btnSave,   &QPushButton::clicked, this, &MedicalRecordAddDialog::onSave);
    connect(btnCancel, &QPushButton::clicked, this, &QDialog::reject);
}

void MedicalRecordAddDialog::onSave() {
    QString pid   = txtPatientId->text().trimmed();
    QString diag  = txtDiagnosis->text().trimmed();
    QString treat = txtTreatment->text().trimmed();
    QString cost  = txtCost->text().trimmed();
    QString date  = txtDate->text().trimmed();

    Patient p;
    if (!p.isValidPatientId(pid.toStdString()) ||
        !p.patientIdAlreadyExists(pid.toStdString(), "Patient.txt")) {
        QMessageBox::warning(this, "Invalid", "Patient ID invalid or not found.");
        return;
    }
    if (diag.isEmpty() || treat.isEmpty() || cost.isEmpty() || date.isEmpty()) {
        QMessageBox::warning(this, "Missing", "All fields required.");
        return;
    }

    int recCount = 0;
    {
        std::ifstream f("MedicalRecords.txt");
        std::string l;
        while (std::getline(f, l)) if (l == "----------") recCount++;
    }
    int next = recCount + 1;
    std::string num = std::to_string(next);
    std::string recId = "R-" + std::string(4 - num.length(), '0') + num;

    std::ofstream out("MedicalRecords.txt", std::ios::app);
    out << "----------\n"
        << recId << "\n"
        << pid.toStdString() << "\n"
        << doctorId.toStdString() << "\n"
        << diag.toStdString() << "\n"
        << treat.toStdString() << "\n"
        << cost.toStdString() << "\n"
        << date.toStdString() << "\n";
    out.close();

    QMessageBox::information(this, "Saved",
                             "Record " + QString::fromStdString(recId) + " added.");
    accept();
}