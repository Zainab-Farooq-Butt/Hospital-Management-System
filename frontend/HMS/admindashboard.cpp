#include "admindashboard.h"
#include "loginwindow.h"
#include "PatientRegisterDialog.h"
#include "PatientListDialog.h"
#include "PatientUpdateDialog.h"
#include "StaffRegisterDialog.h"
#include "StaffListDialog.h"
#include "DoctorRegisterDialog.h"
#include "DoctorListDialog.h"
#include "AppointmentListDialog.h"
#include "CredentialsDialog.h"
#include "MedicalRecordsViewDialog.h"
#include "BillingDialog.h"
#include "RoomAssignDialog.h"
#include "DischargeDialog.h"
#include "PharmacyInventoryDialog.h"
#include "AddMedicineDialog.h"
#include "PrescriptionDialog.h"
#include "PharmacyRecordsDialog.h"
#include "RestockDialog.h"
#include "AmbulanceRegisterDialog.h"
#include "AmbulanceListDialog.h"

#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QTabWidget>
#include <QWidget>
#include <QInputDialog>
#include <QMessageBox>

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
    b->setMinimumHeight(100);
    b->setCursor(Qt::PointingHandCursor);
    return b;
}

AdminDashboard::AdminDashboard(const QString &username, QWidget *parent)
    : QMainWindow(parent), currentUser(username) {
    setWindowTitle("HMS Admin Dashboard");
    resize(1200, 800);

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

    auto *logoLabel = new QLabel("🏥 HMS PRO", sidebar);
    logoLabel->setStyleSheet("color: white; font-size: 22px; font-weight: 900; margin: 20px;");
    sidebarLayout->addWidget(logoLabel);

    sidebarLayout->addSpacing(20);

    auto *btnGroup = new QButtonGroup(this);
    btnGroup->setExclusive(true);

    auto *bNavPat = mkSidebarBtn("👤", "Patients", sidebar);
    auto *bNavStaff = mkSidebarBtn("⚕️", "Staff & Doctors", sidebar);
    auto *bNavBill = mkSidebarBtn("💳", "Billing & Rooms", sidebar);
    auto *bNavPhar = mkSidebarBtn("💊", "Pharmacy", sidebar);
    auto *bNavAmb = mkSidebarBtn("🚑", "Ambulance", sidebar);
    auto *bNavSys = mkSidebarBtn("⚙️", "System Settings", sidebar);

    btnGroup->addButton(bNavPat, 0);
    btnGroup->addButton(bNavStaff, 1);
    btnGroup->addButton(bNavBill, 2);
    btnGroup->addButton(bNavPhar, 3);
    btnGroup->addButton(bNavAmb, 4);
    btnGroup->addButton(bNavSys, 5);

    sidebarLayout->addWidget(bNavPat);
    sidebarLayout->addWidget(bNavStaff);
    sidebarLayout->addWidget(bNavBill);
    sidebarLayout->addWidget(bNavPhar);
    sidebarLayout->addWidget(bNavAmb);
    sidebarLayout->addWidget(bNavSys);

    sidebarLayout->addStretch();

    auto *btnLogout = new QPushButton("🚪 Logout", sidebar);
    btnLogout->setObjectName("ActionBtn");
    btnLogout->setMinimumHeight(45);
    btnLogout->setStyleSheet("margin: 20px; border-radius: 10px;");
    sidebarLayout->addWidget(btnLogout);

    mainLayout->addWidget(sidebar);

    // --- CONTENT AREA ---
    auto *contentArea = new QWidget(central);
    contentArea->setObjectName("ContentArea");
    auto *contentLayout = new QVBoxLayout(contentArea);
    contentLayout->setContentsMargins(40, 40, 40, 40);

    auto *headerLayout = new QHBoxLayout();
    auto *pageTitle = new QLabel("Dashboard Overview", contentArea);
    pageTitle->setObjectName("PageHeader");
    headerLayout->addWidget(pageTitle);
    headerLayout->addStretch();
    auto *userGreeting = new QLabel("Welcome, Admin " + username, contentArea);
    userGreeting->setStyleSheet("color: #64748b; font-weight: 600;");
    headerLayout->addWidget(userGreeting);
    contentLayout->addLayout(headerLayout);

    auto *stack = new QStackedWidget(contentArea);

    // 1. Patients Page
    auto *pPage = new QWidget();
    auto *pLayout = new QVBoxLayout(pPage);
    auto *pTitle = new QLabel("Patient Management", pPage);
    pTitle->setObjectName("SectionHeader");
    pLayout->addWidget(pTitle);
    auto *pGrid = new QGridLayout();
    auto *bRP = mkCardBtn("Register New Patient", pPage);
    auto *bVP = mkCardBtn("View Patient Directory", pPage);
    auto *bUP = mkCardBtn("Update Patient Info", pPage);
    auto *bMR = mkCardBtn("Medical History Records", pPage);
    pGrid->addWidget(bRP, 0, 0); pGrid->addWidget(bVP, 0, 1);
    pGrid->addWidget(bUP, 1, 0); pGrid->addWidget(bMR, 1, 1);
    pLayout->addLayout(pGrid);
    pLayout->addStretch();
    stack->addWidget(pPage);

    // 2. Staff Page
    auto *sPage = new QWidget();
    auto *sLayout = new QVBoxLayout(sPage);
    auto *sTitle = new QLabel("Staff & Doctor Directory", sPage);
    sTitle->setObjectName("SectionHeader");
    sLayout->addWidget(sTitle);
    auto *sGrid = new QGridLayout();
    auto *bRS = mkCardBtn("Register Staff Member", sPage);
    auto *bVS = mkCardBtn("Staff Directory", sPage);
    auto *bRD = mkCardBtn("Register Doctor", sPage);
    auto *bVD = mkCardBtn("Doctor Directory", sPage);
    auto *bDA = mkCardBtn("Manage Appointments", sPage);
    sGrid->addWidget(bRS, 0, 0); sGrid->addWidget(bVS, 0, 1);
    sGrid->addWidget(bRD, 1, 0); sGrid->addWidget(bVD, 1, 1);
    sGrid->addWidget(bDA, 2, 0);
    sLayout->addLayout(sGrid);
    sLayout->addStretch();
    stack->addWidget(sPage);

    // 3. Billing Page
    auto *bPage = new QWidget();
    auto *bLayout = new QVBoxLayout(bPage);
    auto *bTitle = new QLabel("Billing & Hospital Services", bPage);
    bTitle->setObjectName("SectionHeader");
    bLayout->addWidget(bTitle);
    auto *bGrid = new QGridLayout();
    auto *bSPB = mkCardBtn("Generate Patient Bill", bPage);
    auto *bSAB = mkCardBtn("Financial Reports", bPage);
    auto *bUPB = mkCardBtn("Payment Status", bPage);
    auto *bDP  = mkCardBtn("Discharge & Billing", bPage);
    auto *bAR  = mkCardBtn("Room Assignment", bPage);
    bGrid->addWidget(bSPB, 0, 0); bGrid->addWidget(bSAB, 0, 1);
    bGrid->addWidget(bUPB, 1, 0); bGrid->addWidget(bDP, 1, 1);
    bGrid->addWidget(bAR, 2, 0);
    bLayout->addLayout(bGrid);
    bLayout->addStretch();
    stack->addWidget(bPage);

    // 4. Pharmacy Page
    auto *phPage = new QWidget();
    auto *phLayout = new QVBoxLayout(phPage);
    auto *phTitle = new QLabel("Pharmacy & Inventory", phPage);
    phTitle->setObjectName("SectionHeader");
    phLayout->addWidget(phTitle);
    auto *phGrid = new QGridLayout();
    auto *bVPh = mkCardBtn("Current Inventory", phPage);
    auto *bAM  = mkCardBtn("Add New Stock", phPage);
    auto *bIPr = mkCardBtn("New Prescription", phPage);
    auto *bLS  = mkCardBtn("Low Stock Alerts", phPage);
    auto *bAPr = mkCardBtn("Pharmacy Records", phPage);
    auto *bRM  = mkCardBtn("Restock Medicine", phPage);
    phGrid->addWidget(bVPh, 0, 0); phGrid->addWidget(bAM, 0, 1);
    phGrid->addWidget(bIPr, 1, 0); phGrid->addWidget(bLS, 1, 1);
    phGrid->addWidget(bAPr, 2, 0); phGrid->addWidget(bRM, 2, 1);
    phLayout->addLayout(phGrid);
    phLayout->addStretch();
    stack->addWidget(phPage);

    // 5. Ambulance Page
    auto *amPage = new QWidget();
    auto *amLayout = new QVBoxLayout(amPage);
    auto *amTitle = new QLabel("Emergency Services", amPage);
    amTitle->setObjectName("SectionHeader");
    amLayout->addWidget(amTitle);
    auto *amGrid = new QGridLayout();
    auto *bRAm = mkCardBtn("Register Ambulance", amPage);
    auto *bVAm = mkCardBtn("Active Fleet", amPage);
    auto *bUAm = mkCardBtn("Maintenance Logs", amPage);
    amGrid->addWidget(bRAm, 0, 0); amGrid->addWidget(bVAm, 0, 1);
    amGrid->addWidget(bUAm, 1, 0);
    amLayout->addLayout(amGrid);
    amLayout->addStretch();
    stack->addWidget(amPage);

    // 6. System Page
    auto *sysPage = new QWidget();
    auto *sysLayout = new QVBoxLayout(sysPage);
    auto *sysTitle = new QLabel("System Configuration", sysPage);
    sysTitle->setObjectName("SectionHeader");
    sysLayout->addWidget(sysTitle);
    auto *sysGrid = new QGridLayout();
    auto *bRA = mkCardBtn("Manage Admin Users", sysPage);
    auto *bUC = mkCardBtn("Security Credentials", sysPage);
    sysGrid->addWidget(bRA, 0, 0); sysGrid->addWidget(bUC, 0, 1);
    sysLayout->addLayout(sysGrid);
    sysLayout->addStretch();
    stack->addWidget(sysPage);

    contentLayout->addWidget(stack);
    mainLayout->addWidget(contentArea);
    setCentralWidget(central);

    // Sidebar navigation logic
    connect(btnGroup, &QButtonGroup::buttonClicked, [=](QAbstractButton *button){
        int id = btnGroup->id(button);
        stack->setCurrentIndex(id);
        QString titles[] = {"Patient Management", "Staff & Doctors", "Billing & Rooms", "Pharmacy", "Ambulance Fleet", "System Settings"};
        pageTitle->setText(titles[id]);
    });
    bNavPat->setChecked(true);

    // Functional Connections
    connect(bRP,  &QPushButton::clicked, this, &AdminDashboard::onRegisterPatient);
    connect(bVP,  &QPushButton::clicked, this, &AdminDashboard::onViewPatients);
    connect(bUP,  &QPushButton::clicked, this, &AdminDashboard::onUpdatePatient);
    connect(bMR,  &QPushButton::clicked, this, &AdminDashboard::onViewMedicalRecords);
    connect(bRS,  &QPushButton::clicked, this, &AdminDashboard::onRegisterStaff);
    connect(bVS,  &QPushButton::clicked, this, &AdminDashboard::onViewStaff);
    connect(bRD,  &QPushButton::clicked, this, &AdminDashboard::onRegisterDoctor);
    connect(bVD,  &QPushButton::clicked, this, &AdminDashboard::onViewDoctors);
    connect(bDA,  &QPushButton::clicked, this, &AdminDashboard::onViewDoctorAppointments);
    connect(bSPB, &QPushButton::clicked, this, &AdminDashboard::onShowPatientBill);
    connect(bSAB, &QPushButton::clicked, this, &AdminDashboard::onShowAllBills);
    connect(bUPB, &QPushButton::clicked, this, &AdminDashboard::onUpdatePatientBill);
    connect(bDP,  &QPushButton::clicked, this, &AdminDashboard::onDischargePatient);
    connect(bAR,  &QPushButton::clicked, this, &AdminDashboard::onAssignRoom);
    connect(bVPh, &QPushButton::clicked, this, &AdminDashboard::onViewPharmacy);
    connect(bAM,  &QPushButton::clicked, this, &AdminDashboard::onAddMedicine);
    connect(bIPr, &QPushButton::clicked, this, &AdminDashboard::onIssuePrescription);
    connect(bLS,  &QPushButton::clicked, this, &AdminDashboard::onViewLowStock);
    connect(bAPr, &QPushButton::clicked, this, &AdminDashboard::onViewAllPrescriptions);
    connect(bRM,  &QPushButton::clicked, this, &AdminDashboard::onRestockMedicine);
    connect(bRAm, &QPushButton::clicked, this, &AdminDashboard::onRegisterAmbulance);
    connect(bVAm, &QPushButton::clicked, this, &AdminDashboard::onViewAmbulances);
    connect(bUAm, &QPushButton::clicked, this, &AdminDashboard::onUpdateAmbulance);
    connect(bRA,  &QPushButton::clicked, this, &AdminDashboard::onRegisterAdmin);
    connect(bUC,  &QPushButton::clicked, this, &AdminDashboard::onUpdateCredentials);
    connect(btnLogout, &QPushButton::clicked, this, &AdminDashboard::onLogout);
}

void AdminDashboard::onRegisterPatient()       { PatientRegisterDialog dlg(this); dlg.exec(); }
void AdminDashboard::onViewPatients()          { PatientListDialog dlg(this); dlg.exec(); }
void AdminDashboard::onUpdatePatient()         { PatientUpdateDialog dlg(this); dlg.exec(); }
void AdminDashboard::onViewMedicalRecords() {
    bool ok;
    QString pid = QInputDialog::getText(this, "Patient ID", "Enter P-XXXX:",
                                        QLineEdit::Normal, "", &ok);
    if (ok && !pid.isEmpty()) { MedicalRecordsViewDialog dlg(pid, this); dlg.exec(); }
}
void AdminDashboard::onRegisterStaff()         { StaffRegisterDialog dlg(this); dlg.exec(); }
void AdminDashboard::onViewStaff()             { StaffListDialog dlg(this); dlg.exec(); }
void AdminDashboard::onUpdateStaff() {
    QMessageBox::information(this, "Note",
                             "Staff update follows same pattern as Patient update.");
}
void AdminDashboard::onRegisterDoctor()        { DoctorRegisterDialog dlg(this); dlg.exec(); }
void AdminDashboard::onViewDoctors()           { DoctorListDialog dlg(this); dlg.exec(); }
void AdminDashboard::onUpdateDoctor() {
    QMessageBox::information(this, "Note",
                             "Doctor update follows same pattern as Patient update.");
}
void AdminDashboard::onViewDoctorAppointments() {
    bool ok;
    QString did = QInputDialog::getText(this, "Doctor ID", "D-XXXX:",
                                        QLineEdit::Normal, "", &ok);
    if (ok && !did.isEmpty()) {
        AppointmentListDialog dlg(AppointmentListDialog::BY_DOCTOR, did, this);
        dlg.exec();
    }
}
void AdminDashboard::onRegisterAdmin() {
    QMessageBox::information(this, "Note",
                             "Admin registration: same pattern as Patient/Doctor register, role=ADMIN.");
}
void AdminDashboard::onUpdateCredentials()    { CredentialsDialog dlg(this); dlg.exec(); }
void AdminDashboard::onShowPatientBill()      { BillingDialog dlg(BillingDialog::SHOW_ONE, this); dlg.exec(); }
void AdminDashboard::onShowAllBills()         { BillingDialog dlg(BillingDialog::SHOW_ALL, this); dlg.exec(); }
void AdminDashboard::onSetPatientBill()       { BillingDialog dlg(BillingDialog::SET_BILL, this); dlg.exec(); }
void AdminDashboard::onUpdatePatientBill()    { BillingDialog dlg(BillingDialog::UPDATE_STATUS, this); dlg.exec(); }
void AdminDashboard::onDischargePatient()     { DischargeDialog dlg(this); dlg.exec(); }
void AdminDashboard::onAssignRoom()           { RoomAssignDialog dlg(this); dlg.exec(); }
void AdminDashboard::onViewPharmacy()         { PharmacyInventoryDialog dlg(PharmacyInventoryDialog::ALL, this); dlg.exec(); }
void AdminDashboard::onAddMedicine()          { AddMedicineDialog dlg(this); dlg.exec(); }
void AdminDashboard::onIssuePrescription()    { PrescriptionDialog dlg(this); dlg.exec(); }
void AdminDashboard::onSearchPharmacyRecords() {
    bool ok;
    QString pid = QInputDialog::getText(this, "Patient ID", "P-XXXX:",
                                        QLineEdit::Normal, "", &ok);
    if (ok && !pid.isEmpty()) {
        PharmacyRecordsDialog dlg(PharmacyRecordsDialog::BY_PATIENT, pid, this);
        dlg.exec();
    }
}
void AdminDashboard::onViewLowStock()         { PharmacyInventoryDialog dlg(PharmacyInventoryDialog::LOW_STOCK_ONLY, this); dlg.exec(); }
void AdminDashboard::onViewAllPrescriptions() { PharmacyRecordsDialog dlg(PharmacyRecordsDialog::ALL_PRESCRIPTIONS, "", this); dlg.exec(); }
void AdminDashboard::onRestockMedicine()      { RestockDialog dlg(this); dlg.exec(); }
void AdminDashboard::onRegisterAmbulance()    { AmbulanceRegisterDialog dlg(this); dlg.exec(); }
void AdminDashboard::onViewAmbulances()       { AmbulanceListDialog dlg(AmbulanceListDialog::ALL, this); dlg.exec(); }
void AdminDashboard::onUpdateAmbulance() {
    QMessageBox::information(this, "Note",
                             "Ambulance update follows same pattern as Patient update.");
}
void AdminDashboard::onLogout() {
    auto *login = new LoginWindow();
    login->setAttribute(Qt::WA_DeleteOnClose);
    login->show();
    this->close();
}