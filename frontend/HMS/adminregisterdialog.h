#ifndef ADMINREGISTERDIALOG_H
#define ADMINREGISTERDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QSpinBox>
#include <QComboBox>

class AdminRegisterDialog : public QDialog {
    Q_OBJECT
public:
    explicit AdminRegisterDialog(QWidget *parent = nullptr);

private slots:
    void onRegister();

private:
    QLineEdit *txtCnic;
    QLineEdit *txtName;
    QSpinBox  *spinAge;
    QComboBox *cmbGender;
    QLineEdit *txtPhone;
    QLineEdit *txtEmail;
    QLineEdit *txtAddress;
    QLineEdit *txtUsername;
    QLineEdit *txtPassword;
};

#endif // ADMINREGISTERDIALOG_H
