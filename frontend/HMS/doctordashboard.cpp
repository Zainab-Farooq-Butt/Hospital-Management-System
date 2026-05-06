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
    auto *mainLayout = new QHBoxLayout(central);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    // SIDEBAR
    auto *sidebar = new QFrame(central);
    sidebar->setObjectName("sidebar");
    sidebar->setMaximumWidth(260);
    sidebar->setMinimumWidth(260);
    sidebar->setStyleSheet("#sidebar { background-color: rgba(255, 255, 255, 0.9); border-right: 2px solid #e2e8f0; }");
    auto *sideLayout = new QVBoxLayout(sidebar);
    sideLayout->setContentsMargins(20, 30, 20, 30);
    sideLayout->setSpacing(15);

    auto *lblDash = new QLabel("Doctor Menu", sidebar);
    QFont df = lblDash->font(); df.setPointSize(16); df.setBold(true);
    lblDash->setFont(df);
    lblDash->setAlignment(Qt::AlignCenter);
    lblDash->setStyleSheet("color: #0ea5e9; margin-bottom: 20px;");
    sideLayout->addWidget(lblDash);

    auto mk = [&](const QString &t) {
        auto *b = new QPushButton(t, sidebar);
        b->setMinimumHeight(45);
        return b;
    };

    auto *bPI  = mk("Personal Info");
    auto *bPR  = mk("Patient Records");
    auto *bAR  = mk("Add Medical Record");
    auto *bSA  = mk("Appointments");
    auto *bCA  = mk("Cancel Appointment");
    auto *bUC  = mk("Update Credentials");
    
    sideLayout->addWidget(bPI);
    sideLayout->addWidget(bPR);
    sideLayout->addWidget(bAR);
    sideLayout->addWidget(bSA);
    sideLayout->addWidget(bCA);
    sideLayout->addWidget(bUC);
    sideLayout->addStretch();
    
    auto *bLO  = mk("Logout");
    bLO->setStyleSheet("background: #ef4444; color: white;"); // Red logout
    sideLayout->addWidget(bLO);

    // MAIN CONTENT AREA
    auto *contentArea = new QFrame(central);
    auto *contentLayout = new QVBoxLayout(contentArea);
    contentLayout->setAlignment(Qt::AlignCenter);

    auto *logoLabel = new QLabel(contentArea);
    QPixmap logo("C:/Users/mueez/.gemini/antigravity/brain/9baebc15-b0f9-41d5-b46c-d7303fba27d8/medical_logo_1778005812670.png");
    logoLabel->setPixmap(logo.scaled(150, 150, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    logoLabel->setAlignment(Qt::AlignCenter);

    auto *welcome = new QLabel("Welcome, Dr. " + username, contentArea);
    QFont wf = welcome->font(); wf.setPointSize(24); wf.setBold(true);
    welcome->setFont(wf);
    welcome->setAlignment(Qt::AlignCenter);
    welcome->setStyleSheet("color: #0284c7; margin-top: 20px;");

    auto *subtitle = new QLabel("Select an option from the sidebar to manage your hospital operations.", contentArea);
    subtitle->setAlignment(Qt::AlignCenter);
    subtitle->setStyleSheet("color: #64748b; font-size: 14px; margin-top: 10px;");

    contentLayout->addWidget(logoLabel);
    contentLayout->addWidget(welcome);
    contentLayout->addWidget(subtitle);

    mainLayout->addWidget(sidebar);
    mainLayout->addWidget(contentArea);
    
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