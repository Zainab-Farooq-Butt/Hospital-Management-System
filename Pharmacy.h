#include <fstream>
#include <iostream>
using namespace std;
class Pharmacy {
private:
    struct Prescription {
        string patientID;
        string medicineName;
        int quantity;
        double totalCost;
        string dateIssued;
    };
    Medicine* inventory;
    Prescription* records;
    int medicineCount;
    int recordCount;
    // We can use a struct for the Prescription history to keep it simple 
public:
    Pharmacy();
    ~Pharmacy();
    void AddMedicine(Medicine* m);
    void loadInventory();
    void saveInventory();
    void displayInventory() const;
    void searchByPatient(string patientID) const; 
    void issuePrescription(string pID, string medName, int qty);
};