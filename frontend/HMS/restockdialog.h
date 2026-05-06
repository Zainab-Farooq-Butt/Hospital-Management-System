#ifndef RESTOCKDIALOG_H
#define RESTOCKDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QSpinBox>

class RestockDialog : public QDialog {
    Q_OBJECT
public:
    explicit RestockDialog(QWidget *parent = nullptr);

private slots:
    void onRestock();

private:
    QLineEdit *txtMedicine;
    QSpinBox  *spinQty;
};

#endif