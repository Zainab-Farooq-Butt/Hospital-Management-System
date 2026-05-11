#include "AmbulanceListDialog.h"
#include "../../Ambulance.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QTableWidgetItem>
#include <QMessageBox>
#include <QInputDialog>
#include <fstream>
#include <cstdio>

AmbulanceListDialog::AmbulanceListDialog(Mode m, QWidget *parent)
    : QDialog(parent), mode(m) {
    setWindowTitle(m == ALL ? "All Ambulances" : "Request Ambulance");
    resize(900, 480);

    table = new QTableWidget(this);
    QStringList h = {"Ambulance ID", "Available", "Driver ID", "Driver Name", "Plate", "Destination"};
    table->setColumnCount(h.size());
    table->setHorizontalHeaderLabels(h);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    table->horizontalHeader()->setSectionResizeMode(5, QHeaderView::Stretch); // Destination stretches
    table->horizontalHeader()->setStretchLastSection(false);
    table->verticalHeader()->setVisible(false);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setSelectionMode(QAbstractItemView::SingleSelection);

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
        // Resolve Driver Name
        QString driverName = QString::fromStdString(a.getDriverId()); // Default to ID
        std::ifstream fs("Staff.txt");
        std::string sln;
        while (std::getline(fs, sln)) {
            if (sln != "----------") continue;
            std::string scnic, sid, s1, s2, s3, s4, s5, s6;
            std::getline(fs, scnic); std::getline(fs, sid);
            if (sid == a.getDriverId()) {
                std::ifstream fp("Person.txt");
                std::string pln;
                while (std::getline(fp, pln)) {
                    if (pln != "----------") continue;
                    std::string pcnic, pname;
                    std::getline(fp, pcnic); std::getline(fp, pname);
                    if (pcnic == scnic) { driverName = QString::fromStdString(pname); break; }
                }
                break;
            }
        }

        table->insertRow(row);
        table->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(a.getAmbulanceId())));
        table->setItem(row, 1, new QTableWidgetItem(a.getAvailability() ? "Yes" : "No"));
        table->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(a.getDriverId())));
        table->setItem(row, 3, new QTableWidgetItem(driverName));
        table->setItem(row, 4, new QTableWidgetItem(QString::fromStdString(a.getLicensePlate())));
        table->setItem(row, 5, new QTableWidgetItem(QString::fromStdString(a.getDestination())));
        row++;
    }
}

void AmbulanceListDialog::onRequestSelected() {
    int r = table->currentRow();
    if (r < 0) { QMessageBox::warning(this, "Pick", "Select an ambulance."); return; }
    QString aid = table->item(r, 0)->text();

    bool ok;
    QString dest = QInputDialog::getText(this, "Dispatch", "Enter Destination:", QLineEdit::Normal, "", &ok);
    if (!ok || dest.trimmed().isEmpty()) return;

    std::ifstream fin("Ambulance.txt");
    std::ofstream fout("Ambulance_temp.txt");
    std::string ln;
    while (std::getline(fin, ln)) {
        if (ln != "----------") continue;
        std::string id, av, did, pl, d;
        std::getline(fin, id); std::getline(fin, av);
        std::getline(fin, did); std::getline(fin, pl); std::getline(fin, d);
        
        fout << "----------\n" << id << "\n";
        if (id == aid.toStdString()) {
            fout << "0\n"; // Mark unavailable
            fout << did << "\n" << pl << "\n" << dest.toStdString() << "\n";
        } else {
            fout << av << "\n" << did << "\n" << pl << "\n" << d << "\n";
        }
    }
    fin.close(); fout.close();
    std::remove("Ambulance.txt");
    std::rename("Ambulance_temp.txt", "Ambulance.txt");

    QMessageBox::information(this, "On its way!",
                             "Ambulance " + aid + " has been dispatched to " + dest + ".");
    load();
}