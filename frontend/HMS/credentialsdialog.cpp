#include "CredentialsDialog.h"

#include <QFormLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QMessageBox>
#include <fstream>
#include <cstdio>

CredentialsDialog::CredentialsDialog(QWidget *parent) : QDialog(parent) {
    setWindowTitle("Update Credentials");
    resize(380, 180);

    txtCnic     = new QLineEdit(this);
    cmbField    = new QComboBox(this); cmbField->addItems({"Username","Password"});
    txtNewValue = new QLineEdit(this); txtNewValue->setEchoMode(QLineEdit::Password);

    connect(cmbField, &QComboBox::currentTextChanged, this, [this](const QString &t){
        txtNewValue->setEchoMode(t == "Password" ? QLineEdit::Password : QLineEdit::Normal);
    });

    auto *form = new QFormLayout();
    form->addRow("CNIC:",      txtCnic);
    form->addRow("Field:",     cmbField);
    form->addRow("New Value:", txtNewValue);

    auto *btnApply  = new QPushButton("Apply", this);
    auto *btnCancel = new QPushButton("Cancel", this);
    auto *btnRow = new QHBoxLayout();
    btnRow->addStretch(); btnRow->addWidget(btnCancel); btnRow->addWidget(btnApply);

    auto *root = new QVBoxLayout(this);
    root->addLayout(form);
    root->addLayout(btnRow);

    connect(btnApply,  &QPushButton::clicked, this, &CredentialsDialog::onApply);
    connect(btnCancel, &QPushButton::clicked, this, &QDialog::reject);
}

void CredentialsDialog::onApply() {
    QString cnic = txtCnic->text().trimmed();
    int sel = cmbField->currentIndex();
    QString val = txtNewValue->text();
    if (cnic.isEmpty() || val.isEmpty()) {
        QMessageBox::warning(this, "Missing", "Enter CNIC and value.");
        return;
    }

    std::ifstream fin("Users.txt");
    std::ofstream fout("Users_temp.txt");
    std::string ln;
    bool found = false;
    while (std::getline(fin, ln)) {
        if (ln != "----------") continue;
        std::string c, u, p, r;
        std::getline(fin, c); std::getline(fin, u);
        std::getline(fin, p); std::getline(fin, r);
        if (c == cnic.toStdString()) {
            found = true;
            if (sel == 0) u = val.toStdString();
            else          p = val.toStdString();
        }
        fout << "----------\n" << c << "\n" << u << "\n" << p << "\n" << r << "\n";
    }
    fin.close(); fout.close();
    std::remove("Users.txt");
    std::rename("Users_temp.txt", "Users.txt");

    if (found) { QMessageBox::information(this, "Done", "Credentials updated."); accept(); }
    else       { QMessageBox::warning(this, "Not found", "CNIC not found."); }
}