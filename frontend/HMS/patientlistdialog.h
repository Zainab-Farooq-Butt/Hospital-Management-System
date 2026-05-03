#ifndef PATIENTLISTDIALOG_H
#define PATIENTLISTDIALOG_H

#include <QDialog>
#include <QTableWidget>

class PatientListDialog : public QDialog {
    Q_OBJECT
public:
    explicit PatientListDialog(QWidget *parent = nullptr);

private:
    QTableWidget *table;
    void loadPatients();
};

#endif