#include "RoomAssignDialog.h"
#include "../../Patient.h"
#include "../../Room.h"

#include <QFormLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QMessageBox>
#include <QFont>
#include <sstream>
#include <iostream>

RoomAssignDialog::RoomAssignDialog(QWidget *parent) : QDialog(parent) {
    setWindowTitle("Assign Room");
    resize(550, 500);

    cmbType      = new QComboBox(this); cmbType->addItems({"general","private","icu","emergency"});
    txtAvailable = new QPlainTextEdit(this); txtAvailable->setReadOnly(true);
    QFont mono("Courier New"); mono.setStyleHint(QFont::Monospace);
    txtAvailable->setFont(mono);
    txtPatientId = new QLineEdit(this);
    txtRoomId    = new QLineEdit(this);
    txtAdmitDate = new QLineEdit(this); txtAdmitDate->setPlaceholderText("DD/MM/YYYY");

    auto *btnLoad   = new QPushButton("Show Available Rooms", this);
    auto *btnAssign = new QPushButton("Assign", this);
    auto *btnCancel = new QPushButton("Cancel", this);

    auto *form = new QFormLayout();
    form->addRow("Room Type:",  cmbType);
    form->addRow("Patient ID:", txtPatientId);
    form->addRow("Room ID:",    txtRoomId);
    form->addRow("Admit Date:", txtAdmitDate);

    auto *btnRow = new QHBoxLayout();
    btnRow->addStretch(); btnRow->addWidget(btnCancel); btnRow->addWidget(btnAssign);

    auto *root = new QVBoxLayout(this);
    root->addLayout(form);
    root->addWidget(btnLoad);
    root->addWidget(txtAvailable);
    root->addLayout(btnRow);

    connect(btnLoad,   &QPushButton::clicked, this, &RoomAssignDialog::onLoadAvailable);
    connect(btnAssign, &QPushButton::clicked, this, &RoomAssignDialog::onAssign);
    connect(btnCancel, &QPushButton::clicked, this, &QDialog::reject);
}

void RoomAssignDialog::onLoadAvailable() {
    Room r;
    std::stringstream buf;
    std::streambuf *old = std::cout.rdbuf(buf.rdbuf());
    r.displayAvailableRoomsByType(cmbType->currentText().toStdString());
    std::cout.rdbuf(old);
    txtAvailable->setPlainText(QString::fromStdString(buf.str()));
}

void RoomAssignDialog::onAssign() {
    QString pid  = txtPatientId->text().trimmed();
    QString rid  = txtRoomId->text().trimmed();
    QString type = cmbType->currentText();
    QString date = txtAdmitDate->text().trimmed();

    Patient p;
    Room r;

    if (!p.isValidPatientId(pid.toStdString()) ||
        !p.patientIdAlreadyExists(pid.toStdString(), "Patient.txt")) {
        QMessageBox::warning(this, "Invalid", "Bad Patient ID."); return;
    }
    if (!r.isValidID(rid.toStdString())) {
        QMessageBox::warning(this, "Invalid", "Bad Room ID format."); return;
    }
    if (!r.Check_occupied_by_roomID(rid.toStdString(), type.toStdString())) {
        QMessageBox::warning(this, "Unavailable", "Room not available."); return;
    }
    if (!r.isValidAdmitted(date.toStdString())) {
        QMessageBox::warning(this, "Invalid", "Bad admission date."); return;
    }

    r.updatePatientID(rid.toStdString(), pid.toStdString());
    r.updateOccupancy(rid.toStdString(), 1);
    r.updateDateAdmitted(rid.toStdString(), date.toStdString());

    QMessageBox::information(this, "Assigned",
                             "Patient " + pid + " assigned to room " + rid);
    accept();
}