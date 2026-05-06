#include "doctordashboard.h"
#include "loginwindow.h"
#include "PersonalInfoDialog.h"
#include "MedicalRecordsViewDialog.h"
#include "MedicalRecordAddDialog.h"
#include "AppointmentListDialog.h"
#include "CredentialsDialog.h"

#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QWidget>
#include <QInputDialog>
#include <QLineEdit>
#include <QMessageBox>
#include <fstream>
#include <string>

DoctorDashboard::DoctorDashboard(const QString &username, QWidget *parent)
    : QMainWindow(parent), currentUser(username) {
    setWindowTitle("Doctor Dashboard - " + username);
    resize(700, 500);

    auto *central = new QWidget(this);
    auto *root    = new QVBoxLayout(central);

    auto *welcome = new QLabel("Welcome, Dr. " + username, central);
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
    auto *bPR  = mk("View Patient Records");
    auto *bAR  = mk("Add Medical Record");
    auto *bSA  = mk("Show Appointments");
    auto *bCA  = mk("Cancel Appointment");
    auto *bUC  = mk("Update Credentials");
    auto *bLO  = mk("Logout");

    grid->addWidget(bPI, 0, 0); grid->addWidget(bPR, 0, 1);
    grid->addWidget(bAR, 1, 0); grid->addWidget(bSA, 1, 1);
    grid->addWidget(bCA, 2, 0); grid->addWidget(bUC, 2, 1);
    
    root->addLayout(grid);
    root->addStretch();
    
    bLO->setMinimumWidth(150);
    auto *logoutLayout = new QHBoxLayout();
    logoutLayout->addStretch();
    logoutLayout->addWidget(bLO);
    logoutLayout->addStretch();
    root->addLayout(logoutLayout);
    
    setCentralWidget(central);

    resolveDoctorIdentity();
    if (loggedCNIC.isEmpty() || doctorId.isEmpty()) {
        QMessageBox::critical(this, "Error",
                              "Doctor record not found. Login data may be corrupted.");
    }

    connect(bPI, &QPushButton::clicked, this, &DoctorDashboard::onViewPersonalInfo);
    connect(bPR, &QPushButton::clicked, this, &DoctorDashboard::onViewPatientRecords);
    connect(bAR, &QPushButton::clicked, this, &DoctorDashboard::onAddMedicalRecord);
    connect(bSA, &QPushButton::clicked, this, &DoctorDashboard::onShowAppointments);
    connect(bCA, &QPushButton::clicked, this, &DoctorDashboard::onCancelAppointment);
    connect(bUC, &QPushButton::clicked, this, &DoctorDashboard::onUpdateCredentials);
    connect(bLO, &QPushButton::clicked, this, &DoctorDashboard::onLogout);
}

void DoctorDashboard::resolveDoctorIdentity() {
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

    std::ifstream df("Doctor.txt");
    std::string ln;
    while (std::getline(df, ln)) {
        if (ln != "----------") continue;
        std::string cnic, did, spec, qual, exp, fee, avail, stat;
        std::getline(df, cnic); std::getline(df, did);
        std::getline(df, spec); std::getline(df, qual);
        std::getline(df, exp);  std::getline(df, fee);
        std::getline(df, avail); std::getline(df, stat);
        if (cnic == loggedCNIC.toStdString()) {
            doctorId = QString::fromStdString(did);
            break;
        }
    }
}

void DoctorDashboard::onViewPersonalInfo() {
    PersonalInfoDialog dlg(PersonalInfoDialog::DOCTOR_VIEW, loggedCNIC, this);
    dlg.exec();
}
void DoctorDashboard::onViewPatientRecords() {
    bool ok;
    QString pid = QInputDialog::getText(this, "Patient ID", "P-XXXX:",
                                        QLineEdit::Normal, "", &ok);
    if (ok) { MedicalRecordsViewDialog dlg(pid, this); dlg.exec(); }
}
void DoctorDashboard::onAddMedicalRecord() {
    MedicalRecordAddDialog dlg(doctorId, this); dlg.exec();
}
void DoctorDashboard::onShowAppointments() {
    AppointmentListDialog dlg(AppointmentListDialog::BY_DOCTOR, doctorId, this);
    dlg.exec();
}
void DoctorDashboard::onCancelAppointment() {
    AppointmentListDialog dlg(AppointmentListDialog::BY_DOCTOR, doctorId, this);
    dlg.exec();
}
void DoctorDashboard::onUpdateCredentials() {
    CredentialsDialog dlg(this); dlg.exec();
}
void DoctorDashboard::onLogout() {
    auto *login = new LoginWindow();
    login->setAttribute(Qt::WA_DeleteOnClose);
    login->show();
    this->close();
}