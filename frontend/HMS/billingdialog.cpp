#include "BillingDialog.h"
#include "../../Billing.h"
#include "../../Patient.h"

#include <QFormLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QFont>
#include <sstream>
#include <iostream>

BillingDialog::BillingDialog(Mode m, QWidget *parent) : QDialog(parent), mode(m) {
    resize(700, 500);

    txtPatientId = new QLineEdit(this);
    txtOutput    = new QPlainTextEdit(this); txtOutput->setReadOnly(true);
    QFont mono("Courier New"); mono.setStyleHint(QFont::Monospace);
    txtOutput->setFont(mono);
    btnAction = new QPushButton(this);
    auto *btnClose = new QPushButton("Close", this);

    switch (m) {
    case SHOW_ONE:      setWindowTitle("Show Patient Bill"); btnAction->setText("Show"); break;
    case SHOW_ALL:      setWindowTitle("All Bills"); btnAction->setText("Show All");
        txtPatientId->setEnabled(false); break;
    case SET_BILL:      setWindowTitle("Set Patient Bill"); btnAction->setText("Set"); break;
    case UPDATE_STATUS: setWindowTitle("Update Bill Status"); btnAction->setText("Update"); break;
    }

    auto *form = new QFormLayout();
    form->addRow("Patient ID:", txtPatientId);

    auto *btnRow = new QHBoxLayout();
    btnRow->addWidget(btnAction); btnRow->addStretch(); btnRow->addWidget(btnClose);

    auto *root = new QVBoxLayout(this);
    root->addLayout(form);
    root->addWidget(txtOutput);
    root->addLayout(btnRow);

    connect(btnAction, &QPushButton::clicked, this, &BillingDialog::onAction);
    connect(btnClose,  &QPushButton::clicked, this, &QDialog::accept);
}

void BillingDialog::onAction() {
    QString pid = txtPatientId->text().trimmed();
    Billing b;

    std::stringstream buf;
    std::streambuf *old = std::cout.rdbuf(buf.rdbuf());

    if (mode == SHOW_ALL) {
        b.displayAllPatientBills();
    } else {
        Patient p;
        if (!p.isValidPatientId(pid.toStdString()) ||
            !p.patientIdAlreadyExists(pid.toStdString(), "Patient.txt")) {
            std::cout.rdbuf(old);
            QMessageBox::warning(this, "Invalid", "Bad patient ID."); return;
        }
        switch (mode) {
        case SHOW_ONE:      b.searchByPatientId(pid.toStdString()); break;
        case SET_BILL:      b.setBilling("ADMIN", pid.toStdString()); break;
        case UPDATE_STATUS: b.updateStatus("ADMIN", pid.toStdString()); break;
        default: break;
        }
    }
    std::cout.rdbuf(old);
    txtOutput->setPlainText(QString::fromStdString(buf.str()));
}