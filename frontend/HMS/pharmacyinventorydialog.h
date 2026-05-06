#ifndef PHARMACYINVENTORYDIALOG_H
#define PHARMACYINVENTORYDIALOG_H

#include <QDialog>
#include <QTableWidget>

class PharmacyInventoryDialog : public QDialog {
    Q_OBJECT
public:
    enum Mode { ALL, LOW_STOCK_ONLY };
    explicit PharmacyInventoryDialog(Mode m, QWidget *parent = nullptr);

private:
    QTableWidget *table;
};

#endif