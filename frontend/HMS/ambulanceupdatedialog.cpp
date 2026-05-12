#include "AmbulanceUpdateDialog.h"
#include "../../Ambulance.h"
#include <QFormLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <fstream>
#include <cstdio>

AmbulanceUpdateDialog::AmbulanceUpdateDialog(QWidget *parent) : QDialog(parent) {
    setWindowTitle("Update Ambulance Details");
    setMinimumWidth(400);

    txtAmbulanceId = new QLineEdit(this);
    txtAmbulanceId->setPlaceholderText("e.g., A-0001");

    cmbField = new QComboBox(this);
    cmbField->addItems({
        "Availability (1=Yes, 0=No)",
        "Destination"
    });

    txtValue = new QLineEdit(this);

    auto *form = new QFormLayout();
    form->addRow("Ambulance ID:", txtAmbulanceId);
    form->addRow("Field to Update:", cmbField);
    form->addRow("New Value:", txtValue);

    auto *btnApply = new QPushButton("Apply Change", this);
    auto *btnCancel = new QPushButton("Cancel", this);
    
    auto *btnRow = new QHBoxLayout();
    btnRow->addStretch();
    btnRow->addWidget(btnCancel);
    btnRow->addWidget(btnApply);

    auto *root = new QVBoxLayout(this);
    root->addLayout(form);
    root->addSpacing(10);
    root->addLayout(btnRow);

    connect(btnApply, &QPushButton::clicked, this, &AmbulanceUpdateDialog::onApply);
    connect(btnCancel, &QPushButton::clicked, this, &QDialog::reject);
}

void AmbulanceUpdateDialog::onApply() {
    QString id = txtAmbulanceId->text().trimmed();
    QString val = txtValue->text().trimmed();
    int idx = cmbField->currentIndex();

    if (id.isEmpty() || val.isEmpty()) {
        QMessageBox::warning(this, "Empty Fields", "Please provide both ID and New Value.");
        return;
    }

    // Basic Validation
    Ambulance a;
    if (!a.isValidAmbulanceId(id.toStdString())) {
        QMessageBox::warning(this, "Invalid ID", "Invalid Ambulance ID format (A-XXXX).");
        return;
    }
    
    // Check if ID exists
    std::ifstream check("Ambulance.txt");
    std::string line;
    bool found = false;
    while (std::getline(check, line)) {
        if (line == id.toStdString()) { found = true; break; }
    }
    check.close();

    if (!found) {
        QMessageBox::warning(this, "Not Found", "Ambulance ID " + id + " does not exist.");
        return;
    }

    rewriteAmbulance(id, idx, val);
    QMessageBox::information(this, "Success", "Ambulance record updated successfully.");
    accept();
}

void AmbulanceUpdateDialog::rewriteAmbulance(const QString &targetId, int field, const QString &val) {
    std::ifstream fin("Ambulance.txt");
    std::ofstream fout("Ambulance_temp.txt");
    std::string ln;

    while (std::getline(fin, ln)) {
        if (ln == "----------") {
            fout << "----------\n";
            std::string id, avail, driver, plate, dest;
            std::getline(fin, id);
            std::getline(fin, avail);
            std::getline(fin, driver);
            std::getline(fin, plate);
            std::getline(fin, dest);

            if (id == targetId.toStdString()) {
                fout << id << "\n";
                fout << (field == 0 ? val.toStdString() : avail) << "\n";
                fout << driver << "\n";
                fout << plate << "\n";
                fout << (field == 1 ? val.toStdString() : dest) << "\n";
            } else {
                fout << id << "\n" << avail << "\n" << driver << "\n" << plate << "\n" << dest << "\n";
            }
        }
    }
    fin.close(); fout.close();
    std::remove("Ambulance.txt");
    if (std::rename("Ambulance_temp.txt", "Ambulance.txt") != 0) {
        std::remove("Ambulance.txt");
        std::rename("Ambulance_temp.txt", "Ambulance.txt");
    }
}
