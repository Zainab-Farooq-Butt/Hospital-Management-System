#ifndef MEDICALRECORDADDDIALOG_H
#define MEDICALRECORDADDDIALOG_H

#include <QDialog>
#include <QString>
#include <QLineEdit>
#include <QLabel>

class MedicalRecordAddDialog : public QDialog {
    Q_OBJECT
public:
    explicit MedicalRecordAddDialog(const QString &doctorId, QWidget *parent = nullptr);

private slots:
    void onSave();

private:
    QString doctorId;
    QLabel    *lblDoctor;
    QLineEdit *txtPatientId, *txtDiagnosis, *txtTreatment, *txtCost, *txtDate;
};

#endif