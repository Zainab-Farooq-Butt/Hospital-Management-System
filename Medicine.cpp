#include <Medicine.h>

Medicine::Medicine(string n="", string d="",int q=0, double p=0.00, string exp="", string issued="", int stock=0)
    : name(n), dosage(d),quantity(q) price(p >= 0 ? p : 0), expiryDate(exp),
    issueDate(issued), stockAvailability(stock >= 0 ? stock : 0) {}
Medicine::~Medicine();
//setters
Medicine& Medicine::setName(string n) {
    this->name = n;
    return *this;
}
Medicine& Medicine::setDosage(string d) {
    this->dosage = d;
    return *this;
}
Medicine& Medicine::setQuantity(int q) {
    this->quantity = q;
    return *this;
}
Medicine& Medicine::setPrice(double p) {
    this->price =p;
    return *this;
}
Medicine& Medicine::setExpiryDate(string e) {
    this->expiryDate = exp;
    return *this;
}
Medicine& Medicine::setIssueDate(string i) {
    this->dateIssued = issued;
    return *this;
}
Medicine& Medicine::setStock(int s) {
    this->stockAvailability = s;
    return *this;
}
//getters
string Medicine::getName() const { return name; }
string Medicine:: getDosage()const{return }
double Medicine::getPrice() const { return price; }
int Medicine::getQuantity()const { return quantiry; }
int Medicine::getStock() const { return stockAvailability; }
//display
void Medicine::displayMedicine() const {
    cout << "Medwicine: " << name << " (" << dosage << ") | Price: " << price
        << " | Stock: " << stockAvailability << endl;
}