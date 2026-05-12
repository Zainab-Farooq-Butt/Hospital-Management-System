#include "BillingDialog.h"
#include "../../Billing.h"
#include "../../Patient.h"
#include "../../Doctor.h"


#include <QInputDialog>
#include "../../MedicalRecords.h"
#include "../../Room.h"

#include <QFormLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QHeaderView>
#include <QFont>
#include <fstream>
#include <sstream>
#include <iostream>

BillingDialog::BillingDialog(Mode m, QWidget* parent, const QString& patientId)
    : QDialog(parent), mode(m) {
    resize(1100, 500);

    lblPatientId = new QLabel("Patient ID:", this);
    txtPatientId = new QLineEdit(this);
    if (!patientId.isEmpty()) {
        txtPatientId->setText(patientId);
        txtPatientId->setReadOnly(true);
    }


    table = new QTableWidget(this);
    QStringList h = { "Bill ID","Patient","Doctor","Record ID","Doc Fee","Room Fee","Treat Cost","Total","Remains","Status","Date" };
    table->setColumnCount(h.size());
    table->setHorizontalHeaderLabels(h);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    table->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch); // Patient stretches
    table->horizontalHeader()->setStretchLastSection(false);
    table->verticalHeader()->setVisible(false);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setSelectionMode(QAbstractItemView::SingleSelection);

    btnAction = new QPushButton(this);
    btnAction->setAutoDefault(false);
    btnAction->setDefault(false);

    auto* btnClose = new QPushButton("Close", this);
    btnClose->setAutoDefault(false);

    switch (m) {
    case SHOW_ONE:
        setWindowTitle("Show Patient Bill");
        btnAction->hide();
        break;
    case SHOW_ALL:
        setWindowTitle("All Bills");
        btnAction->hide();
        lblPatientId->hide();
        txtPatientId->hide();
        loadBills();
        break;
    case SET_BILL:      setWindowTitle("Set Patient Bill"); btnAction->setText("Set"); break;
    case UPDATE_STATUS: setWindowTitle("Update Bill Status"); btnAction->setText("Update"); break;
    }

    auto* form = new QHBoxLayout();
    form->addWidget(lblPatientId);
    form->addWidget(txtPatientId);

    auto* btnRow = new QHBoxLayout();
    btnRow->addWidget(btnAction); btnRow->addStretch(); btnRow->addWidget(btnClose);

    auto* root = new QVBoxLayout(this);
    if (m != SHOW_ALL) root->addLayout(form);
    root->addWidget(table);
    root->addLayout(btnRow);

    connect(txtPatientId, &QLineEdit::returnPressed, this, &BillingDialog::onAction);
    connect(btnAction, &QPushButton::clicked, this, &BillingDialog::onAction);
    connect(btnClose, &QPushButton::clicked, this, &QDialog::accept);

    if (!patientId.isEmpty()) {
        onAction();
    }
}

void BillingDialog::onAction() {
    table->setRowCount(0); // Clear previous results immediately
    QString pid = txtPatientId->text().trimmed();
    if (pid.isEmpty() && mode != SHOW_ALL) return;

    if (mode == SHOW_ONE) {
        Patient p;
        if (!p.isValidPatientId(pid.toStdString()) || !p.patientIdAlreadyExists(pid.toStdString(), "Patient.txt")) {
            QMessageBox::warning(this, "Invalid", "Patient ID not found."); return;
        }
        loadBills(pid.toStdString());

    }
    else if (mode == SET_BILL) {
        Patient p;
        if (!p.isValidPatientId(pid.toStdString()) || !p.patientIdAlreadyExists(pid.toStdString(), "Patient.txt")) {
            QMessageBox::warning(this, "Invalid", "Invalid patient ID."); return;
        }

        loadBills(pid.toStdString()); // Show existing bills during search
        if (sender() == txtPatientId) return; // Search only if triggered by Enter key

        bool ok;
        QString recId = QInputDialog::getText(this, "Record ID",
            "Enter Record ID (format R-0001):", QLineEdit::Normal, "", &ok);
        if (!ok || recId.isEmpty()) return;
        
        // ... rest of SET_BILL logic remains the same ...
        MedicalRecords m;
        if (!m.isValidRecordId(recId.toStdString())) {
            QMessageBox::warning(this, "Invalid", "Invalid Record ID format."); return;
        }
        if (!m.recordIdAlreadyExists(recId.toStdString())) {
            QMessageBox::warning(this, "Invalid", "Record ID doesn't exist."); return;
        }

        Billing b;
        if (!b.Patient_has_RID(pid.toStdString(), recId.toStdString())) {
            QMessageBox::warning(this, "Invalid",
                pid + " has no " + recId); return;
        }

        m.fetchFromFile(recId.toStdString());

        b.loadCounterFromFile("Billing.txt");
        std::string billId = b.generateBillId();
        std::string doctorId = m.getDoctorId();
        double treatmentCost = m.getTreatmentCost();

        Doctor d;
        double doctorFee = d.fetchDoctorFee(doctorId, "Doctor.txt");
        Room r;
        double roomFee = r.fetchRoomFee(pid.toStdString());
        double totalAmount = doctorFee + roomFee + treatmentCost;

        QString summary = QString(
            "Bill ID: %1\nPatient ID: %2\nDoctor ID: %3\nRecord ID: %4\n"
            "Doctor Fee: %5\nTreatment Cost: %6\nRoom Fee: %7\nTotal: %8")
            .arg(QString::fromStdString(billId), pid,
                QString::fromStdString(doctorId), recId)
            .arg(doctorFee, 0, 'f', 2)
            .arg(treatmentCost, 0, 'f', 2)
            .arg(roomFee, 0, 'f', 2)
            .arg(totalAmount, 0, 'f', 2);

        double amountReceived = QInputDialog::getDouble(this, "Payment",
            summary + "\n\nEnter Amount Received:", 0, 0, 100000000, 2, &ok);
        if (!ok) return;
        if (amountReceived <= 0) {
            QMessageBox::warning(this, "Invalid", "Amount must be positive."); return;
        }

        std::string status;
        double remainingAmount;
        if (amountReceived >= totalAmount) {
            double change = amountReceived - totalAmount;
            if (change > 0)
                QMessageBox::information(this, "Change",
                    "Change: " + QString::number(change));
            status = "Paid";
            remainingAmount = 0;
        }
        else {
            status = "Partially Paid";
            remainingAmount = totalAmount - amountReceived;
            QMessageBox::information(this, "Remaining",
                "Remaining Amount: " + QString::number(remainingAmount));
        }

        QString dateStr = QInputDialog::getText(this, "Billing Date",
            "Enter Billing Date (format 1/1/2000):", QLineEdit::Normal, "", &ok);
        if (!ok || dateStr.isEmpty()) return;
        if (!b.isValidBillDate(dateStr.toStdString())) {
            QMessageBox::warning(this, "Invalid", "Invalid date format."); return;
        }
        if (Billing::isDateBefore(dateStr.toStdString(), m.getDate())) {
            QMessageBox::warning(this, "Invalid", "Bill date cannot be before Medical Record date (" + QString::fromStdString(m.getDate()) + ").");
            return;
        }

        Billing newBill(billId, pid.toStdString(), doctorId, recId.toStdString(),
            doctorFee, roomFee, treatmentCost, remainingAmount,
            status, dateStr.toStdString());
        newBill.saveToFile();

        QMessageBox::information(this, "Success", "Bill generated successfully!");
        loadBills(pid.toStdString());

    }
    else if (mode == UPDATE_STATUS) {
        Patient p;
        if (!p.isValidPatientId(pid.toStdString()) || !p.patientIdAlreadyExists(pid.toStdString(), "Patient.txt")) {
            QMessageBox::warning(this, "Invalid", "Invalid patient ID."); return;
        }

        // Check if patient has any bills
        {
            std::ifstream infile("Billing.txt");
            bool found = false;
            if (infile.is_open()) {
                std::string sep, bId, pId, skip;
                double d;
                while (std::getline(infile, sep)) {
                    std::getline(infile, bId);
                    std::getline(infile, pId);
                    std::getline(infile, skip);
                    std::getline(infile, skip);
                    infile >> d >> d >> d >> d >> d;
                    infile.ignore();
                    std::getline(infile, skip);
                    std::getline(infile, skip);
                    if (pId == pid.toStdString()) { found = true; break; }
                }
                infile.close();
            }
            if (!found) {
                QMessageBox::warning(this, "Not Found",
                    "No bills for Patient ID: " + pid);
                return;
            }
        }

        loadBills(pid.toStdString());   // show patient's bills in the table
        if (sender() == txtPatientId) return; // Search only if triggered by Enter key

        bool ok;
        QString billId = QInputDialog::getText(this, "Bill ID",
            "Enter Bill ID to update:", QLineEdit::Normal, "", &ok);
        if (!ok || billId.isEmpty()) return;

        Billing b;
        if (!b.isValidBillId(billId.toStdString())) {
            QMessageBox::warning(this, "Invalid", "Invalid Bill ID format."); return;
        }
        if (!b.billIdAlreadyExists(billId.toStdString())) {
            QMessageBox::warning(this, "Not Found", "Bill ID doesn't exist."); return;
        }
        if (!b.Patient_has_BID(pid.toStdString(), billId.toStdString())) {
            QMessageBox::warning(this, "Mismatch", pid + " has no " + billId); return;
        }

        // Read all bills from file
        std::string bIds[100], pIds[100], dIds[100], rIds[100], stats[100], dates[100];
        double roomfees[100], docfees[100], tmentcosts[100], totals[100], ramounts[100];
        std::string sep;
        int count = 0;

        std::ifstream infile("Billing.txt");
        if (!infile.is_open()) {
            QMessageBox::warning(this, "Error", "Error opening file."); return;
        }
        while (std::getline(infile, sep)) {
            std::getline(infile, bIds[count]);
            std::getline(infile, pIds[count]);
            std::getline(infile, dIds[count]);
            std::getline(infile, rIds[count]);
            infile >> docfees[count] >> roomfees[count] >> tmentcosts[count]
                >> totals[count] >> ramounts[count];
                infile.ignore();
                std::getline(infile, stats[count]);
                std::getline(infile, dates[count]);
                count++;
        }
        infile.close();

        int index = -1;
        for (int i = 0; i < count; i++) {
            if (billId.toStdString() == bIds[i]) { index = i; break; }
        }
        if (index == -1) {
            QMessageBox::warning(this, "Error", "Bill not found in file."); return;
        }
        if (stats[index] == "Paid") {
            QMessageBox::information(this, "Already Paid",
                "Bill is already paid. Cannot update."); return;
        }

        double amountReceived = QInputDialog::getDouble(this, "Payment",
            "Remaining: " + QString::number(ramounts[index], 'f', 2) +
            "\n\nEnter Amount Received:", 0, 0, 100000000, 2, &ok);
        if (!ok) return;
        if (amountReceived <= 0) {
            QMessageBox::warning(this, "Invalid", "Amount must be positive."); return;
        }

        if (amountReceived >= ramounts[index]) {
            double change = amountReceived - ramounts[index];
            if (change > 0)
                QMessageBox::information(this, "Change",
                    "Change: " + QString::number(change));
            stats[index] = "Paid";
            ramounts[index] = 0;
        }
        else {
            stats[index] = "Partially Paid";
            ramounts[index] -= amountReceived;
            QMessageBox::information(this, "Remaining",
                "Remaining: " + QString::number(ramounts[index]));
        }

        std::ofstream outfile("Billing.txt");
        if (!outfile.is_open()) {
            QMessageBox::warning(this, "Error", "Error writing to file."); return;
        }
        for (int i = 0; i < count; i++) {
            outfile << "-----------" << std::endl;
            outfile << bIds[i] << std::endl;
            outfile << pIds[i] << std::endl;
            outfile << dIds[i] << std::endl;
            outfile << rIds[i] << std::endl;
            outfile << docfees[i] << std::endl;
            outfile << roomfees[i] << std::endl;
            outfile << tmentcosts[i] << std::endl;
            outfile << totals[i] << std::endl;
            outfile << ramounts[i] << std::endl;
            outfile << stats[i] << std::endl;
            outfile << dates[i] << std::endl;
        }
        outfile.close();

        QMessageBox::information(this, "Success", "Status updated successfully!");
        loadBills(pid.toStdString());
    }
}


void BillingDialog::loadBills(const std::string& filterPid) {
    table->setRowCount(0);
    std::ifstream infile("Billing.txt");
    if (!infile.is_open()) return;

    Patient pHelper;
    Doctor dHelper;
    std::string sep;
    int row = 0;
    while (std::getline(infile, sep)) {
        if (sep.find("---") == std::string::npos) continue;

        std::string bid, pid, did, rid, stat, date;
        double df, rf, tc, tot, rem;

        std::getline(infile, bid);
        std::getline(infile, pid);
        std::getline(infile, did);
        std::getline(infile, rid);
        infile >> df >> rf >> tc >> tot >> rem;
        infile.ignore(1000, '\n');
        std::getline(infile, stat);
        std::getline(infile, date);

        if (!filterPid.empty() && pid != filterPid) continue;

        table->insertRow(row);
        table->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(bid)));
        table->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(pHelper.getNameById(pid))));
        table->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(dHelper.getNameById(did))));
        table->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(rid)));
        table->setItem(row, 4, new QTableWidgetItem(QString::number(df)));
        table->setItem(row, 5, new QTableWidgetItem(QString::number(rf)));
        table->setItem(row, 6, new QTableWidgetItem(QString::number(tc)));
        table->setItem(row, 7, new QTableWidgetItem(QString::number(tot)));
        table->setItem(row, 8, new QTableWidgetItem(QString::number(rem)));
        table->setItem(row, 9, new QTableWidgetItem(QString::fromStdString(stat)));
        table->setItem(row, 10, new QTableWidgetItem(QString::fromStdString(date)));
        row++;
    }
    infile.close();
}