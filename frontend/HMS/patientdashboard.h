#ifndef PATIENTDASHBOARD_H
#define PATIENTDASHBOARD_H

#include <QMainWindow>
#include <QString>

class PatientDashboard : public QMainWindow {
    Q_OBJECT
public:
    explicit PatientDashboard(const QString &username, QWidget *parent = nullptr);

private slots:
    void onViewPersonalInfo();
    void onViewMedicalRecords();
    void onBookAppointment();
    void onCancelAppointment();
    void onViewBill();
    void onUpdateCredentials();
    void onShowPharmacyRecords();
    void onRequestAmbulance();
    void onLogout();

private:
    QString currentUser;
    QString loggedCNIC;
    QString patientId;

    void resolvePatientIdentity();
};

#endif