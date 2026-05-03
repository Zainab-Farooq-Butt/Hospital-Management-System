#ifndef CREDENTIALSDIALOG_H
#define CREDENTIALSDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QComboBox>

class CredentialsDialog : public QDialog {
    Q_OBJECT
public:
    explicit CredentialsDialog(QWidget *parent = nullptr);

private slots:
    void onApply();

private:
    QLineEdit *txtCnic, *txtNewValue;
    QComboBox *cmbField;
};

#endif