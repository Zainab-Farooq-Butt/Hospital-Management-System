#include <Medicine.h>
    // Constructor
    Medicine::Medicine(string n = "", string d = "", int q = 0, 
    int stock = 0, double p = 0.00, string iss = "", string exp = ""):
    name(n),dosage(d),quantity(q),stockAvailability(s),price(p),issueDate(iss),expiryDate(exp){}
    ~Medicine(){}
    //Validations
    bool isValidName(string n) {
        if (n.empty()) return false;

        return true;
    }
    bool isValidDosage(string d) {
        if (d.length()==0) return false;
        int i = 0;
        bool isDigit = false;
        string unitOfMedicine = "";
        while (i < d.length()) {
            if (isdigit(d[i])) {
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
        if (i.length() != 10) return false;
        if (i[2] != '-' || i[5] != '-') return false;
        int day = stoi(i.substr(0, 2));
        int month = stoi(i.substr(3, 2));
        int year = stoi(i.substr(6, 4));
        if (month < 1 || month>12) return false;
        if (day < 1 || day>31) return false;
        if (year < 2000) return false;
        return true;
    }
    bool isValidDateofExpiry(string e, string i){
        if (!isValidDateofIssue(e)) return false;
        int day1 = stoi(i.substr(0, 2));
        int month1 = stoi(i.substr(3, 2));
        int year1 = stoi(i.substr(6, 4));
        int day2 = stoi(e.substr(0, 2));
        int month2 = stoi(e.substr(3, 2));
        int year2 = stoi(e.substr(6, 4));
        if (year2 < year1) return false;
        if (year2 == year1 && month2 < month1) return false;
        if (year2 == year1 && month2 == month1 && day2 < day1) return false;
        return true;
    }
    // Setters
    Medicine& Medicine::setName(string n) {
        if (isValidName(n)) {
            name = n;
        }return *this;
    }
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
    void Medicine::displayInfo() const{
        cout << "=======DISPLAYING MEDICINE DETAILS=======" << endl;
        cout << "Name: " << name << endl;
        cout << "Dosage: " << dosage << endl;
        cout << "Quantity: " << quantity << endl;
        cout << "Price: " << price << endl;
        cout << "Date of Issue: " << issueDate << endl;
        cout << "Date of Expiry: " << expiryDate << endl;
        cout << "=======DISPLAYING MEDICINE DETAILS=======" << endl;
    }
    bool Medicine::isMedicineExpired(string currentDate) const{
        int day1 = stoi(expiryDate.substr(0, 2));
        int month1 = stoi(expiryDate.substr(3, 2));
        int year1 = stoi(expiryDate.substr(6, 4));
        int day2 = stoi(currentDate.substr(0, 2));
        int month2 = stoi(currentDate.substr(3, 2));
        int year2 = stoi(currentDate.substr(6, 4));
        //convert inro YYMMDD for easier comparison
        long long date1 = (year1 * 10000) + (month1 * 100) + day1;
        long long date2 = (year2 * 10000) + (month2 * 100) + day2;

        if (date1 > date2) return true;

        return false;
    }
    //file handling
    bool Medicine::fileInput(ifstream& myfile) {
        if (!getline(myfile, name) || name.empty()) return false;
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