#include"Ambulance.h"

Ambulance::Ambulance() {
    ambulanceId = "";
    availability = false;
    driverId = "";
    licensePlate = "";
    address = "";
}

Ambulance::Ambulance(string aId, bool avail, string dId, string plate, string location) {
    ambulanceId = aId;
    availability = avail;
    driverId = dId;
    licensePlate = plate;
    address = location;
}

bool Ambulance::isValidAmbulanceId(string id) {
    if (id == "") return false;
    if (id.length() != 5) return false;
    if (id[0] != 'A' || id[1] != '-') return false;
    if (!isdigit(id[2]) || !isdigit(id[3]) || !isdigit(id[4])) return false;
    return true;
}

bool Ambulance::isValidDriverId(string id) {
    if (id == "") return false;
    if (id.length() != 5) return false;
    if (id[0] != 'D' || id[1] != '-') return false;
    if (!isdigit(id[2]) || !isdigit(id[3]) || !isdigit(id[4])) return false;
    return true;
}

bool Ambulance::isValidLicensePlate(string plate) {
    if (plate.empty() || plate.length() < 7 || plate.length() > 8)
        return false;
    for (int i = 0; i < 3; i++) {
        if (!isalpha(plate[i]))
            return false;
        char upper = toupper(plate[i]);
        if (upper == 'I' || upper == 'O' || upper == 'U')
            return false;
    }
    if (plate[3] != '-')
        return false;
    for (int i = 4; i < (int)plate.length(); i++) {
        if (!isdigit(plate[i]))
            return false;
    }
    return true;
}

bool Ambulance::isValidAddress(string location) {
    if (location == "")
        return false;
    return true;
}

string Ambulance::getAmbulanceId()const {
    return ambulanceId;
}

bool Ambulance::getAvailability()const {
    return availability;
}

string Ambulance::getDriverId()const {
    return driverId;
}

string Ambulance::getLicensePlate()const {
    return licensePlate;
}

string Ambulance::getAddress()const {
    return address;
}

void Ambulance::setAmbulanceId(string id) {
    if (!isValidAmbulanceId(id)) {
        while (true) {
            cout << "Enter Ambulance ID: ";
            cin >> id;
            if (isValidAmbulanceId(id)) break;
            cout << "Invalid ID. Must be in the format A-000. Try again." << endl;
        }
    }
    ambulanceId = id;
}

void Ambulance::setAvailability(bool avail) {
    availability = avail;
}

void Ambulance::setDriverId(string id) {
    if (!isValidDriverId(id)) {
        while (true) {
            cout << "Enter Driver ID: ";
            cin >> id;
            if (isValidDriverId(id)) break;
            cout << "Invalid ID. Must be in the format D-000. Try again." << endl;
        }
    }
    driverId = id;
}

void Ambulance::setLicensePlate(string plate) {
    if (!isValidLicensePlate(plate)) {
        while (true) {
            cout << "Enter License Plate: ";
            cin >> plate;
            if (isValidLicensePlate(plate)) break;
            cout << "Invalid plate. Must be in the format ABC-123 or ABC-1234. Try again." << endl;
        }
    }
    licensePlate = plate;
}

void Ambulance::setAddress(string addr) {
    if (isValidAddress(addr))
        this->address = addr;
    else {
        while (true) {
            cout << "Enter Address: ";
            cin >> addr;
            if (isValidAddress(addr)) {
                this->address = addr;
                break;
            }
            cout << "Invalid Address. Try again." << endl;
        }
    }
}

void Ambulance::displayAmbulanceInfo() {
    cout << "-------------AMBULANCE DETAILS---------------" << endl;
    cout << "Ambulance ID: " << ambulanceId << endl;
    cout << "Availability: " << availability << endl;
    cout << "Driver ID:    " << driverId     << endl;
    cout << "License Plate:" << licensePlate << endl;
    cout << "Address:      " << address      << endl;
}
void Ambulance::saveToFile(string filename) {
    ofstream outfile(filename, ios::app);
    if (outfile.is_open()) {
        outfile << "----------" << endl;
        outfile << ambulanceId << endl;
        outfile << availability << endl;
        outfile << driverId << endl;
        outfile << licensePlate << endl;
        outfile << address << endl;
        outfile.close();
    }
    else {
        cout << "Error opening file." << endl;
    }
}

void Ambulance::loadFromFile(ifstream& infile) {
    string avail;
    getline(infile, ambulanceId);
    getline(infile, avail);
    availability = (avail == "1");
    getline(infile, driverId);
    getline(infile, licensePlate);
    getline(infile, address);
}

bool Ambulance::ambulanceIdAlreadyExists(string id, string filename) {
    ifstream infile(filename);
    if (!infile.is_open()) return false;
    string line;
    while (getline(infile, line)) {
        if (line != "----------") continue;
        Ambulance temp;
        temp.loadFromFile(infile);
        if (temp.getAmbulanceId() == id) {
            infile.close();
            return true;
        }
    }
    infile.close();
    return false;
}

void Ambulance::displayAllAmbulances(string filename) {
    ifstream infile(filename);
    if (!infile.is_open()) {
        cout << "No ambulance records found." << endl;
        return;
    }
    string line;
    int count = 0;
    while (getline(infile, line)) {
        if (line != "----------") continue;
        Ambulance temp;
        temp.loadFromFile(infile);
        cout << "\n--- Ambulance " << ++count << " ---\n";
        temp.displayAmbulanceInfo();
    }
    infile.close();
    if (count == 0)
        cout << "No ambulances on record." << endl;
}