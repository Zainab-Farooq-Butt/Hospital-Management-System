#include "patientdashboard.h"
#include "loginwindow.h"
#include "PersonalInfoDialog.h"
#include "MedicalRecordsViewDialog.h"
#include "AppointmentBookDialog.h"
#include "AppointmentListDialog.h"
#include "BillingDialog.h"
#include "CredentialsDialog.h"
#include "PharmacyRecordsDialog.h"
#include "AmbulanceListDialog.h"

#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QWidget>
#include <QMessageBox>
#include <fstream>
#include <string>

PatientDashboard::PatientDashboard(const QString &username, QWidget *parent)
    : QMainWindow(parent), currentUser(username) {
    setWindowTitle("Patient Dashboard - " + username);
    resize(700, 550);

    auto *central = new QWidget(this);
    auto *root    = new QVBoxLayout(central);

    auto *welcome = new QLabel("Welcome, " + username, central);
    QFont wf = welcome->font(); wf.setPointSize(14); wf.setBold(true);
    welcome->setFont(wf);
    root->addWidget(welcome);

    auto *grid = new QGridLayout();
    auto mk = [&](const QString &t) {
        auto *b = new QPushButton(t, central);
        b->setMinimumHeight(50);
        return b;
    };

    auto *bPI  = mk("View Personal Info");
    auto *bMR  = mk("View Medical Records");
    auto *bBA  = mk("Book Appointment");
    auto *bCA  = mk("Cancel Appointment");
    auto *bVB  = mk("View Bill");
    auto *bUC  = mk("Update Credentials");
    auto *bPR  = mk("Show Pharmacy Records");
    auto *bRA  = mk("Request Ambulance");
    auto *bLO  = mk("Logout");

    grid->addWidget(bPI, 0, 0); grid->addWidget(bMR, 0, 1);
    grid->addWidget(bBA, 1, 0); grid->addWidget(bCA, 1, 1);
    grid->addWidget(bVB, 2, 0); grid->addWidget(bUC, 2, 1);
    grid->addWidget(bPR, 3, 0); grid->addWidget(bRA, 3, 1);
    
    root->addLayout(grid);
    root->addStretch();
    
    bLO->setMinimumWidth(150);
    auto *logoutLayout = new QHBoxLayout();
    logoutLayout->addStretch();
    logoutLayout->addWidget(bLO);
    logoutLayout->addStretch();
    root->addLayout(logoutLayout);

    setCentralWidget(central);

    resolvePatientIdentity();
    if (loggedCNIC.isEmpty()) {
        QMessageBox::critical(this, "Error",
                              "User CNIC not found. Login data may be corrupted.");
    }

    connect(bPI, &QPushButton::clicked, this, &PatientDashboard::onViewPersonalInfo);
    connect(bMR, &QPushButton::clicked, this, &PatientDashboard::onViewMedicalRecords);
    connect(bBA, &QPushButton::clicked, this, &PatientDashboard::onBookAppointment);
    connect(bCA, &QPushButton::clicked, this, &PatientDashboard::onCancelAppointment);
    connect(bVB, &QPushButton::clicked, this, &PatientDashboard::onViewBill);
    connect(bUC, &QPushButton::clicked, this, &PatientDashboard::onUpdateCredentials);
    connect(bPR, &QPushButton::clicked, this, &PatientDashboard::onShowPharmacyRecords);
    connect(bRA, &QPushButton::clicked, this, &PatientDashboard::onRequestAmbulance);
    connect(bLO, &QPushButton::clicked, this, &PatientDashboard::onLogout);
}

void PatientDashboard::resolvePatientIdentity() {
    {
        std::ifstream f("Users.txt");
        std::string ln;
        while (std::getline(f, ln)) {
            if (ln != "----------") continue;
            std::string cnic, uname, pass, role;
            std::getline(f, cnic); std::getline(f, uname);
            std::getline(f, pass); std::getline(f, role);
            if (uname == currentUser.toStdString()) {
                loggedCNIC = QString::fromStdString(cnic);
                break;
            }
        }
    }
    if (loggedCNIC.isEmpty()) return;

    std::ifstream pf("Patient.txt");
    std::string ln;
    while (std::getline(pf, ln)) {
        if (ln != "----------") continue;
        std::string c, pid, blood, type, h, w, ec, st;
        std::getline(pf, c); std::getline(pf, pid); std::getline(pf, blood);
        std::getline(pf, type); std::getline(pf, h); std::getline(pf, w);
        std::getline(pf, ec); std::getline(pf, st);
        if (c == loggedCNIC.toStdString()) {
            patientId = QString::fromStdString(pid);
            break;
        }
    }
}

void PatientDashboard::onViewPersonalInfo() {
    PersonalInfoDialog dlg(PersonalInfoDialog::PATIENT_VIEW, loggedCNIC, this);
    dlg.exec();
}
void PatientDashboard::onViewMedicalRecords() {
    MedicalRecordsViewDialog dlg(patientId, this); dlg.exec();
}
void PatientDashboard::onBookAppointment() {
    AppointmentBookDialog dlg(patientId, this); dlg.exec();
}
void PatientDashboard::onCancelAppointment() {
    AppointmentListDialog dlg(AppointmentListDialog::BY_PATIENT, patientId, this);
    dlg.exec();
}
void PatientDashboard::onViewBill() {
    BillingDialog dlg(BillingDialog::SHOW_ONE, this); dlg.exec();
}
void PatientDashboard::onUpdateCredentials() {
    CredentialsDialog dlg(this); dlg.exec();
}
void PatientDashboard::onShowPharmacyRecords() {
    PharmacyRecordsDialog dlg(PharmacyRecordsDialog::BY_PATIENT, patientId, this);
    dlg.exec();
}
void PatientDashboard::onRequestAmbulance() {
    AmbulanceListDialog dlg(AmbulanceListDialog::AVAILABLE_FOR_REQUEST, this);
    dlg.exec();
}
void PatientDashboard::onLogout() {
    auto *login = new LoginWindow();
    login->setAttribute(Qt::WA_DeleteOnClose);
    login->show();
    this->close();
}