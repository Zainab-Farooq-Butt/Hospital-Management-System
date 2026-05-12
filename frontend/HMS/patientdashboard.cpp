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

#include <QStackedWidget>
#include <QButtonGroup>
#include <QFrame>

static QPushButton* mkSidebarBtn(const QString &icon, const QString &text, QWidget *parent) {
    auto *b = new QPushButton(icon + "  " + text, parent);
    b->setCheckable(true);
    b->setMinimumHeight(50);
    return b;
}

static QPushButton* mkCardBtn(const QString &text, QWidget *parent) {
    auto *b = new QPushButton(text, parent);
    b->setMinimumHeight(120);
    b->setCursor(Qt::PointingHandCursor);
    return b;
}

PatientDashboard::PatientDashboard(const QString &username, QWidget *parent)
    : QMainWindow(parent), currentUser(username) {
    setWindowTitle("HMS Patient Portal");
    resize(1100, 750);

    auto *central = new QWidget(this);
    auto *mainLayout = new QHBoxLayout(central);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    // --- SIDEBAR ---
    auto *sidebar = new QWidget(central);
    sidebar->setObjectName("Sidebar");
    auto *sidebarLayout = new QVBoxLayout(sidebar);
    sidebarLayout->setContentsMargins(0, 20, 0, 20);
    sidebarLayout->setSpacing(5);

    auto *logoLabel = new QLabel("🏥 PATIENT HUB", sidebar);
    logoLabel->setStyleSheet("color: white; font-size: 20px; font-weight: 900; margin: 20px;");
    sidebarLayout->addWidget(logoLabel);

    sidebarLayout->addSpacing(20);

    auto *btnGroup = new QButtonGroup(this);
    btnGroup->setExclusive(true);

    auto *bNavOver = mkSidebarBtn("📊", "Overview", sidebar);
    auto *bNavMed  = mkSidebarBtn("📋", "Medical Records", sidebar);
    auto *bNavApp  = mkSidebarBtn("📅", "Appointments", sidebar);
    auto *bNavBill = mkSidebarBtn("💳", "Billing", sidebar);
    auto *bNavSys  = mkSidebarBtn("⚙️", "Settings", sidebar);

    btnGroup->addButton(bNavOver, 0);
    btnGroup->addButton(bNavMed, 1);
    btnGroup->addButton(bNavApp, 2);
    btnGroup->addButton(bNavBill, 3);
    btnGroup->addButton(bNavSys, 4);

    sidebarLayout->addWidget(bNavOver);
    sidebarLayout->addWidget(bNavMed);
    sidebarLayout->addWidget(bNavApp);
    sidebarLayout->addWidget(bNavBill);
    sidebarLayout->addWidget(bNavSys);

    sidebarLayout->addStretch();

    auto *bLO = new QPushButton("🚪 Logout", sidebar);
    bLO->setObjectName("ActionBtn");
    bLO->setMinimumHeight(45);
    bLO->setStyleSheet("margin: 20px; border-radius: 10px;");
    sidebarLayout->addWidget(bLO);

    mainLayout->addWidget(sidebar);

    // --- CONTENT AREA ---
    auto *contentArea = new QWidget(central);
    contentArea->setObjectName("ContentArea");
    auto *contentLayout = new QVBoxLayout(contentArea);
    contentLayout->setContentsMargins(40, 40, 40, 40);

    auto *headerLayout = new QHBoxLayout();
    auto *pageTitle = new QLabel("Patient Overview", contentArea);
    pageTitle->setObjectName("PageHeader");
    headerLayout->addWidget(pageTitle);
    headerLayout->addStretch();
    auto *userGreeting = new QLabel("Welcome, " + username, contentArea);
    userGreeting->setStyleSheet("color: #64748b; font-weight: 600;");
    headerLayout->addWidget(userGreeting);
    contentLayout->addLayout(headerLayout);

    auto *stack = new QStackedWidget(contentArea);

    // 1. Overview Page
    auto *overPage = new QWidget();
    auto *overLayout = new QVBoxLayout(overPage);
    auto *overTitle = new QLabel("Quick Actions", overPage);
    overTitle->setObjectName("SectionHeader");
    overLayout->addWidget(overTitle);
    auto *overGrid = new QGridLayout();
    auto *bPI  = mkCardBtn("View My Profile", overPage);
    auto *bRA  = mkCardBtn("Request Emergency\nAmbulance", overPage);
    overGrid->addWidget(bPI, 0, 0); overGrid->addWidget(bRA, 0, 1);
    overLayout->addLayout(overGrid);
    overLayout->addStretch();
    stack->addWidget(overPage);

    // 2. Records Page
    auto *recPage = new QWidget();
    auto *recLayout = new QVBoxLayout(recPage);
    auto *recTitle = new QLabel("Health Records", recPage);
    recTitle->setObjectName("SectionHeader");
    recLayout->addWidget(recTitle);
    auto *recGrid = new QGridLayout();
    auto *bMR  = mkCardBtn("View Medical History", recPage);
    auto *bPR  = mkCardBtn("Pharmacy & Prescriptions", recPage);
    recGrid->addWidget(bMR, 0, 0); recGrid->addWidget(bPR, 0, 1);
    recLayout->addLayout(recGrid);
    recLayout->addStretch();
    stack->addWidget(recPage);

    // 3. Appointments Page
    auto *appPage = new QWidget();
    auto *appLayout = new QVBoxLayout(appPage);
    auto *appTitle = new QLabel("Manage Visits", appPage);
    appTitle->setObjectName("SectionHeader");
    appLayout->addWidget(appTitle);
    auto *appGrid = new QGridLayout();
    auto *bBA  = mkCardBtn("Book New Appointment", appPage);
    auto *bCA  = mkCardBtn("View/Cancel Appointments", appPage);
    appGrid->addWidget(bBA, 0, 0); appGrid->addWidget(bCA, 0, 1);
    appLayout->addLayout(appGrid);
    appLayout->addStretch();
    stack->addWidget(appPage);

    // 4. Billing Page
    auto *billPage = new QWidget();
    auto *billLayout = new QVBoxLayout(billPage);
    auto *billTitle = new QLabel("Financial Information", billPage);
    billTitle->setObjectName("SectionHeader");
    billLayout->addWidget(billTitle);
    auto *billGrid = new QGridLayout();
    auto *bVB  = mkCardBtn("View Current Bill", billPage);
    billGrid->addWidget(bVB, 0, 0);
    billLayout->addLayout(billGrid);
    billLayout->addStretch();
    stack->addWidget(billPage);

    // 5. Settings Page
    auto *setPage = new QWidget();
    auto *setLayout = new QVBoxLayout(setPage);
    auto *setTitle = new QLabel("Account Security", setPage);
    setTitle->setObjectName("SectionHeader");
    setLayout->addWidget(setTitle);
    auto *setGrid = new QGridLayout();
    auto *bUC  = mkCardBtn("Update Login Credentials", setPage);
    setGrid->addWidget(bUC, 0, 0);
    setLayout->addLayout(setGrid);
    setLayout->addStretch();
    stack->addWidget(setPage);

    contentLayout->addWidget(stack);
    mainLayout->addWidget(contentArea);
    setCentralWidget(central);

    resolvePatientIdentity();
    if (loggedCNIC.isEmpty()) {
        QMessageBox::critical(this, "Error", "User CNIC not found. Login data may be corrupted.");
    }

    // Sidebar navigation
    connect(btnGroup, &QButtonGroup::buttonClicked, [=](QAbstractButton *button){
        int id = btnGroup->id(button);
        stack->setCurrentIndex(id);
        QString titles[] = {"Patient Overview", "Medical Records", "Appointments", "Billing", "Account Settings"};
        pageTitle->setText(titles[id]);
    });
    bNavOver->setChecked(true);

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
<<<<<<< HEAD
    BillingDialog dlg(BillingDialog::SHOW_ONE, this); dlg.exec();
}
void PatientDashboard::onUpdateCredentials() {
    CredentialsDialog dlg(this); dlg.exec();
=======
    BillingDialog dlg(BillingDialog::SHOW_ONE, this, patientId); dlg.exec();
}
void PatientDashboard::onUpdateCredentials() {
    CredentialsDialog dlg(loggedCNIC, this); dlg.exec();
>>>>>>> origin/zainab
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