#ifndef PHARMACYRECORDSDIALOG_H
#define PHARMACYRECORDSDIALOG_H

#include <QDialog>
#include <QString>
#include <QTableWidget>

class PharmacyRecordsDialog : public QDialog {
    Q_OBJECT
public:
    enum Mode { ALL_PRESCRIPTIONS, BY_PATIENT };
    explicit PharmacyRecordsDialog(Mode m, const QString &pid = "",
                                   QWidget *parent = nullptr);

private:
    QTableWidget *table;
};

#endif