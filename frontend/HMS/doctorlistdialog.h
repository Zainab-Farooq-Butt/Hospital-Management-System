#ifndef DOCTORLISTDIALOG_H
#define DOCTORLISTDIALOG_H

#include <QDialog>
#include <QTableWidget>

class DoctorListDialog : public QDialog {
    Q_OBJECT
public:
    explicit DoctorListDialog(QWidget *parent = nullptr);

private:
    QTableWidget *table;
    void loadDoctors();
};

#endif