#ifndef ROOMASSIGNDIALOG_H
#define ROOMASSIGNDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QComboBox>
#include <QPlainTextEdit>

class RoomAssignDialog : public QDialog {
    Q_OBJECT
public:
    explicit RoomAssignDialog(QWidget *parent = nullptr);

private slots:
    void onAssign();
    void onLoadAvailable();

private:
    QLineEdit *txtPatientId, *txtRoomId, *txtAdmitDate;
    QComboBox *cmbType;
    QPlainTextEdit *txtAvailable;
};

#endif