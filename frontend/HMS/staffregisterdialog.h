#ifndef STAFFREGISTERDIALOG_H
#define STAFFREGISTERDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QComboBox>

class StaffRegisterDialog : public QDialog {
    Q_OBJECT
public:
    explicit StaffRegisterDialog(QWidget *parent = nullptr);

private slots:
    void onRegister();

private:
    QLineEdit *txtCnic, *txtName, *txtPhone, *txtEmail, *txtAddress;
    QLineEdit *txtDepartment, *txtJobTitle, *txtShift, *txtJoinDate;
    QSpinBox  *spinAge;
    QComboBox *cmbGender, *cmbStatus;
    QDoubleSpinBox *spinSalary;
};

#endif