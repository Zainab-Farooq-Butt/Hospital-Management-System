#ifndef ADDMEDICINEDIALOG_H
#define ADDMEDICINEDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QSpinBox>
#include <QDoubleSpinBox>

class AddMedicineDialog : public QDialog {
    Q_OBJECT
public:
    explicit AddMedicineDialog(QWidget *parent = nullptr);

private slots:
    void onAdd();

private:
    QLineEdit *txtName, *txtDosage;
    QSpinBox  *spinStock;
    QDoubleSpinBox *spinPrice;
};

#endif