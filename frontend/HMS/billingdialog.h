#pragma once

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTableWidget>
#include <QString>
#include <string>

class BillingDialog : public QDialog {
    Q_OBJECT

public:
    enum Mode {
        SHOW_ONE,
        SHOW_ALL,
        SET_BILL,
        UPDATE_STATUS
    };

    explicit BillingDialog(Mode m, QWidget* parent = nullptr, const QString& patientId = "");

private slots:
    void onAction();

private:
    void loadBills(const std::string& filterPid = "");

    Mode mode;

    QLabel* lblPatientId;
    QLineEdit* txtPatientId;
    QTableWidget* table;
    QPushButton* btnAction;
};