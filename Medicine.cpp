#include <Medicine.h>
    // Constructor
    Medicine::Medicine(string n = "", string d = "", int q = 0, 
    int stock = 0, double p = 0.00, string iss = "", string exp = ""):
    name(n),dosage(d),quantity(q),stockAvailability(s),price(p),issueDate(iss),expiryDate(exp){}
    ~Medicine(){}
    //Validations
    bool isValidDosage(string d){}
    bool isValidQuantity(int q){}
    bool isValidAvailability(int s){}
    bool isValidDateofIssue(string i){}
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
    Medicine& Medicine::setPrice(double p){}
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

    //other Functions
    void Medicine::displayInfo() const{}
    bool Medicine::isMedicineExpired(string currentDate) const{}