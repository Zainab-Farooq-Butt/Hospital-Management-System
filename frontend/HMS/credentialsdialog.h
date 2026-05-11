#ifndef CREDENTIALSDIALOG_H
#define CREDENTIALSDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QComboBox>

class CredentialsDialog : public QDialog {
    Q_OBJECT
public:
    explicit CredentialsDialog(const QString &cnic = "", QWidget *parent = nullptr);

private slots:
    void onApply();

private:
    QLineEdit *txtCnic, *txtNewValue;
    QComboBox *cmbField;
    QString fixedCnic;
};

#endif