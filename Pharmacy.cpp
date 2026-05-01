#include "Pharmacy.h"
#include "edicine.h"
#include "Patient.h"

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
            outfile << inventory[i].getName() << endl;
            outfile << inventory[i].getDosage() << endl;
            outfile << inventory[i].getStock() << endl;
            outfile << inventory[i].getPrice() << endl;
            outfile << inventory[i].getIssueDate() << endl;
            outfile << inventory[i].getExpiryDate() << endl;
        }
        outfile.close();
    }
    void display() const{
        cout << "=======HOSPITAL PHARMACY INVENTORY=======" << endl;
        for (int i = 0; i < medicineCount; i++) {
            inventory[i].displayInfo();
            //check for stock >=quantity
            if (!(inventory[i] >= 10)) {
                cout << ">>>>>LOW STOCK WARNING<<<<<(" << inventory[i].getStock() << ")" << endl;
            }
        }
        cout << "=======HOSPITAL PHARMACY INVENTORY=======" << endl;
    }
    void searchPatient(const Patient& p) const{
        string Id = p.getPatientId();
        int index = -1;
        bool found = false;
        for (int i = 0; i < recordCount; i++) {
            if (records[i].patientID == Id){
                found = true;
                index = i;
                break;
                }
        }
        if (found == true) {
            cout << ">>>>>PHARMACY SEARCH RESULT FOUND<<<<<" << endl;
            cout << "Patient Id: " << Id << endl;
            cout << "Account status: " << endl;
            cout << "Last Purchase: " << records[index].medicineName << endl;
        }
        else
            cout << "Pharmacy record for " << Id << " does not exist" << endl;

        return found;
    }
    void prescriptionIssue(string pID, string medName, int qty){
        for (int i = 0; i < medicineCount; i++) {
            if (inventory[i].getName() == medName) {
                //check if stock>=quantity
                if (inventory[i] >= qty) {
                    inventory[i].setStock(getStock() - qty);//update stock

                    Prescription* newPres = new Prescription[recordCount + 1];
                    for (int j = 0; i < recordCount; j++) {
                        newPres[j] = records[j];
                    }
                    //adding new prescription
                    newPres[recordCount].patientID = pID;
                    newPres[recordCount].medicineName = medName;
                    newPres[recordCount].quantity = qty;
                    newPres[recordCount].totalcost = qty * inventory[i].getPrice();
                    newPres[recordCount].dateIssued = inventory[i].getIssueDate();

                    if (records != nullptr) delete[] records;
                    records = newPres;
                    recordCount++;
                }
                else {
                    cout << medName << " OUT OF STOCK" << endl;
                }
                return;
            }
            else {
                cout << medName << " NOT FOUND IN INVENTORY" << endl;
            }
        }
    }