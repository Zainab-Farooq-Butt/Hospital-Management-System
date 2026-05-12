#ifndef DOCTORDASHBOARD_H
#define DOCTORDASHBOARD_H

#include <QMainWindow>
#include <QString>

class DoctorDashboard : public QMainWindow {
    Q_OBJECT

public:
    explicit DoctorDashboard(const QString& username, QWidget* parent = nullptr);

private slots:
    void onViewPersonalInfo();
    void onViewPatientRecords();
    void onAddMedicalRecord();
    void onShowAppointments();   //  KEEP THIS
    void onUpdateCredentials();
    void onLogout();

private:
    QString currentUser;
    QString loggedCNIC;
    QString doctorId;

    void resolveDoctorIdentity();
};

#endif