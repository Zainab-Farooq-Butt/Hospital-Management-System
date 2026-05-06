#ifndef APPOINTMENTLISTDIALOG_H
#define APPOINTMENTLISTDIALOG_H

#include <QDialog>
#include <QString>
#include <QTableWidget>

class AppointmentListDialog : public QDialog {
    Q_OBJECT
public:
    enum Filter { ALL, BY_DOCTOR, BY_PATIENT };
    explicit AppointmentListDialog(Filter f, const QString &id, QWidget *parent = nullptr);

private slots:
    void onCancelSelected();

private:
    Filter filter;
    QString filterId;
    QTableWidget *table;
    void load();
};

#endif