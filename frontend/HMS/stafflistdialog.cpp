#include "StaffListDialog.h"
#include "../../Person.h"
#include "../../Staff.h"

#include <QVBoxLayout>
#include <QPushButton>
#include <QHeaderView>
#include <QTableWidgetItem>
#include <fstream>

StaffListDialog::StaffListDialog(QWidget *parent) : QDialog(parent) {
    setWindowTitle("All Staff");
    resize(1100, 500);

    table = new QTableWidget(this);
    QStringList headers = {"CNIC","Name","Age","Staff ID","Department","Job","Shift","Salary","Joined","Status"};
    table->setColumnCount(headers.size());
    table->setHorizontalHeaderLabels(headers);
    table->horizontalHeader()->setStretchLastSection(true);

    auto *btnClose = new QPushButton("Close", this);

    auto *root = new QVBoxLayout(this);
    root->addWidget(table);
    root->addWidget(btnClose);

    loadStaff();
    connect(btnClose, &QPushButton::clicked, this, &QDialog::accept);
}

void StaffListDialog::loadStaff() {
    std::ifstream sf("Staff.txt");
    if (!sf) return;
    std::string line;
    int row = 0;
    while (std::getline(sf, line)) {
        if (line != "----------") continue;
        Staff s; s.Load_From_File(sf);

        QString name="-", age="-";
        std::ifstream pf("Person.txt");
        std::string sep;
        while (std::getline(pf, sep)) {
            if (sep != "----------") continue;
            Person p; p.Load_From_File(pf);
            if (p.Get_CNIC() == s.get_CNIC()) {
                name = QString::fromStdString(p.Get_Name());
                age  = QString::number(p.Get_Age());
                break;
            }
        }
        pf.close();

        table->insertRow(row);
        table->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(s.get_CNIC())));
        table->setItem(row, 1, new QTableWidgetItem(name));
        table->setItem(row, 2, new QTableWidgetItem(age));
        table->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(s.getStaffId())));
        table->setItem(row, 4, new QTableWidgetItem(QString::fromStdString(s.getDepartment())));
        table->setItem(row, 5, new QTableWidgetItem(QString::fromStdString(s.getJobTitle())));
        table->setItem(row, 6, new QTableWidgetItem(QString::fromStdString(s.getShift())));
        table->setItem(row, 7, new QTableWidgetItem(QString::number(s.getSalary())));
        table->setItem(row, 8, new QTableWidgetItem(QString::fromStdString(s.getJoiningDate())));
        table->setItem(row, 9, new QTableWidgetItem(QString::fromStdString(s.getEmploymentStatus())));
        row++;
    }
    sf.close();
}