#include <Pharmacy.h>
#include <Medicine.h>

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
    void loadInventory(){
        ifstream infile("Medicine.txt");
        if (!infile) return;
        while (true) {
            Medicine tempM;
            if (temp.fileInput(infile)) {
                this->AddMedicine(&temp);
            }
            else break;
        }
        infile.close();
    }
    void saveInventory(){
        ofstream outfile("Medicine.txt");
        for (int i = 0; i < medicineCount; i++) {
            outfile << inventory[medicineCount].getName() << endl;
            outfile << inventory[medicineCount].getDosage() << endl;
            outfile << inventory[medicineCount].getStock() << endl;
            outfile << inventory[medicineCount].getPrice() << endl;
            outfile << inventory[medicineCount].getIssueDate() << endl;
            outfile << inventory[medicineCount].getExpiryDate() << endl;
        }
        outfile.close();
    }
    void display() const{
    
    }
    void searchPatient(string patientID) const{}
    void prescriptionIssue(string pID, string medName, int qty){}
