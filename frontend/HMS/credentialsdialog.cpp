#include "CredentialsDialog.h"

#include <QFormLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QMessageBox>
#include <QLineEdit>
#include <QComboBox>

#include <fstream>
#include <cstdio>

CredentialsDialog::CredentialsDialog(const QString& cnic, QWidget* parent)
    : QDialog(parent), fixedCnic(cnic)
{
    setWindowTitle("Update Credentials");
    resize(380, 180);

    txtCnic = new QLineEdit(this);
    txtCnic->setText(fixedCnic);
    txtCnic->setReadOnly(true);

    cmbField = new QComboBox(this);
    cmbField->addItems({ "Username", "Password" });

    txtNewValue = new QLineEdit(this);
    txtNewValue->setEchoMode(QLineEdit::Normal);

    connect(cmbField, &QComboBox::currentTextChanged,
        this, [this](const QString& t) {

            txtNewValue->setEchoMode(
                t == "Password" ? QLineEdit::Password : QLineEdit::Normal
            );

            txtNewValue->clear();
            txtNewValue->setPlaceholderText(
                t == "Password" ? "Enter new password"
                : "Enter new username"
            );
        });

    auto* form = new QFormLayout();

    form->addRow("CNIC:", txtCnic);
    form->addRow("Field to Update:", cmbField);
    form->addRow("New Value:", txtNewValue);

    auto* btnApply = new QPushButton("Apply", this);
    auto* btnCancel = new QPushButton("Cancel", this);

    auto* btnRow = new QHBoxLayout();
    btnRow->addStretch();
    btnRow->addWidget(btnCancel);
    btnRow->addWidget(btnApply);

    auto* root = new QVBoxLayout(this);
    root->addLayout(form);
    root->addLayout(btnRow);

    connect(btnApply, &QPushButton::clicked,
        this, &CredentialsDialog::onApply);

    connect(btnCancel, &QPushButton::clicked,
        this, &QDialog::reject);
}

void CredentialsDialog::onApply()
{
    QString cnic = txtCnic->text().trimmed();
    QString val = txtNewValue->text();

    int sel = cmbField->currentIndex();

    if (cnic.isEmpty() || val.isEmpty()) {
        QMessageBox::warning(this, "Missing", "Fill all fields.");
        return;
    }

    std::ifstream fin("Users.txt");
    std::ofstream fout("Users_temp.txt");

    std::string ln;
    bool found = false;

    while (std::getline(fin, ln)) {
        if (ln != "----------") continue;

        std::string c, u, p, r;
        std::getline(fin, c);
        std::getline(fin, u);
        std::getline(fin, p);
        std::getline(fin, r);

        if (c == cnic.toStdString()) {
            found = true;

            if (sel == 0)
                u = val.toStdString();
            else
                p = val.toStdString();
        }

        fout << "----------\n"
            << c << "\n"
            << u << "\n"
            << p << "\n"
            << r << "\n";
    }

    fin.close();
    fout.close();

    std::remove("Users.txt");
    std::rename("Users_temp.txt", "Users.txt");

    if (found) {
        QMessageBox::information(this, "Success",
            "Credentials updated.");
        accept();
    }
    else {
        QMessageBox::warning(this, "Error",
            "User not found.");
    }
}