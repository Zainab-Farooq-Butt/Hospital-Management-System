#include "RoomAssignDialog.h"
#include "../../Patient.h"
#include "../../Room.h"

#include <QFormLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QMessageBox>
<<<<<<< HEAD
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
=======
#include <QHeaderView>
#include <QTableWidgetItem>
#include <fstream>

RoomAssignDialog::RoomAssignDialog(QWidget *parent) : QDialog(parent) {
    setWindowTitle("Assign Room");
    resize(600, 500);

    cmbType      = new QComboBox(this); cmbType->addItems({"general","private","icu","emergency"});
    
    table = new QTableWidget(this);
    table->setColumnCount(1);
    table->setHorizontalHeaderLabels({"Available Rooms"});
    table->horizontalHeader()->setStretchLastSection(true);
    table->verticalHeader()->setVisible(false);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);

>>>>>>> origin/zainab
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
<<<<<<< HEAD
    root->addWidget(txtAvailable);
=======
    root->addWidget(table);
>>>>>>> origin/zainab
    root->addLayout(btnRow);

    connect(btnLoad,   &QPushButton::clicked, this, &RoomAssignDialog::onLoadAvailable);
    connect(btnAssign, &QPushButton::clicked, this, &RoomAssignDialog::onAssign);
    connect(btnCancel, &QPushButton::clicked, this, &QDialog::reject);
}

void RoomAssignDialog::onLoadAvailable() {
<<<<<<< HEAD
    Room r;
    std::stringstream buf;
    std::streambuf *old = std::cout.rdbuf(buf.rdbuf());
    r.displayAvailableRoomsByType(cmbType->currentText().toStdString());
    std::cout.rdbuf(old);
    txtAvailable->setPlainText(QString::fromStdString(buf.str()));
=======
    table->setRowCount(0);
    std::string type = cmbType->currentText().toStdString();
    
    std::ifstream file("Room.txt");
    if (!file) return;

    std::string line, roomID, patientID, roomType;
    int isOccupied;
    std::string dateAdmitted, dateDischarged;
    int row = 0;

    while (std::getline(file, line)) {
        if (line == "----------") {
            std::getline(file, roomID);
            std::getline(file, patientID);
            std::getline(file, roomType);
            file >> isOccupied;
            file.ignore(); 
            std::getline(file, dateAdmitted);
            std::getline(file, dateDischarged);

            if (roomType == type && isOccupied == 0) {
                table->insertRow(row);
                table->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(roomID)));
                row++;
            }
        }
    }
    file.close();
    if (row == 0) {
        QMessageBox::information(this, "None", "No available rooms for this type.");
    }
>>>>>>> origin/zainab
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
<<<<<<< HEAD
        QMessageBox::warning(this, "Invalid", "Bad Patient ID."); return;
    }
    if (!r.isValidID(rid.toStdString())) {
        QMessageBox::warning(this, "Invalid", "Bad Room ID format."); return;
=======
        QMessageBox::warning(this, "Invalid", "Invalid Patient ID."); return;
    }
    if (!r.isValidID(rid.toStdString())) {
        QMessageBox::warning(this, "Invalid", "Invalid Room ID format."); return;
>>>>>>> origin/zainab
    }
    if (!r.Check_occupied_by_roomID(rid.toStdString(), type.toStdString())) {
        QMessageBox::warning(this, "Unavailable", "Room not available."); return;
    }
    if (!r.isValidAdmitted(date.toStdString())) {
<<<<<<< HEAD
        QMessageBox::warning(this, "Invalid", "Bad admission date."); return;
=======
        QMessageBox::warning(this, "Invalid", "Invalid admission date."); return;
>>>>>>> origin/zainab
    }

    r.updatePatientID(rid.toStdString(), pid.toStdString());
    r.updateOccupancy(rid.toStdString(), 1);
    r.updateDateAdmitted(rid.toStdString(), date.toStdString());

    QMessageBox::information(this, "Assigned",
                             "Patient " + pid + " assigned to room " + rid);
    accept();
}