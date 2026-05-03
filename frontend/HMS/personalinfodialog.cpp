#include "PersonalInfoDialog.h"

#include <QVBoxLayout>
#include <QPushButton>
#include <QFont>
#include <fstream>
#include <string>

PersonalInfoDialog::PersonalInfoDialog(Mode m, const QString &cnic, QWidget *parent)
    : QDialog(parent) {
    setWindowTitle("Personal Information");
    resize(520, 480);

    txtInfo = new QPlainTextEdit(this);
    txtInfo->setReadOnly(true);
    QFont mono("Courier New"); mono.setStyleHint(QFont::Monospace);
    txtInfo->setFont(mono);

    auto *btnClose = new QPushButton("Close", this);

    auto *root = new QVBoxLayout(this);
    root->addWidget(txtInfo);
    root->addWidget(btnClose);

    QString out;
    {
        std::ifstream f("Person.txt");
        std::string ln;
        while (std::getline(f, ln)) {
            if (ln != "----------") continue;
            std::string c, n, age, g, ph, em, ad;
            std::getline(f, c); std::getline(f, n); std::getline(f, age);
            std::getline(f, g); std::getline(f, ph); std::getline(f, em); std::getline(f, ad);
            if (c == cnic.toStdString()) {
                out += "--- Personal ---\n";
                out += "CNIC    : " + QString::fromStdString(c) + "\n";
                out += "Name    : " + QString::fromStdString(n) + "\n";
                out += "Age     : " + QString::fromStdString(age) + "\n";
                out += "Gender  : " + QString::fromStdString(g) + "\n";
                out += "Phone   : " + QString::fromStdString(ph) + "\n";
                out += "Email   : " + QString::fromStdString(em) + "\n";
                out += "Address : " + QString::fromStdString(ad) + "\n\n";
                break;
            }
        }
    }
    if (m == PATIENT_VIEW) {
        std::ifstream f("Patient.txt");
        std::string ln;
        while (std::getline(f, ln)) {
            if (ln != "----------") continue;
            std::string c, pid, blood, type, h, w, ec, st;
            std::getline(f, c); std::getline(f, pid); std::getline(f, blood);
            std::getline(f, type); std::getline(f, h); std::getline(f, w);
            std::getline(f, ec); std::getline(f, st);
            if (c == cnic.toStdString()) {
                out += "--- Patient ---\n";
                out += "Patient ID  : " + QString::fromStdString(pid) + "\n";
                out += "Blood       : " + QString::fromStdString(blood) + "\n";
                out += "Type        : " + QString::fromStdString(type) + "\n";
                out += "Height      : " + QString::fromStdString(h) + "\n";
                out += "Weight      : " + QString::fromStdString(w) + "\n";
                out += "Emergency   : " + QString::fromStdString(ec) + "\n";
                out += "Status      : " + QString::fromStdString(st) + "\n";
                break;
            }
        }
    } else {
        std::ifstream f("Doctor.txt");
        std::string ln;
        while (std::getline(f, ln)) {
            if (ln != "----------") continue;
            std::string c, did, sp, qu, ex, fe, av, st;
            std::getline(f, c); std::getline(f, did); std::getline(f, sp);
            std::getline(f, qu); std::getline(f, ex); std::getline(f, fe);
            std::getline(f, av); std::getline(f, st);
            if (c == cnic.toStdString()) {
                out += "--- Doctor ---\n";
                out += "Doctor ID      : " + QString::fromStdString(did) + "\n";
                out += "Specialization : " + QString::fromStdString(sp) + "\n";
                out += "Qualification  : " + QString::fromStdString(qu) + "\n";
                out += "Experience     : " + QString::fromStdString(ex) + " yrs\n";
                out += "Fee            : " + QString::fromStdString(fe) + "\n";
                out += "Availability   : " + QString::fromStdString(av) + "\n";
                out += "Status         : " + QString::fromStdString(st) + "\n";
                break;
            }
        }
    }
    txtInfo->setPlainText(out);

    connect(btnClose, &QPushButton::clicked, this, &QDialog::accept);
}