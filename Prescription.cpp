#include "Prescription.h"

// Constructor
Prescription::Prescription(string pID, string medName, int qty, double cost)
    : patientID(pID), medicineName(medName), quantity(qty), totalcost(cost) {}

Prescription::~Prescription() {}

// Setters
void Prescription::setPatientID(string pID) {
    if (!pID.empty())
        patientID = pID;
}

void Prescription::setMedicineName(string medName) {
    if (!medName.empty())
        medicineName = medName;
}

void Prescription::setQuantity(int qty) {
    if (qty >= 0)
        quantity = qty;
}

void Prescription::setTotalCost(double cost) {
    if (cost >= 0.0)
        totalcost = cost;
}

// Getters
string Prescription::getPatientID() const {
    return patientID;
}

string Prescription::getMedicineName() const {
    return medicineName;
}

int Prescription::getQuantity() const {
    return quantity;
}

double Prescription::getTotalCost() const {
    return totalcost;
}

// Display
void Prescription::displayInfo() const {
    cout << "-------------------------------" << endl;
    cout << "Patient ID : " << patientID    << endl;
    cout << "Medicine   : " << medicineName << endl;
    cout << "Quantity   : " << quantity     << endl;
    cout << "Total Cost : " << totalcost    << endl;
    cout << "-------------------------------" << endl;
}

// File Output — saves one prescription to file
void Prescription::fileOutput(ofstream& outfile) const {
    outfile << "----------"    << endl;
    outfile << patientID       << endl;
    outfile << medicineName    << endl;
    outfile << quantity        << endl;
    outfile << totalcost       << endl;
}

// File Input — loads one prescription from file
bool Prescription::fileInput(ifstream& infile) {
    string separator;

    // read "----------"
    if (!getline(infile, separator)) return false;
    if (separator != "----------")   return false;

    string temp;

    // patientID
    if (!getline(infile, temp) || temp.empty()) return false;
    patientID = temp;

    // medicineName
    if (!getline(infile, temp) || temp.empty()) return false;
    medicineName = temp;

    // quantity
    if (!(infile >> quantity)) return false;

    // totalcost
    if (!(infile >> totalcost)) return false;

    infile.ignore(); // clear newline
    return true;
}