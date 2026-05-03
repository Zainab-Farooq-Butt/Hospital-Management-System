#ifndef PATIENTREGISTERDIALOG_H
#define PATIENTREGISTERDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QComboBox>
#include <QPlainTextEdit>

class PatientRegisterDialog : public QDialog {
    Q_OBJECT
public:
    explicit PatientRegisterDialog(QWidget *parent = nullptr);

private slots:
    void onRegister();

private:
    QLineEdit *txtCnic, *txtName, *txtPhone, *txtEmail, *txtContact, *txtUsername, *txtPassword;
    QSpinBox  *spinAge;
    QComboBox *cmbGender, *cmbBlood, *cmbType;
    QPlainTextEdit *txtAddress;
    QDoubleSpinBox *spinHeight, *spinWeight;
};

#endif