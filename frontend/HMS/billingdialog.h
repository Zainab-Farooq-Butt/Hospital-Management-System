#ifndef BILLINGDIALOG_H
#define BILLINGDIALOG_H

#include <QDialog>
#include <QString>
#include <QLineEdit>
<<<<<<< HEAD
#include <QPlainTextEdit>
=======
#include <QTableWidget>
#include <QLabel>
>>>>>>> origin/zainab
#include <QPushButton>

class BillingDialog : public QDialog {
    Q_OBJECT
public:
    enum Mode { SHOW_ONE, SHOW_ALL, SET_BILL, UPDATE_STATUS };
<<<<<<< HEAD
    explicit BillingDialog(Mode m, QWidget *parent = nullptr);
=======
    explicit BillingDialog(Mode m, QWidget *parent = nullptr, const QString &preloadPatientId = "");
>>>>>>> origin/zainab

private slots:
    void onAction();

private:
<<<<<<< HEAD
    Mode mode;
    QLineEdit      *txtPatientId;
    QPlainTextEdit *txtOutput;
=======
    void loadBills(const std::string& filterPid = "");
    Mode mode;
    QLineEdit      *txtPatientId;
    QLabel         *lblPatientId;
    QTableWidget   *table;
>>>>>>> origin/zainab
    QPushButton    *btnAction;
};

#endif