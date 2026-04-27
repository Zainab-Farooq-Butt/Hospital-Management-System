    Pharmacy();
    ~Pharmacy() {
        delete[]inventory;
        delete[]records;
    }
    void loadInventory();
    void saveInventory();
    void displayInventory() const;
    void searchByPatient(string patientID) const;
    void issuePrescription(string pID, string medName, int qty);
