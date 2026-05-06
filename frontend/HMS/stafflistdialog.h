#ifndef STAFFLISTDIALOG_H
#define STAFFLISTDIALOG_H

#include <QDialog>
#include <QTableWidget>

class StaffListDialog : public QDialog {
    Q_OBJECT
public:
    explicit StaffListDialog(QWidget *parent = nullptr);

private:
    QTableWidget *table;
    void loadStaff();
};

#endif