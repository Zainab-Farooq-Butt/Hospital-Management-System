#ifndef DOCTORREGISTERDIALOG_H
#define DOCTORREGISTERDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QComboBox>

class DoctorRegisterDialog : public QDialog {
    Q_OBJECT
public:
    explicit DoctorRegisterDialog(QWidget *parent = nullptr);

private slots:
    void onRegister();

private:
    QLineEdit *txtCnic, *txtName, *txtPhone, *txtEmail, *txtAddress;
    QLineEdit *txtAvailability, *txtUsername, *txtPassword;
    QSpinBox  *spinAge, *spinExp;
    QComboBox *cmbGender, *cmbSpec, *cmbQual, *cmbStatus;
    QDoubleSpinBox *spinFee;
};

#endif