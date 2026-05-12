#include "MedicalRecordsViewDialog.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QHeaderView>
#include <QTableWidgetItem>
#include <QMessageBox>
#include <fstream>

MedicalRecordsViewDialog::MedicalRecordsViewDialog(const QString &pid, QWidget *parent, const QString &did_filter)
    : QDialog(parent) {
    setWindowTitle("Medical Records - " + pid);
    resize(900, 500);

    // Look up Patient Name
    QString patientName = "Unknown Patient";
    std::string targetCnic = "";
    {
        std::ifstream fpat("Patient.txt");
        std::string ln;
        while (std::getline(fpat, ln)) {
            if (ln != "----------") continue;
            std::string c, id, b, t, h, w, ec, s;
            std::getline(fpat, c); std::getline(fpat, id);
            if (id == pid.toStdString()) { targetCnic = c; break; }
        }
    }
    if (targetCnic.empty()) {
        QMessageBox::critical(this, "Not Found", "No patient record found for ID: " + pid);
        patientName = "Unknown Patient";
    } else {
        std::ifstream fper("Person.txt");
        std::string ln;
        while (std::getline(fper, ln)) {
            if (ln != "----------") continue;
            std::string c, n, a, g, r;
            std::getline(fper, c); std::getline(fper, n);
            if (c == targetCnic) { patientName = QString::fromStdString(n); break; }
        }
    }

    auto *lblTitle = new QLabel("Medical History: " + patientName + " (" + pid + ")", this);
    lblTitle->setObjectName("PageHeader");
    lblTitle->setStyleSheet("font-size: 18px; color: #0f172a; margin: 10px;");

    table = new QTableWidget(this);
    QStringList h = {"Record ID","Doctor","Diagnosis","Treatment","Cost","Date"};
    table->setColumnCount(h.size());
    table->setHorizontalHeaderLabels(h);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    table->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch); // Stretch Diagnosis
    table->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Stretch); // Stretch Treatment
    table->verticalHeader()->setVisible(false);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setSelectionMode(QAbstractItemView::SingleSelection);

    auto *btnClose = new QPushButton("Close", this);

    auto *root = new QVBoxLayout(this);
    root->addWidget(lblTitle);
    root->addWidget(table);
    root->addWidget(btnClose);

    std::ifstream f("MedicalRecords.txt");
    std::string ln;
    int row = 0;
    while (std::getline(f, ln)) {
        if (ln != "----------") continue;
        std::string rid, p, d, diag, treat, cost, date;
        std::getline(f, rid); std::getline(f, p); std::getline(f, d);
        std::getline(f, diag); std::getline(f, treat); std::getline(f, cost);
        std::getline(f, date);
        if (p != pid.toStdString()) continue;
        if (!did_filter.isEmpty() && d != did_filter.toStdString()) continue;

        // Resolve Doctor Name
        QString docName = QString::fromStdString(d); // Default to ID
        std::ifstream df("Doctor.txt");
        std::string dln;
        while (std::getline(df, dln)) {
            if (dln != "----------") continue;
            std::string dCnic, dId, spec, qual, exp, fee, avail, stat;
            std::getline(df, dCnic); std::getline(df, dId);
            std::getline(df, spec);  std::getline(df, qual);
            std::getline(df, exp);   std::getline(df, fee);
            std::getline(df, avail); std::getline(df, stat);
            
            if (dId == d) {
                std::ifstream pf("Person.txt");
                std::string pln;
                while (std::getline(pf, pln)) {
                    if (pln != "----------") continue;
                    std::string pCnic, pName, pAge, pGender, pRole;
                    std::getline(pf, pCnic); std::getline(pf, pName);
                    std::getline(pf, pAge);  std::getline(pf, pGender);
                    std::getline(pf, pRole);
                    if (pCnic == dCnic) {
                        docName = QString::fromStdString(pName);
                        break;
                    }
                }
                pf.close();
                break;
            }
        }
        df.close();

        table->insertRow(row);
        table->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(rid)));
        table->setItem(row, 1, new QTableWidgetItem(docName));
        table->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(diag)));
        table->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(treat)));
        table->setItem(row, 4, new QTableWidgetItem(QString::fromStdString(cost)));
        
        auto *dateItem = new QTableWidgetItem(QString::fromStdString(date));
        dateItem->setTextAlignment(Qt::AlignCenter);
        table->setItem(row, 5, dateItem);
        row++;
    }

    connect(btnClose, &QPushButton::clicked, this, &QDialog::accept);
}