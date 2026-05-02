#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "Prescription.h"
using namespace std;

class Medicine;
class Patient;

class Pharmacy {
private:
    Medicine*     inventory;
    Prescription* records;
    int           medicineCount;
    int           recordCount;

public:
    Pharmacy();
    ~Pharmacy();

    // Inventory
    void AddMedicine(Medicine* m);
    void loadInventory();
    void saveInventory();
    void updateStock(string medName, int qty);

    // Prescriptions
    void loadPrescriptions();
    void savePrescriptions();
    void prescriptionIssue(string pID, string medName, int qty);

    // Display
    void display()                  const;
    void displayLowStock()          const;
    void displayAllPrescriptions()  const;

    // Search
    bool searchPatient(const Patient& p) const;
    bool medicineAlreadyExists(string medName) const;
};