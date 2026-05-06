#include "DoctorListDialog.h"
#include "../../Person.h"
#include "../../Doctor.h"

#include <QVBoxLayout>
#include <QPushButton>
#include <QHeaderView>
#include <QTableWidgetItem>
#include <fstream>

DoctorListDialog::DoctorListDialog(QWidget *parent) : QDialog(parent) {
    setWindowTitle("All Doctors");
    resize(1100, 500);

    table = new QTableWidget(this);
    QStringList headers = {"CNIC","Name","Doctor ID","Specialization",
                           "Qualification","Experience","Fee","Availability","Status"};
    table->setColumnCount(headers.size());
    table->setHorizontalHeaderLabels(headers);
    table->horizontalHeader()->setStretchLastSection(true);

    auto *btnClose = new QPushButton("Close", this);

    auto *root = new QVBoxLayout(this);
    root->addWidget(table);
    root->addWidget(btnClose);

    loadDoctors();
    connect(btnClose, &QPushButton::clicked, this, &QDialog::accept);
}

void DoctorListDialog::loadDoctors() {
    std::ifstream df("Doctor.txt");
    if (!df) return;
    std::string line;
    int row = 0;
    while (std::getline(df, line)) {
        if (line != "----------") continue;
        Doctor d; d.Load_From_File(df);

        QString name = "-";
        std::ifstream pf("Person.txt");
        std::string sep;
        while (std::getline(pf, sep)) {
            if (sep != "----------") continue;
            Person p; p.Load_From_File(pf);
            if (p.Get_CNIC() == d.get_CNIC()) {
                name = QString::fromStdString(p.Get_Name());
                break;
            }
        }
        pf.close();

        table->insertRow(row);
        table->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(d.get_CNIC())));
        table->setItem(row, 1, new QTableWidgetItem(name));
        table->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(d.getDoctorId())));
        table->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(d.getSpecialization())));
        table->setItem(row, 4, new QTableWidgetItem(QString::fromStdString(d.getQualification())));
        table->setItem(row, 5, new QTableWidgetItem(QString::number(d.getExperienceYears())));
        table->setItem(row, 6, new QTableWidgetItem(QString::number(d.getConsultationFee())));
        table->setItem(row, 7, new QTableWidgetItem(QString::fromStdString(d.getAvailability())));
        table->setItem(row, 8, new QTableWidgetItem(QString::fromStdString(d.getAvailabilityStatus())));
        row++;
    }
    df.close();
}