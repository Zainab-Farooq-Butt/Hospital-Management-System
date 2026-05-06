#include "Medicine.h"

// Constructor
Medicine::Medicine(string n, string d, int q, int stock, double p)
    : name(n), dosage(d), quantity(q), stockAvailability(stock), price(p) {}

Medicine::~Medicine() {}

// Validations
bool Medicine::isValidName(string n) {
    if (n.empty()) return false;
    return true;
}

bool Medicine::isValidDosage(string d) {
    if (d.length() == 0) return false;

    int i = 0;
    bool isDigit = false;
    string unitOfMedicine = "";

    // read digits
    while (i < d.length()) {
        if (isdigit(d[i])) {
            isDigit = true;
            i++;
        }
        else if (d[i] == ' ') {
            i++;
        }
        else break;
    }

    if (!isDigit) return false;

    // FIX: was using d[i] inside j loop, should be d[j]
    int j = i;
    while (j < d.length()) {
        if (d[j] != ' ') {
            unitOfMedicine += tolower(d[j]);
        }
        j++;
    }

    if (unitOfMedicine == "mg" || unitOfMedicine == "ml") return true;
    return false;
}

bool Medicine::isValidPrice(double p) {
    return p >= 0.0;
}

bool Medicine::isValidQuantity(int q) {
    return q >= 0;
}

bool Medicine::isValidAvailability(int s) {
    return s >= 0;
}

// Setters
Medicine& Medicine::setName(string n) {
    if (isValidName(n))
        name = n;
    return *this;
}

Medicine& Medicine::setDosage(string d) {
    if (isValidDosage(d))
        dosage = d;
    return *this;
}

Medicine& Medicine::setQuantity(int q) {
    if (isValidQuantity(q))
        quantity = q;
    return *this;
}

Medicine& Medicine::setStock(int s) {
    if (isValidAvailability(s))   // FIX: was isValidStock, now isValidAvailability
        stockAvailability = s;
    return *this;
}

Medicine& Medicine::setPrice(double p) {
    if (isValidPrice(p))
        price = p;
    return *this;
}

// Getters
string Medicine::getName() const {
    return name;
}

string Medicine::getDosage() const {
    return dosage;
}

int Medicine::getQuantity() const {
    return quantity;
}

int Medicine::getStock() const {
    return stockAvailability;
}

double Medicine::getPrice() const {
    return price;
}

// Comparison
bool Medicine::operator>=(int rQty) const {
    return this->stockAvailability >= rQty;
}

// Display
void Medicine::displayInfo() const {
    cout << "=========================================" << endl;
    cout << "Name     : " << name             << endl;
    cout << "Dosage   : " << dosage           << endl;
    cout << "Quantity : " << quantity         << endl;
    cout << "Stock    : " << stockAvailability<< endl;
    cout << "Price    : " << price            << endl;
    cout << "=========================================" << endl;
}

// File Handling
bool Medicine::fileInput(ifstream& myfile) {
    string separator;

    // read the "----------" separator line
    if (!getline(myfile, separator)) return false;
    if (separator != "----------")   return false;

    string temp;

    // name
    if (!getline(myfile, temp) || temp.empty()) return false;
    name = temp;

    // dosage
    if (!getline(myfile, temp) || temp.empty()) return false;
    this->setDosage(temp);

    // stock
    if (!(myfile >> stockAvailability)) return false;

    // price
    if (!(myfile >> price)) return false;

    myfile.ignore(); // clear newline after price
    return true;
}