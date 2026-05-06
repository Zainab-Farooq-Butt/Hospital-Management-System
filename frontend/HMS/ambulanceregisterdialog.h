#ifndef AMBULANCEREGISTERDIALOG_H
#define AMBULANCEREGISTERDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QCheckBox>

class AmbulanceRegisterDialog : public QDialog {
    Q_OBJECT
public:
    explicit AmbulanceRegisterDialog(QWidget *parent = nullptr);

private slots:
    void onRegister();

private:
    QLineEdit *txtPlate, *txtAddress;
    QCheckBox *chkAvailable;
};

#endif