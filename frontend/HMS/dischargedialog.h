#ifndef DISCHARGEDIALOG_H
#define DISCHARGEDIALOG_H

#include <QDialog>
#include <QLineEdit>

class DischargeDialog : public QDialog {
    Q_OBJECT
public:
    explicit DischargeDialog(QWidget *parent = nullptr);

private slots:
    void onDischarge();

private:
    QLineEdit *txtPatientId, *txtDischargeDate;
};

#endif