#include "RestockDialog.h"
#include "../../Pharmacy.h"

#include <QFormLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QMessageBox>
#include <sstream>
#include <iostream>

RestockDialog::RestockDialog(QWidget *parent) : QDialog(parent) {
    setWindowTitle("Restock Medicine");
    resize(380, 180);

    txtMedicine = new QLineEdit(this);
    spinQty     = new QSpinBox(this); spinQty->setRange(1, 100000);

    auto *form = new QFormLayout();
    form->addRow("Medicine:", txtMedicine);
    form->addRow("Add Qty:",  spinQty);

    auto *btnRestock = new QPushButton("Restock", this);
    auto *btnCancel  = new QPushButton("Cancel", this);
    auto *btnRow = new QHBoxLayout();
    btnRow->addStretch(); btnRow->addWidget(btnCancel); btnRow->addWidget(btnRestock);

    auto *root = new QVBoxLayout(this);
    root->addLayout(form);
    root->addLayout(btnRow);

    connect(btnRestock, &QPushButton::clicked, this, &RestockDialog::onRestock);
    connect(btnCancel,  &QPushButton::clicked, this, &QDialog::reject);
}

void RestockDialog::onRestock() {
    QString name = txtMedicine->text().trimmed();
    int qty      = spinQty->value();
    if (name.isEmpty() || qty <= 0) {
        QMessageBox::warning(this, "Invalid", "Enter name and qty > 0."); return;
    }

    Pharmacy ph;
    ph.loadInventory();
    std::stringstream buf;
    std::streambuf *old = std::cout.rdbuf(buf.rdbuf());
    ph.updateStock(name.toStdString(), qty);
    std::cout.rdbuf(old);

    QMessageBox::information(this, "Done", QString::fromStdString(buf.str()));
    accept();
}