#include "AmbulanceListDialog.h"
#include "../../Ambulance.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QTableWidgetItem>
#include <QMessageBox>
#include <fstream>
#include <cstdio>

AmbulanceListDialog::AmbulanceListDialog(Mode m, QWidget *parent)
    : QDialog(parent), mode(m) {
    setWindowTitle(m == ALL ? "All Ambulances" : "Request Ambulance");
    resize(900, 480);

    table = new QTableWidget(this);
    QStringList h = {"Ambulance ID","Available","Driver","Plate","Address"};
    table->setColumnCount(h.size());
    table->setHorizontalHeaderLabels(h);
    table->horizontalHeader()->setStretchLastSection(true);

    btnRequest    = new QPushButton("Request Selected", this);
    auto *btnClose = new QPushButton("Close", this);
    btnRequest->setVisible(m == AVAILABLE_FOR_REQUEST);

    auto *btnRow = new QHBoxLayout();
    btnRow->addWidget(btnRequest); btnRow->addStretch(); btnRow->addWidget(btnClose);

    auto *root = new QVBoxLayout(this);
    root->addWidget(table);
    root->addLayout(btnRow);

    load();
    connect(btnRequest, &QPushButton::clicked, this, &AmbulanceListDialog::onRequestSelected);
    connect(btnClose,   &QPushButton::clicked, this, &QDialog::accept);
}

void AmbulanceListDialog::load() {
    table->setRowCount(0);
    std::ifstream f("Ambulance.txt");
    std::string ln;
    int row = 0;
    while (std::getline(f, ln)) {
        if (ln != "----------") continue;
        Ambulance a; a.loadFromFile(f);
        if (mode == AVAILABLE_FOR_REQUEST && !a.getAvailability()) continue;
        table->insertRow(row);
        table->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(a.getAmbulanceId())));
        table->setItem(row, 1, new QTableWidgetItem(a.getAvailability() ? "Yes" : "No"));
        table->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(a.getDriverId())));
        table->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(a.getLicensePlate())));
        table->setItem(row, 4, new QTableWidgetItem(QString::fromStdString(a.getAddress())));
        row++;
    }
}

void AmbulanceListDialog::onRequestSelected() {
    int r = table->currentRow();
    if (r < 0) { QMessageBox::warning(this, "Pick", "Select an ambulance."); return; }
    QString aid = table->item(r, 0)->text();

    std::ifstream fin("Ambulance.txt");
    std::ofstream fout("Ambulance_temp.txt");
    std::string ln;
    while (std::getline(fin, ln)) {
        if (ln != "----------") continue;
        std::string id, av, did, pl, addr;
        std::getline(fin, id); std::getline(fin, av);
        std::getline(fin, did); std::getline(fin, pl); std::getline(fin, addr);
        fout << "----------\n" << id << "\n";
        fout << ((id == aid.toStdString()) ? "0" : av) << "\n";
        fout << did << "\n" << pl << "\n" << addr << "\n";
    }
    fin.close(); fout.close();
    std::remove("Ambulance.txt");
    std::rename("Ambulance_temp.txt", "Ambulance.txt");

    QMessageBox::information(this, "On its way!",
                             "Ambulance " + aid + " has been dispatched.");
    load();
}