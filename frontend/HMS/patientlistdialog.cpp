#include "PatientListDialog.h"
#include "../../Person.h"
#include "../../Patient.h"

#include <QVBoxLayout>
#include <QPushButton>
#include <QHeaderView>
#include <QTableWidgetItem>
#include <fstream>

PatientListDialog::PatientListDialog(QWidget *parent) : QDialog(parent) {
    setWindowTitle("All Patients");
    resize(1100, 500);

    table = new QTableWidget(this);
    QStringList headers = {"CNIC","Name","Age","Gender","Patient ID","Blood",
                           "Type","Height","Weight","Emergency","Status"};
    table->setColumnCount(headers.size());
    table->setHorizontalHeaderLabels(headers);
    table->horizontalHeader()->setStretchLastSection(true);

    auto *btnClose = new QPushButton("Close", this);

    auto *root = new QVBoxLayout(this);
    root->addWidget(table);
    root->addWidget(btnClose);

    loadPatients();
    connect(btnClose, &QPushButton::clicked, this, &QDialog::accept);
}

void PatientListDialog::loadPatients() {
    std::ifstream patFile("Patient.txt");
    if (!patFile) return;
    std::string line;
    int row = 0;
    while (std::getline(patFile, line)) {
        if (line != "----------") continue;
        Patient p; p.Load_From_File(patFile);

        QString name="-", age="-", gender="-";
        std::ifstream perFile("Person.txt");
        std::string sep;
        while (std::getline(perFile, sep)) {
            if (sep != "----------") continue;
            Person tmp; tmp.Load_From_File(perFile);
            if (tmp.Get_CNIC() == p.get_CNIC()) {
                name   = QString::fromStdString(tmp.Get_Name());
                age    = QString::number(tmp.Get_Age());
                gender = QString::fromStdString(tmp.Get_Gender());
                break;
            }
        }
        perFile.close();

        table->insertRow(row);
        table->setItem(row, 0,  new QTableWidgetItem(QString::fromStdString(p.get_CNIC())));
        table->setItem(row, 1,  new QTableWidgetItem(name));
        table->setItem(row, 2,  new QTableWidgetItem(age));
        table->setItem(row, 3,  new QTableWidgetItem(gender));
        table->setItem(row, 4,  new QTableWidgetItem(QString::fromStdString(p.getPatientId())));
        table->setItem(row, 5,  new QTableWidgetItem(QString::fromStdString(p.getBloodGroup())));
        table->setItem(row, 6,  new QTableWidgetItem(QString::fromStdString(p.getPatientType())));
        table->setItem(row, 7,  new QTableWidgetItem(QString::number(p.getHeight())));
        table->setItem(row, 8,  new QTableWidgetItem(QString::number(p.getWeight())));
        table->setItem(row, 9,  new QTableWidgetItem(QString::fromStdString(p.getEmergencyContact())));
        table->setItem(row, 10, new QTableWidgetItem(QString::fromStdString(p.getPatientStatus())));
        row++;
    }
    patFile.close();
}