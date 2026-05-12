#ifndef CREDENTIALSDIALOG_H
#define CREDENTIALSDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QComboBox>

class CredentialsDialog : public QDialog {
    Q_OBJECT
public:
<<<<<<< HEAD
    explicit CredentialsDialog(QWidget *parent = nullptr);
=======
    explicit CredentialsDialog(const QString &cnic = "", QWidget *parent = nullptr);
>>>>>>> origin/zainab

private slots:
    void onApply();

private:
    QLineEdit *txtCnic, *txtNewValue;
    QComboBox *cmbField;
<<<<<<< HEAD
=======
    QString fixedCnic;
>>>>>>> origin/zainab
};

#endif