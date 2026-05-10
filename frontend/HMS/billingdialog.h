#ifndef BILLINGDIALOG_H
#define BILLINGDIALOG_H

#include <QDialog>
#include <QString>
#include <QLineEdit>
#include <QTableWidget>
#include <QLabel>
#include <QPushButton>

class BillingDialog : public QDialog {
    Q_OBJECT
public:
    enum Mode { SHOW_ONE, SHOW_ALL, SET_BILL, UPDATE_STATUS };
    explicit BillingDialog(Mode m, QWidget *parent = nullptr);

private slots:
    void onAction();

private:
    void loadBills(const std::string& filterPid = "");
    Mode mode;
    QLineEdit      *txtPatientId;
    QLabel         *lblPatientId;
    QTableWidget   *table;
    QPushButton    *btnAction;
};

#endif