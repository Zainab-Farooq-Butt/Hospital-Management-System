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

static QPushButton* mkBtn(const QString &text, QWidget *parent) {
    auto *b = new QPushButton(text, parent);
    b->setMinimumHeight(40);
    return b;
}

AdminDashboard::AdminDashboard(const QString &username, QWidget *parent)
    : QMainWindow(parent), currentUser(username) {
    setWindowTitle("Admin Dashboard - " + username);
    resize(900, 650);

    auto *central = new QWidget(this);
    auto *root    = new QVBoxLayout(central);

    auto *welcome = new QLabel("Welcome, " + username, central);
    QFont wf = welcome->font();
    wf.setPointSize(14);
    wf.setBold(true);
    welcome->setFont(wf);
    root->addWidget(welcome);

    auto *tabs = new QTabWidget(central);

    // -------- Patients tab --------
    auto *patTab = new QWidget(tabs);
    auto *patGrid = new QGridLayout(patTab);
    auto *bRP  = mkBtn("Register Patient",      patTab);
    auto *bVP  = mkBtn("View All Patients",     patTab);
    auto *bUP  = mkBtn("Update Patient",        patTab);
    auto *bMR  = mkBtn("View Medical Records",  patTab);
    patGrid->addWidget(bRP, 0, 0); patGrid->addWidget(bVP, 0, 1);
    patGrid->addWidget(bUP, 1, 0); patGrid->addWidget(bMR, 1, 1);
    tabs->addTab(patTab, "Patients");

    // -------- Staff/Doctors tab --------
    auto *sdTab = new QWidget(tabs);
    auto *sdGrid = new QGridLayout(sdTab);
    auto *bRS  = mkBtn("Register Staff",        sdTab);
    auto *bVS  = mkBtn("View All Staff",        sdTab);
    auto *bUS  = mkBtn("Update Staff",          sdTab);
    auto *bRD  = mkBtn("Register Doctor",       sdTab);
    auto *bVD  = mkBtn("View All Doctors",      sdTab);
    auto *bUD  = mkBtn("Update Doctor",         sdTab);
    auto *bDA  = mkBtn("View Doctor Appts",     sdTab);
    sdGrid->addWidget(bRS, 0, 0); sdGrid->addWidget(bVS, 0, 1); sdGrid->addWidget(bUS, 0, 2);
    sdGrid->addWidget(bRD, 1, 0); sdGrid->addWidget(bVD, 1, 1); sdGrid->addWidget(bUD, 1, 2);
    sdGrid->addWidget(bDA, 2, 0);
    tabs->addTab(sdTab, "Staff/Doctors");

    // -------- Billing/Rooms tab --------
    auto *brTab = new QWidget(tabs);
    auto *brGrid = new QGridLayout(brTab);
    auto *bSPB = mkBtn("Show Patient Bill",     brTab);
    auto *bSAB = mkBtn("Show All Bills",        brTab);
    auto *bSEB = mkBtn("Set Patient Bill",      brTab);
    auto *bUPB = mkBtn("Update Patient Bill",   brTab);
    auto *bDP  = mkBtn("Discharge Patient",     brTab);
    auto *bAR  = mkBtn("Assign Room",           brTab);
    brGrid->addWidget(bSPB, 0, 0); brGrid->addWidget(bSAB, 0, 1);
    brGrid->addWidget(bSEB, 1, 0); brGrid->addWidget(bUPB, 1, 1);
    brGrid->addWidget(bDP,  2, 0); brGrid->addWidget(bAR,  2, 1);
    tabs->addTab(brTab, "Billing/Rooms");

    // -------- Pharmacy tab --------
    auto *phTab = new QWidget(tabs);
    auto *phGrid = new QGridLayout(phTab);
    auto *bVPh = mkBtn("View Pharmacy",         phTab);
    auto *bAM  = mkBtn("Add Medicine",          phTab);
    auto *bIPr = mkBtn("Issue Prescription",    phTab);
    auto *bSPr = mkBtn("Search Pharm Records",  phTab);
    auto *bLS  = mkBtn("View Low Stock",        phTab);
    auto *bAPr = mkBtn("View All Prescr.",      phTab);
    auto *bRM  = mkBtn("Restock Medicine",      phTab);
    phGrid->addWidget(bVPh,0,0); phGrid->addWidget(bAM, 0,1); phGrid->addWidget(bIPr,0,2);
    phGrid->addWidget(bSPr,1,0); phGrid->addWidget(bLS, 1,1); phGrid->addWidget(bAPr,1,2);
    phGrid->addWidget(bRM, 2,0);
    tabs->addTab(phTab, "Pharmacy");

    // -------- Ambulance tab --------
    auto *amTab = new QWidget(tabs);
    auto *amGrid = new QGridLayout(amTab);
    auto *bRAm = mkBtn("Register Ambulance",    amTab);
    auto *bVAm = mkBtn("View Ambulances",       amTab);
    auto *bUAm = mkBtn("Update Ambulance",      amTab);
    amGrid->addWidget(bRAm, 0, 0); amGrid->addWidget(bVAm, 0, 1); amGrid->addWidget(bUAm, 0, 2);
    tabs->addTab(amTab, "Ambulance");

    // -------- System tab --------
    auto *sysTab = new QWidget(tabs);
    auto *sysGrid = new QGridLayout(sysTab);
    auto *bRA  = mkBtn("Register Admin",        sysTab);
    auto *bUC  = mkBtn("Update Credentials",    sysTab);
    sysGrid->addWidget(bRA, 0, 0); sysGrid->addWidget(bUC, 0, 1);
    tabs->addTab(sysTab, "System");

    root->addWidget(tabs);

    auto *btnLogout = new QPushButton("Logout", central);
    btnLogout->setMinimumHeight(36);
    btnLogout->setMinimumWidth(150);
    
    // Create a horizontal layout to center the logout button
    auto *logoutLayout = new QHBoxLayout();
    logoutLayout->addStretch();
    logoutLayout->addWidget(btnLogout);
    logoutLayout->addStretch();
    
    root->addLayout(logoutLayout);

    setCentralWidget(central);

    // Connections
    connect(bRP,  &QPushButton::clicked, this, &AdminDashboard::onRegisterPatient);
    connect(bVP,  &QPushButton::clicked, this, &AdminDashboard::onViewPatients);
    connect(bUP,  &QPushButton::clicked, this, &AdminDashboard::onUpdatePatient);
    connect(bMR,  &QPushButton::clicked, this, &AdminDashboard::onViewMedicalRecords);
    connect(bRS,  &QPushButton::clicked, this, &AdminDashboard::onRegisterStaff);
    connect(bVS,  &QPushButton::clicked, this, &AdminDashboard::onViewStaff);
    connect(bUS,  &QPushButton::clicked, this, &AdminDashboard::onUpdateStaff);
    connect(bRD,  &QPushButton::clicked, this, &AdminDashboard::onRegisterDoctor);
    connect(bVD,  &QPushButton::clicked, this, &AdminDashboard::onViewDoctors);
    connect(bUD,  &QPushButton::clicked, this, &AdminDashboard::onUpdateDoctor);
    connect(bDA,  &QPushButton::clicked, this, &AdminDashboard::onViewDoctorAppointments);
    connect(bSPB, &QPushButton::clicked, this, &AdminDashboard::onShowPatientBill);
    connect(bSAB, &QPushButton::clicked, this, &AdminDashboard::onShowAllBills);
    connect(bSEB, &QPushButton::clicked, this, &AdminDashboard::onSetPatientBill);
    connect(bUPB, &QPushButton::clicked, this, &AdminDashboard::onUpdatePatientBill);
    connect(bDP,  &QPushButton::clicked, this, &AdminDashboard::onDischargePatient);
    connect(bAR,  &QPushButton::clicked, this, &AdminDashboard::onAssignRoom);
    connect(bVPh, &QPushButton::clicked, this, &AdminDashboard::onViewPharmacy);
    connect(bAM,  &QPushButton::clicked, this, &AdminDashboard::onAddMedicine);
    connect(bIPr, &QPushButton::clicked, this, &AdminDashboard::onIssuePrescription);
    connect(bSPr, &QPushButton::clicked, this, &AdminDashboard::onSearchPharmacyRecords);
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