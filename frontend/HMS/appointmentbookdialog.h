#ifndef APPOINTMENTBOOKDIALOG_H
#define APPOINTMENTBOOKDIALOG_H

#include <QDialog>
#include <QString>
#include <QLineEdit>
#include <QLabel>

#include <QComboBox>
#include <QDateEdit>

class AppointmentBookDialog : public QDialog {
    Q_OBJECT
public:
    explicit AppointmentBookDialog(const QString &patientId, QWidget *parent = nullptr);

private slots:
    void onBook();
    void onDoctorChanged(int index);

private:
    struct DoctorInfo {
        QString id;
        QString name;
        QString schedule;
        QString status;
        DoctorInfo(const QString &i, const QString &n, const QString &s, const QString &st)
            : id(i), name(n), schedule(s), status(st) {}
    };
    QList<DoctorInfo> doctorList;

    QString patientId;
    QLabel    *lblPatient, *lblAvailability;
    QComboBox *cmbDoctor, *cmbSlot;
    QDateEdit *dateEdit;
    QLineEdit *txtReason;

    void loadDoctors();
};

#endif