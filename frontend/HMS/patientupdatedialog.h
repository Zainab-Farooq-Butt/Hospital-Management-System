#ifndef PATIENTUPDATEDIALOG_H
#define PATIENTUPDATEDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QComboBox>

class PatientUpdateDialog : public QDialog {
    Q_OBJECT
public:
    explicit PatientUpdateDialog(QWidget *parent = nullptr);

private slots:
    void onApply();

private:
    QLineEdit *txtCnic, *txtValue;
    QComboBox *cmbField;
    void rewritePerson(const QString &targetCnic, int field, const QString &val, int newAge);
    void rewritePatient(const QString &targetCnic, int field, const QString &val, double newNum);
};

#endif