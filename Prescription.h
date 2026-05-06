#pragma once
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Prescription {
private:
    string patientID;
    string medicineName;
    int    quantity;
    double totalcost;

public:
    // Constructor
    Prescription(string pID = "", string medName = "",int qty = 0, double cost = 0.0);
    ~Prescription();

    // Setters
    void setPatientID(string pID);
    void setMedicineName(string medName);
    void setQuantity(int qty);
    void setTotalCost(double cost);

    // Getters
    string getPatientID()    const;
    string getMedicineName() const;
    int    getQuantity()     const;
    double getTotalCost()    const;

    // Display
    void displayInfo() const;

    // File Handling
    void fileOutput(ofstream& outfile) const;
    bool fileInput(ifstream& infile);
};