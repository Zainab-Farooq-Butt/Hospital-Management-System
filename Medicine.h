// Medicine.h
#pragma once
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Medicine {
private:
    string name;
    string dosage;
    int    quantity;
    int    stockAvailability;
    double price;

public:
    // Constructor & Destructor
    Medicine(string n = "", string d = "", int q = 0,
             int stock = 0, double p = 0.00);
    ~Medicine();

    // Validations
    bool isValidName(string n);
    bool isValidDosage(string d);
    bool isValidPrice(double p);
    bool isValidQuantity(int q);
    bool isValidAvailability(int s);

    // Setters
    Medicine& setName(string n);
    Medicine& setDosage(string d);
    Medicine& setQuantity(int q);
    Medicine& setStock(int s);
    Medicine& setPrice(double p);

    // Getters
    string getName()    const;
    string getDosage()  const;
    int    getQuantity()const;
    int    getStock()   const;
    double getPrice()   const;

    // Operator
    bool operator>=(int rQty) const;

    // Other
    void displayInfo()              const;
    bool fileInput(ifstream& myfile);
};