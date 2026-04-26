#include <iostream>
#include <string>
#include<iomanip>
using namespace std;
class Medicine {
private:
    string name;
    string dosage;
    int quantity;
    int stockAvailability;
    double price;
    string issueDate;
    string expiryDate;

public:
    // Constructor
    Medicine(string n="", string d="", int q=0,int stock=0, double p=0.00, string iss = "", string exp="");
    ~Medicine();

    // Setters
    Medicine& setName(string n);
    Medicine& setDosage(string d);
    Medicine& setQuantity(int q);
    Medicine& setStock(int s); 
    Medicine& setPrice(double p); 
    Medicine& setExpiryDate(string e);
    Medicine& setIssueDate(string i);

    // Getters
    string getName() const;
    string getDosage() const;
    int getQuantity() const;
    int getStock() const;
    double getPrice() const;
    string getIssueDate() const;
    string getExpiryDate() const;

    //other Functions
    void displayInfo() const;
    bool isMedicineExpired(string currentDate) const;
};