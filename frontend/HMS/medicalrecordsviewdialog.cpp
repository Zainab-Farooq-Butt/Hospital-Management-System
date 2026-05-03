#include "MedicalRecordsViewDialog.h"

#include <QVBoxLayout>
#include <QPushButton>
#include <QHeaderView>
#include <QTableWidgetItem>
#include <fstream>

MedicalRecordsViewDialog::MedicalRecordsViewDialog(const QString &pid, QWidget *parent)
    : QDialog(parent) {
    setWindowTitle("Medical Records - " + pid);
    resize(900, 450);

    table = new QTableWidget(this);
    QStringList h = {"Record ID","Doctor","Diagnosis","Treatment","Cost","Date"};
    table->setColumnCount(h.size());
    table->setHorizontalHeaderLabels(h);
    table->horizontalHeader()->setStretchLastSection(true);

    auto *btnClose = new QPushButton("Close", this);

    auto *root = new QVBoxLayout(this);
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
        table->insertRow(row);
        table->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(rid)));
        table->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(d)));
        table->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(diag)));
        table->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(treat)));
        table->setItem(row, 4, new QTableWidgetItem(QString::fromStdString(cost)));
        table->setItem(row, 5, new QTableWidgetItem(QString::fromStdString(date)));
        row++;
    }

    connect(btnClose, &QPushButton::clicked, this, &QDialog::accept);
}