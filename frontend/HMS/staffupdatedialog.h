#ifndef STAFFUPDATEDIALOG_H
#define STAFFUPDATEDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QComboBox>

class StaffUpdateDialog : public QDialog {
    Q_OBJECT
public:
    explicit StaffUpdateDialog(QWidget *parent = nullptr);

private slots:
    void onApply();

private:
    QLineEdit *txtCnic, *txtValue;
    QComboBox *cmbField;
    void rewritePerson(const QString &targetCnic, int field, const QString &val, int newAge);
    void rewriteStaff(const QString &targetCnic, int field, const QString &val, double newSalary);
};

#endif