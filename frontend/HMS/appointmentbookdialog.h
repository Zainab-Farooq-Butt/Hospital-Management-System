#ifndef APPOINTMENTBOOKDIALOG_H
#define APPOINTMENTBOOKDIALOG_H

#include <QDialog>
#include <QString>
#include <QLineEdit>
#include <QLabel>

class AppointmentBookDialog : public QDialog {
    Q_OBJECT
public:
    explicit AppointmentBookDialog(const QString &patientId, QWidget *parent = nullptr);

private slots:
    void onBook();

private:
    QString patientId;
    QLabel    *lblPatient;
    QLineEdit *txtDoctorId, *txtDate, *txtTime, *txtReason;
};

#endif