#include <Medicine.h>
    // Constructor
    Medicine::Medicine(string n = "", string d = "", int q = 0, 
    int stock = 0, double p = 0.00, string iss = "", string exp = ""):
    name(n),dosage(d),quantity(q),stockAvailability(s),price(p),issueDate(iss),expiryDate(exp){}
    ~Medicine(){}
    //Validations
    bool isValidDosage(string d) {
        if (d.length()==0) return false;
        int i = 0;
        bool isDigit = false;
        string unitOfMedicine = "";
        while (i < d.length()) {
            if (isdigit[d[i]]) {
                isDigit = true;
                i++;
            }
            else if (d[i] ==' ') {
                i++;
            }
            else
                break; // mg/MG or ml/ML 
        }
        if (!isDigit) return false;

        int j = i;
        while (j < d.length()) {
            if (d[i] != ' ') {
                unitOfMedicine += tolower(d[i]);
            }
            j++;
        }

        if (unitOfMedicine == "mg" || unitOfMedicine == "ml") return true;

        return false;

    }
    bool isValidPrice(double p) {
        return p >= 0.0;
    }
    bool isValidQuantity(int q){
        return q >= 0;
    }
    bool isValidAvailability(int s){
        return s >= 0;
    }
    bool isValidDateofIssue(string i){
        if (i.length != 10) return false;

    }
    bool isValidDateofExpiry(string e){}
    // Setters
    Medicine& Medicine::setName(string n) {}
    Medicine& Medicine::setDosage(string d) {
        if (isValidDosage(d)) {
            dosage = d;
    }
        return *this;
    }
    Medicine& Medicine::setQuantity(int q){
        if (isValidQuantity(q)) {
            quantity = q;
        }return *this;
    }
    Medicine& Medicine::setStock(int s){
        if (isValidStock(s)) {
            stockAvailability = s;
        }return *this;
    }
    Medicine& Medicine::setPrice(double p){
        if (isValidPrice(p)) {
            price = p;
    }
        return *this;
    }
    Medicine& Medicine::setExpiryDate(string e){
        if (isValidDateofExpiry(e)) {
            expiryDate = e;
        }return *this;
    }
    Medicine& Medicine::setIssueDate(string i){
        if (isValidDateofIssue(i)) {
            issueDate = i;
        }return *this;
    }

    // Getters
    string Medicine::getName() const{
        return name;
    }
    string Medicine::getDosage() const{
        return dosage;
    }
    int Medicine::getQuantity()const{
        return quantity;
    }
    int Medicine::getStock() const{
        return stockAvailability;
    }
    double Medicine::getPrice() const{
        return price;
    }
    string Medicine::getIssueDate() const{
        return issueDate;
    }
    string Medicine::getExpiryDate() const{
        return expiryDate;
    }
    //comparison
    bool operator>=(int rQty) const {
        return this->stockAvailability >= rQty;
    }
    //other Functions
    void Medicine::displayInfo() const{}
    bool Medicine::isMedicineExpired(string currentDate) const{
    
    }
    //file handling
    bool Medicine::fileInput(ifstream& myfile) {
        if (!getline(myfile, name) || name.empty())
            return false;
        string temp;
        getline(myfile, temp);
        this->setDosage(temp);
        if (!(myfile >> stockAvailability)) return false;
        if (!(myfile >> price)) return false;
        myfile.ignore(); //for clearing the new line
        getline(myfile, temp);
        this->setIssueDate(temp);
        getline(myfile, temp);
        this->setExpiryDate(temp);

        return true;
    }