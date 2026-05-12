#include "BillingDialog.h"
#include "../../Billing.h"
#include "../../Patient.h"
<<<<<<< HEAD
=======
#include "../../Doctor.h"
>>>>>>> origin/zainab

#include <QFormLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
<<<<<<< HEAD
#include <QFont>
#include <sstream>
#include <iostream>

BillingDialog::BillingDialog(Mode m, QWidget *parent) : QDialog(parent), mode(m) {
    resize(700, 500);

    txtPatientId = new QLineEdit(this);
    txtOutput    = new QPlainTextEdit(this); txtOutput->setReadOnly(true);
    QFont mono("Courier New"); mono.setStyleHint(QFont::Monospace);
    txtOutput->setFont(mono);
=======
#include <QHeaderView>
#include <QFont>
#include <fstream>
#include <sstream>
#include <iostream>

BillingDialog::BillingDialog(Mode m, QWidget *parent, const QString &preloadPatientId)
    : QDialog(parent), mode(m) {
    resize(1100, 500);

    lblPatientId = new QLabel("Patient ID:", this);
    txtPatientId = new QLineEdit(this);
    
    table = new QTableWidget(this);
    QStringList h = {"Bill ID","Patient","Doctor","Record ID","Doc Fee","Room Fee","Treat Cost","Total","Remains","Status","Date"};
    table->setColumnCount(h.size());
    table->setHorizontalHeaderLabels(h);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    table->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch); // Patient stretches
    table->horizontalHeader()->setStretchLastSection(false);
    table->verticalHeader()->setVisible(false);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setSelectionMode(QAbstractItemView::SingleSelection);

>>>>>>> origin/zainab
    btnAction = new QPushButton(this);
    auto *btnClose = new QPushButton("Close", this);

    switch (m) {
<<<<<<< HEAD
    case SHOW_ONE:      setWindowTitle("Show Patient Bill"); btnAction->setText("Show"); break;
    case SHOW_ALL:      setWindowTitle("All Bills"); btnAction->setText("Show All");
        txtPatientId->setEnabled(false); break;
=======
    case SHOW_ONE:
        setWindowTitle("My Bill");
        btnAction->hide();
        if (!preloadPatientId.isEmpty()) {
            // Called from Patient Dashboard — hide input, auto-load
            lblPatientId->hide();
            txtPatientId->hide();
            loadBills(preloadPatientId.toStdString());
        }
        break;
    case SHOW_ALL:
        setWindowTitle("All Bills");
        btnAction->hide();
        lblPatientId->hide();
        txtPatientId->hide();
        loadBills();
        break;
>>>>>>> origin/zainab
    case SET_BILL:      setWindowTitle("Set Patient Bill"); btnAction->setText("Set"); break;
    case UPDATE_STATUS: setWindowTitle("Update Bill Status"); btnAction->setText("Update"); break;
    }

<<<<<<< HEAD
    auto *form = new QFormLayout();
    form->addRow("Patient ID:", txtPatientId);
=======
    auto *form = new QHBoxLayout();
    form->addWidget(lblPatientId);
    form->addWidget(txtPatientId);
>>>>>>> origin/zainab

    auto *btnRow = new QHBoxLayout();
    btnRow->addWidget(btnAction); btnRow->addStretch(); btnRow->addWidget(btnClose);

    auto *root = new QVBoxLayout(this);
<<<<<<< HEAD
    root->addLayout(form);
    root->addWidget(txtOutput);
    root->addLayout(btnRow);

=======
    if (m != SHOW_ALL) root->addLayout(form);
    root->addWidget(table);
    root->addLayout(btnRow);

    connect(txtPatientId, &QLineEdit::returnPressed, this, &BillingDialog::onAction);
>>>>>>> origin/zainab
    connect(btnAction, &QPushButton::clicked, this, &BillingDialog::onAction);
    connect(btnClose,  &QPushButton::clicked, this, &QDialog::accept);
}

void BillingDialog::onAction() {
    QString pid = txtPatientId->text().trimmed();
<<<<<<< HEAD
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
=======
    if (pid.isEmpty() && mode != SHOW_ALL) return;

    if (mode == SHOW_ONE) {
        loadBills(pid.toStdString());
    } else if (mode == SET_BILL || mode == UPDATE_STATUS) {
        Billing b;
        Patient p;
        if (!p.isValidPatientId(pid.toStdString()) || !p.patientIdAlreadyExists(pid.toStdString(), "Patient.txt")) {
            QMessageBox::warning(this, "Invalid", "Invalid patient ID."); return;
        }
        
        if (mode == SET_BILL) b.setBilling("ADMIN", pid.toStdString());
        else b.updateStatus("ADMIN", pid.toStdString());
        
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
        table->setItem(row, 0,  new QTableWidgetItem(QString::fromStdString(bid)));
        table->setItem(row, 1,  new QTableWidgetItem(QString::fromStdString(pHelper.getNameById(pid))));
        table->setItem(row, 2,  new QTableWidgetItem(QString::fromStdString(dHelper.getNameById(did))));
        table->setItem(row, 3,  new QTableWidgetItem(QString::fromStdString(rid)));
        table->setItem(row, 4,  new QTableWidgetItem(QString::number(df)));
        table->setItem(row, 5,  new QTableWidgetItem(QString::number(rf)));
        table->setItem(row, 6,  new QTableWidgetItem(QString::number(tc)));
        table->setItem(row, 7,  new QTableWidgetItem(QString::number(tot)));
        table->setItem(row, 8,  new QTableWidgetItem(QString::number(rem)));
        table->setItem(row, 9,  new QTableWidgetItem(QString::fromStdString(stat)));
        table->setItem(row, 10, new QTableWidgetItem(QString::fromStdString(date)));
        row++;
    }
    infile.close();
>>>>>>> origin/zainab
}