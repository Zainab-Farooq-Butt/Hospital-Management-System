#include "PharmacyInventoryDialog.h"

#include <QVBoxLayout>
#include <QPushButton>
#include <QHeaderView>
#include <QTableWidgetItem>
#include <QColor>
#include <fstream>

PharmacyInventoryDialog::PharmacyInventoryDialog(Mode m, QWidget *parent) : QDialog(parent) {
    setWindowTitle(m == ALL ? "Pharmacy Inventory" : "Low Stock Medicines");
    resize(700, 480);

    table = new QTableWidget(this);
    QStringList h = {"Name","Dosage","Stock","Price"};
    table->setColumnCount(h.size());
    table->setHorizontalHeaderLabels(h);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
<<<<<<< HEAD
    table->horizontalHeader()->setStretchLastSection(true);
    table->verticalHeader()->setVisible(true);
=======
    table->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch); // Name stretches
    table->horizontalHeader()->setStretchLastSection(false);
    table->verticalHeader()->setVisible(false);
>>>>>>> origin/zainab
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setSelectionMode(QAbstractItemView::SingleSelection);

    auto *btnClose = new QPushButton("Close", this);

    auto *root = new QVBoxLayout(this);
    root->addWidget(table);
    root->addWidget(btnClose);

    std::ifstream f("Medicine.txt");
    std::string ln;
    int row = 0;
    while (std::getline(f, ln)) {
        if (ln != "----------") continue;
        std::string name, dosage, stockS, priceS;
        std::getline(f, name);
        std::getline(f, dosage);
        std::getline(f, stockS);
        std::getline(f, priceS);
        int stock = std::stoi(stockS);
        if (m == LOW_STOCK_ONLY && stock >= 10) continue;

        table->insertRow(row);
        auto *iName  = new QTableWidgetItem(QString::fromStdString(name));
        auto *iDos   = new QTableWidgetItem(QString::fromStdString(dosage));
        auto *iStock = new QTableWidgetItem(QString::number(stock));
        auto *iPrice = new QTableWidgetItem(QString::fromStdString(priceS));
        if (stock < 10) {
            iStock->setBackground(QColor(255, 200, 200));
        }
        table->setItem(row, 0, iName);
        table->setItem(row, 1, iDos);
        table->setItem(row, 2, iStock);
        table->setItem(row, 3, iPrice);
        row++;
    }

    connect(btnClose, &QPushButton::clicked, this, &QDialog::accept);
}