#include "PharmacyRecordsDialog.h"

#include <QVBoxLayout>
#include <QPushButton>
#include <QHeaderView>
#include <QTableWidgetItem>
#include <fstream>

PharmacyRecordsDialog::PharmacyRecordsDialog(Mode m, const QString &pid, QWidget *parent)
    : QDialog(parent) {
    setWindowTitle(m == ALL_PRESCRIPTIONS ? "All Prescriptions" : "Patient Pharmacy Records");
    resize(700, 450);

    table = new QTableWidget(this);
    QStringList h = {"Patient ID","Medicine","Quantity","Total Cost"};
    table->setColumnCount(h.size());
    table->setHorizontalHeaderLabels(h);
    table->horizontalHeader()->setStretchLastSection(true);

    auto *btnClose = new QPushButton("Close", this);

    auto *root = new QVBoxLayout(this);
    root->addWidget(table);
    root->addWidget(btnClose);

    std::ifstream f("Prescriptions.txt");
    std::string ln;
    int row = 0;
    while (std::getline(f, ln)) {
        if (ln != "----------") continue;
        std::string p, med, qty, cost;
        std::getline(f, p);
        std::getline(f, med);
        std::getline(f, qty);
        std::getline(f, cost);
        if (m == BY_PATIENT && p != pid.toStdString()) continue;

        table->insertRow(row);
        table->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(p)));
        table->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(med)));
        table->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(qty)));
        table->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(cost)));
        row++;
    }

    connect(btnClose, &QPushButton::clicked, this, &QDialog::accept);
}