    Pharmacy():inventory(nullptr), records(nullptr),medicineCount(0),recordCount(0) {}
    ~Pharmacy() {
        delete[]inventory;
        delete[]records;
    }
    void AddMedicine(Medicine *m){
        Medicine* array = new Medicine[medicineCount + 1];
        for (int i = 0; i < medicineCount; i++) {
            array[i] = inventory[i];
        }
        array[medicineCount] = *m;
        if(inventory!=nullptr) delete[] inventory;
        inventory = array;
        medicineCount++;
    }
    void loadInventory(){}
    void saveInventory(){}
    void display() const{}
    void searchPatient(string patientID) const{}
    void prescriptionIssue(string pID, string medName, int qty){}
