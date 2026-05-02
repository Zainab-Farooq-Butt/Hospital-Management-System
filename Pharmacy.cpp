#include "Pharmacy.h"
#include "Medicine.h"
#include "Patient.h"
#include "Prescription.h"
#include <fstream>
#include <iostream>
using namespace std;

Pharmacy::Pharmacy() : inventory(nullptr), records(nullptr), medicineCount(0), recordCount(0) {}

Pharmacy::~Pharmacy() {
    delete[] inventory;
    delete[] records;
}

void Pharmacy::AddMedicine(Medicine* m) {
    Medicine* array = new Medicine[medicineCount + 1];
    for (int i = 0; i < medicineCount; i++) {
        array[i] = inventory[i];
    }
    array[medicineCount] = *m;
    if (inventory != nullptr) delete[] inventory;
    inventory = array;
    medicineCount++;
}

void Pharmacy::loadInventory() {
    // clear existing inventory first
    if (inventory != nullptr) {
        delete[] inventory;
        inventory = nullptr;
        medicineCount = 0;
    }

    ifstream infile("Medicine.txt");
    if (!infile) return;
    while (true) {
        Medicine tempM;
        if (tempM.fileInput(infile)) {
            this->AddMedicine(&tempM);
        }
        else break;
    }
    infile.close();
}

void Pharmacy::saveInventory() {
    ofstream outfile("Medicine.txt");
    for (int i = 0; i < medicineCount; i++) {
        outfile << "----------"                 << endl;
        outfile << inventory[i].getName()       << endl;
        outfile << inventory[i].getDosage()     << endl;
        outfile << inventory[i].getStock()      << endl;
        outfile << inventory[i].getPrice()      << endl;
    }
    outfile.close();
}

void Pharmacy::loadPrescriptions() {
    // clear existing records first
    if (records != nullptr) {
        delete[] records;
        records = nullptr;
        recordCount = 0;
    }

    ifstream infile("Prescriptions.txt");
    if (!infile) return;
    while (true) {
        Prescription tempP;
        if (tempP.fileInput(infile)) {
            Prescription* newRecs = new Prescription[recordCount + 1];
            for (int i = 0; i < recordCount; i++) {
                newRecs[i] = records[i];
            }
            newRecs[recordCount] = tempP;
            if (records != nullptr) delete[] records;
            records = newRecs;
            recordCount++;
        }
        else break;
    }
    infile.close();
}
void Pharmacy::savePrescriptions() {
    ofstream outfile("Prescriptions.txt");
    for (int i = 0; i < recordCount; i++) {
        records[i].fileOutput(outfile);
    }
    outfile.close();
}

void Pharmacy::display() const {
    cout << "=======HOSPITAL PHARMACY INVENTORY=======" << endl;
    if (medicineCount == 0) {
        cout << "No medicines in inventory." << endl;
    }
    for (int i = 0; i < medicineCount; i++) {
        inventory[i].displayInfo();
        if (!(inventory[i] >= 10)) {
            cout << ">>>>>LOW STOCK WARNING<<<<<("
                 << inventory[i].getStock() << ")" << endl;
        }
    }
    cout << "=========================================" << endl;
}

void Pharmacy::displayLowStock() const {
    cout << "=======LOW STOCK MEDICINES=======" << endl;
    bool any = false;
    for (int i = 0; i < medicineCount; i++) {
        if (!(inventory[i] >= 10)) {
            inventory[i].displayInfo();
            cout << "Stock remaining: " << inventory[i].getStock() << endl;
            any = true;
        }
    }
    if (!any) cout << "All medicines are sufficiently stocked." << endl;
    cout << "=================================" << endl;
}

void Pharmacy::displayAllPrescriptions() const {
    cout << "=======ALL PRESCRIPTIONS=======" << endl;
    if (recordCount == 0) {
        cout << "No prescriptions issued yet." << endl;
        return;
    }
    for (int i = 0; i < recordCount; i++) {
        records[i].displayInfo();
    }
    cout << "===============================" << endl;
}

bool Pharmacy::searchPatient(const Patient& p) const {
    string Id = p.getPatientId();
    bool found = false;

    for (int i = 0; i < recordCount; i++) {
        if (records[i].getPatientID() == Id) {
            if (!found) {
                cout << ">>>>>PHARMACY SEARCH RESULT FOUND<<<<<" << endl;
                cout << "Patient ID : " << Id << endl;
                found = true;
            }
            records[i].displayInfo();
        }
    }
    if (!found)
        cout << "Pharmacy record for " << Id << " does not exist." << endl;

    return found;
}

void Pharmacy::prescriptionIssue(string pID, string medName, int qty) {
    for (int i = 0; i < medicineCount; i++) {
        if (inventory[i].getName() == medName) {
            if (inventory[i] >= qty) {
                inventory[i].setStock(inventory[i].getStock() - qty);

                Prescription* newPres = new Prescription[recordCount + 1];
                for (int j = 0; j < recordCount; j++) {
                    newPres[j] = records[j];
                }
                newPres[recordCount].setPatientID(pID);
                newPres[recordCount].setMedicineName(medName);
                newPres[recordCount].setQuantity(qty);
                newPres[recordCount].setTotalCost(qty * inventory[i].getPrice());

                if (records != nullptr) delete[] records;
                records = newPres;
                recordCount++;

                // save to file immediately after issuing
                savePrescriptions();
                saveInventory(); // stock changed so save inventory too

                cout << "Prescription issued successfully." << endl;
            }
            else {
                cout << medName << " is OUT OF STOCK." << endl;
            }
            return;
        }
    }
    cout << medName << " NOT FOUND IN INVENTORY." << endl;
}

void Pharmacy::updateStock(string medName, int qty) {
    for (int i = 0; i < medicineCount; i++) {
        if (inventory[i].getName() == medName) {
            inventory[i].setStock(inventory[i].getStock() + qty);
            cout << "Stock updated. New stock for " << medName
                 << ": " << inventory[i].getStock() << endl;
            saveInventory(); // save immediately after updating stock
            return;
        }
    }
    cout << medName << " NOT FOUND IN INVENTORY." << endl;
}