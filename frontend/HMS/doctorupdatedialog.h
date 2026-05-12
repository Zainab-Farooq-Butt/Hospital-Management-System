#ifndef DOCTORUPDATEDIALOG_H
#define DOCTORUPDATEDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QComboBox>

class DoctorUpdateDialog : public QDialog {
    Q_OBJECT
public:
    explicit DoctorUpdateDialog(QWidget *parent = nullptr);

private slots:
    void onApply();

private:
    QLineEdit *txtCnic, *txtValue;
    QComboBox *cmbField;
    void rewritePerson(const QString &targetCnic, int field, const QString &val, int newAge);
    void rewriteDoctor(const QString &targetCnic, int field, const QString &val, int newExp, double newFee);
};

#endif