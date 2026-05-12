#include "AppointmentListDialog.h"
#include "../../Patient.h"
#include "../../Doctor.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QHeaderView>
#include <QTableWidgetItem>
#include <QMessageBox>
#include <fstream>
#include <cstdio>

AppointmentListDialog::AppointmentListDialog(Filter f, const QString &id, QWidget *parent)
    : QDialog(parent), filter(f), filterId(id) {
    setWindowTitle("Appointments");
    resize(900, 500);

    table = new QTableWidget(this);
    QStringList h = {"Appt ID","Patient","Doctor","Date","Time","Reason","Status"};
    table->setColumnCount(h.size());
    table->setHorizontalHeaderLabels(h);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
<<<<<<< HEAD
    table->horizontalHeader()->setStretchLastSection(true);
    table->verticalHeader()->setVisible(true);
=======
    table->horizontalHeader()->setSectionResizeMode(5, QHeaderView::Stretch); // Reason stretches
    table->horizontalHeader()->setStretchLastSection(false);
    table->verticalHeader()->setVisible(false);
>>>>>>> origin/zainab
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setSelectionMode(QAbstractItemView::SingleSelection);

<<<<<<< HEAD
    auto *btnCancelSel = new QPushButton("Cancel Selected", this);
    auto *btnClose     = new QPushButton("Close", this);
=======
    btnCancelSel = new QPushButton("Cancel Selected", this);
    auto *btnClose = new QPushButton("Close", this);
>>>>>>> origin/zainab
    auto *btnRow = new QHBoxLayout();
    btnRow->addWidget(btnCancelSel); btnRow->addStretch(); btnRow->addWidget(btnClose);

    auto *root = new QVBoxLayout(this);
    root->addWidget(table);
    root->addLayout(btnRow);

    load();
<<<<<<< HEAD
=======
    connect(table, &QTableWidget::currentCellChanged, this, [this](int row, int, int, int) {
        if (row < 0) return;
        auto *statusItem = table->item(row, 6);
        bool isCancelled = statusItem && statusItem->text() == "Cancelled";
        btnCancelSel->setEnabled(!isCancelled);
        btnCancelSel->setToolTip(isCancelled ? "This appointment is already cancelled." : "");
    });
>>>>>>> origin/zainab
    connect(btnCancelSel, &QPushButton::clicked, this, &AppointmentListDialog::onCancelSelected);
    connect(btnClose,     &QPushButton::clicked, this, &QDialog::accept);
}

void AppointmentListDialog::load() {
    table->setRowCount(0);
    std::ifstream f("Appointment.txt");
    std::string ln;
    int row = 0;
    while (std::getline(f, ln)) {
        if (ln != "----------") continue;
        std::string aid, pid, did, date, time, reason, status;
        std::getline(f, aid); std::getline(f, pid); std::getline(f, did);
        std::getline(f, date); std::getline(f, time); std::getline(f, reason);
        std::getline(f, status);

        bool show = true;
        if (filter == BY_DOCTOR  && did != filterId.toStdString()) show = false;
        if (filter == BY_PATIENT && pid != filterId.toStdString()) show = false;
        if (!show) continue;

        // Resolve Names
        Patient p;
        Doctor d;
        QString pName = QString::fromStdString(p.getNameById(pid));
        QString dName = QString::fromStdString(d.getNameById(did));

        table->insertRow(row);
        table->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(aid)));
        table->setItem(row, 1, new QTableWidgetItem(pName));
        table->setItem(row, 2, new QTableWidgetItem(dName));
        table->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(date)));
        table->setItem(row, 4, new QTableWidgetItem(QString::fromStdString(time)));
        table->setItem(row, 5, new QTableWidgetItem(QString::fromStdString(reason)));
        table->setItem(row, 6, new QTableWidgetItem(QString::fromStdString(status)));
<<<<<<< HEAD
=======

        // Grey out cancelled rows
        if (status == "Cancelled") {
            for (int col = 0; col < 7; col++) {
                if (table->item(row, col))
                    table->item(row, col)->setForeground(QColor("#94a3b8"));
            }
        }
>>>>>>> origin/zainab
        row++;
    }
}

void AppointmentListDialog::onCancelSelected() {
    int r = table->currentRow();
    if (r < 0) { QMessageBox::warning(this, "Pick", "Select a row first."); return; }
    QString targetId = table->item(r, 0)->text();
<<<<<<< HEAD
=======
    QString currentStatus = table->item(r, 6)->text();

    if (currentStatus == "Cancelled") {
        QMessageBox::information(this, "Already Cancelled", "This appointment is already cancelled.");
        return;
    }
>>>>>>> origin/zainab

    std::ifstream fin("Appointment.txt");
    std::ofstream fout("Appointment_temp.txt");
    std::string ln;
    while (std::getline(fin, ln)) {
        if (ln != "----------") continue;
        std::string aid, pid, did, date, time, reason, status;
        std::getline(fin, aid); std::getline(fin, pid); std::getline(fin, did);
        std::getline(fin, date); std::getline(fin, time); std::getline(fin, reason);
        std::getline(fin, status);
        fout << "----------\n" << aid << "\n" << pid << "\n" << did << "\n"
             << date << "\n" << time << "\n" << reason << "\n"
             << (aid == targetId.toStdString() ? "Cancelled" : status) << "\n";
    }
    fin.close(); fout.close();
    std::remove("Appointment.txt");
    std::rename("Appointment_temp.txt", "Appointment.txt");

    QMessageBox::information(this, "Cancelled", "Appointment " + targetId + " cancelled.");
    load();
}