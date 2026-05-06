#ifndef MEDICALRECORDSVIEWDIALOG_H
#define MEDICALRECORDSVIEWDIALOG_H

#include <QDialog>
#include <QString>
#include <QTableWidget>

class MedicalRecordsViewDialog : public QDialog {
    Q_OBJECT
public:
    explicit MedicalRecordsViewDialog(const QString &patientId, QWidget *parent = nullptr);

private:
    QTableWidget *table;
};

#endif