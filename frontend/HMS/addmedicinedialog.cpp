#include "AddMedicineDialog.h"
#include "../../Pharmacy.h"
#include "../../Medicine.h"

#include <QFormLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QMessageBox>

AddMedicineDialog::AddMedicineDialog(QWidget *parent) : QDialog(parent) {
    setWindowTitle("Add Medicine");
    resize(380, 250);

    txtName   = new QLineEdit(this);
    txtDosage = new QLineEdit(this); txtDosage->setPlaceholderText("e.g. 500mg or 10ml");
    spinStock = new QSpinBox(this); spinStock->setRange(0, 100000);
    spinPrice = new QDoubleSpinBox(this); spinPrice->setRange(0, 1000000);

    auto *form = new QFormLayout();
    form->addRow("Name:",   txtName);
    form->addRow("Dosage:", txtDosage);
    form->addRow("Stock:",  spinStock);
    form->addRow("Price:",  spinPrice);

    auto *btnAdd    = new QPushButton("Add", this);
    auto *btnCancel = new QPushButton("Cancel", this);
    auto *btnRow = new QHBoxLayout();
    btnRow->addStretch(); btnRow->addWidget(btnCancel); btnRow->addWidget(btnAdd);

    auto *root = new QVBoxLayout(this);
    root->addLayout(form);
    root->addLayout(btnRow);

    connect(btnAdd,    &QPushButton::clicked, this, &AddMedicineDialog::onAdd);
    connect(btnCancel, &QPushButton::clicked, this, &QDialog::reject);
}

void AddMedicineDialog::onAdd() {
    QString name   = txtName->text().trimmed();
    QString dosage = txtDosage->text().trimmed();
    int stock      = spinStock->value();
    double price   = spinPrice->value();

    Pharmacy ph;
    ph.loadInventory();

    if (ph.medicineNameExists(name.toStdString())) {
        QMessageBox::warning(this, "Duplicate",
                             "Medicine '" + name + "' already exists. Use Restock instead.");
        return;
    }

    Medicine m;
    if (!m.isValidName(name.toStdString()))     { QMessageBox::warning(this,"Invalid","Bad name."); return; }
    if (!m.isValidDosage(dosage.toStdString())) { QMessageBox::warning(this,"Invalid","Bad dosage."); return; }
    if (!m.isValidQuantity(stock))              { QMessageBox::warning(this,"Invalid","Bad stock."); return; }
    if (!m.isValidPrice(price))                 { QMessageBox::warning(this,"Invalid","Bad price."); return; }

    m.setName(name.toStdString());
    m.setDosage(dosage.toStdString());
    m.setStock(stock);
    m.setPrice(price);

    ph.AddMedicine(&m);
    ph.saveInventory();

    QMessageBox::information(this, "Added", "Medicine added.");
    accept();
}