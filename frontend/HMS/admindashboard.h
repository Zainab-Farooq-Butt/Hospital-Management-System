#ifndef ADMINDASHBOARD_H
#define ADMINDASHBOARD_H

#include <QMainWindow>
#include <QString>

class AdminDashboard : public QMainWindow {
    Q_OBJECT
public:
    explicit AdminDashboard(const QString &username, QWidget *parent = nullptr);

private slots:
    void onRegisterPatient();
    void onViewPatients();
    void onUpdatePatient();
    void onViewMedicalRecords();
    void onRegisterStaff();
    void onViewStaff();
    void onUpdateStaff();
    void onRegisterDoctor();
    void onViewDoctors();
    void onUpdateDoctor();
    void onViewDoctorAppointments();
    void onRegisterAdmin();
    void onUpdateCredentials();
    void onShowPatientBill();
    void onShowAllBills();
    void onSetPatientBill();
    void onUpdatePatientBill();
    void onDischargePatient();
    void onAssignRoom();
    void onViewPharmacy();
    void onAddMedicine();
    void onIssuePrescription();
    void onSearchPharmacyRecords();
    void onViewLowStock();
    void onViewAllPrescriptions();
    void onRestockMedicine();
    void onRegisterAmbulance();
    void onViewAmbulances();
    void onUpdateAmbulance();
    void onLogout();

private:
    QString currentUser;
<<<<<<< HEAD
=======
    QString loggedCNIC;
    void resolveAdminIdentity();
>>>>>>> origin/zainab
};

#endif