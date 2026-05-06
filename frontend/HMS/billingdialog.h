#ifndef BILLINGDIALOG_H
#define BILLINGDIALOG_H

#include <QDialog>
#include <QString>
#include <QLineEdit>
#include <QPlainTextEdit>
#include <QPushButton>

class BillingDialog : public QDialog {
    Q_OBJECT
public:
    enum Mode { SHOW_ONE, SHOW_ALL, SET_BILL, UPDATE_STATUS };
    explicit BillingDialog(Mode m, QWidget *parent = nullptr);

private slots:
    void onAction();

private:
    Mode mode;
    QLineEdit      *txtPatientId;
    QPlainTextEdit *txtOutput;
    QPushButton    *btnAction;
};

#endif