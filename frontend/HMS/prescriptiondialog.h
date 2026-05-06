#ifndef PRESCRIPTIONDIALOG_H
#define PRESCRIPTIONDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QSpinBox>

class PrescriptionDialog : public QDialog {
    Q_OBJECT
public:
    explicit PrescriptionDialog(QWidget *parent = nullptr);

private slots:
    void onIssue();

private:
    QLineEdit *txtPatientId, *txtMedicine;
    QSpinBox  *spinQty;
};

#endif