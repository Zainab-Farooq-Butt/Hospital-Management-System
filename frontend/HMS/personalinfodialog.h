#ifndef PERSONALINFODIALOG_H
#define PERSONALINFODIALOG_H

#include <QDialog>
#include <QString>
#include <QPlainTextEdit>

class PersonalInfoDialog : public QDialog {
    Q_OBJECT
public:
    enum Mode { PATIENT_VIEW, DOCTOR_VIEW };
    explicit PersonalInfoDialog(Mode m, const QString &cnic, QWidget *parent = nullptr);

private:
    QPlainTextEdit *txtInfo;
};

#endif