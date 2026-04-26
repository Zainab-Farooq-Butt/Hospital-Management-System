#include <Medicine.h>
    // Constructor
    Medicine::Medicine(string n = "", string d = "", int q = 0, 
    int stock = 0, double p = 0.00, string iss = "", string exp = ""){}
    ~Medicine(){}

    // Setters
    Medicine& Medicine::setName(string n) {}
    Medicine& Medicine::setDosage(string d) {}
    Medicine& Medicine::setQuantity(int q){}
    Medicine& Medicine::setStock(int s){}
    Medicine& Medicine::setPrice(double p){}
    Medicine& Medicine::setExpiryDate(string e){}
    Medicine& Medicine::setIssueDate(string i){}

    // Getters
    string Medicine::getName() const{}
    string Medicine::getDosage() const{}
    int Medicine::getQuantity()const{}
    int Medicine::getStock() const{}
    double Medicine::getPrice() const{}
    string Medicine::getIssueDate() const{}
    string Medicine::getExpiryDate() const{}

    //other Functions
    void Medicine::displayInfo() const{}
    bool Medicine::isMedicineExpired(string currentDate) const{}