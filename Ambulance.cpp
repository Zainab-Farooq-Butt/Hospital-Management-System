#include"Ambulance.h"

Ambulance::Ambulance() {
    ambulanceId = "";
    availability = false;
    driverId = "";
    licensePlate = "";
    destination = "";
}

Ambulance::Ambulance(string aId, bool avail, string dId, string plate, string location) {
    ambulanceId = aId;
    availability = avail;
    driverId = dId;
    licensePlate = plate;
    destination = location;
}

string Ambulance::generateAmbulanceId() {
    ambulanceCounter++;
    string num = to_string(ambulanceCounter);
    while (num.length() < 4){
        num = "0" + num;
    }
    return "A-" + num;
}

string Ambulance::generateDriverId() {
    string num = to_string(ambulanceCounter); // same counter 
    while (num.length() < 4){
        num = "0" + num;
    }
    return "D-" + num;
}

bool Ambulance::licensePlateAlreadyExists(string plate, string filename) {
    ifstream infile(filename);
    if (!infile.is_open()) return false;
    string line;
    while (getline(infile, line)) {
        if (line != "----------") continue;
        Ambulance temp;
        temp.loadFromFile(infile);
        if (temp.getLicensePlate() == plate) {
            infile.close();
            return true;
        }
    }
    infile.close();
    return false;
}

bool Ambulance::isValidAmbulanceId(string id) {
    if (id == "") return false;
    if (id.length() != 6) return false;
    if (id[0] != 'A' || id[1] != '-') return false;
    if (!isdigit(id[2]) || !isdigit(id[3]) || !isdigit(id[4]) || !isdigit(id[5])) return false;
    return true;
}

bool Ambulance::isValidDriverId(string id) {
    if (id == "") return false;
    if (id.length() != 6) return false;
    if (id[0] != 'D' || id[1] != '-') return false;
    if (!isdigit(id[2]) || !isdigit(id[3]) || !isdigit(id[4]) || !isdigit(id[5])) return false;
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

bool Ambulance::isValidDestination(string location) {
    if (location == "")
        return false;
    return true;
}

string Ambulance::getAmbulanceId()const {
    return ambulanceId;
}

bool Ambulance::getAvailability()const {
    // If destination is set (not empty and not "None"), ambulance is unavailable
    if (!destination.empty() && destination != "None" && destination != "none") {
        return false;
    }
    return availability;
}

string Ambulance::getDriverId()const {
    return driverId;
}

string Ambulance::getLicensePlate()const {
    return licensePlate;
}

string Ambulance::getDestination()const {
    return destination;
}

void Ambulance::setAmbulanceId(string id) {
    if (!isValidAmbulanceId(id)) {
        while (true) {
            cout << "Enter Ambulance ID: ";
            cin >> id;
            if (isValidAmbulanceId(id)) break;
            cout << "Invalid ID. Must be in the format A-0000. Try again." << endl;
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
            cout << "Invalid ID. Must be in the format D-0000. Try again." << endl;
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

void Ambulance::setDestination(string addr) {
    if (isValidDestination(addr))
        this->destination = addr;
    else {
        while (true) {
            cout << "Enter Destination: ";
            cin >> addr;
            if (isValidDestination(addr)) {
                this->destination = addr;
                break;
            }
            cout << "Invalid Destination. Try again." << endl;
        }
    }
}

void Ambulance::displayAmbulanceInfo() {
    cout << "Ambulance ID:  " << ambulanceId << endl;
    cout << "Availability:  " << (getAvailability() ? "Available" : "Not Available")<< endl;
    cout << "Driver ID:     " << driverId     << endl;
    cout << "License Plate: " << licensePlate << endl;
    cout << "Destination:   " << destination   << endl;
}


void Ambulance::displayAllAmbulances(string filename) {
    ifstream infile(filename);
    if (!infile.is_open()) {
        cout << "No ambulance records found." << endl;
        return;
    }
    string line;
    int count = 0;
	cout << "-------------AMBULANCE DETAILS---------------" << endl;
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

void Ambulance::loadCounterFromFile(string filename) {
    ifstream infile(filename);
    int maxnum = 0;
    string sep, aid;
    if (infile.is_open()) {
        while (getline(infile, sep)) {
            if (sep != "----------") 
                continue;
            getline(infile, aid);    // ambulanceId
            string skip;
            for (int i = 0; i < 4; i++)  // skip availability, driverId, licensePlate, address
                getline(infile, skip);
            if (aid.length() < 3) continue;
            int num = stoi(aid.substr(2));  // strips "A-"
            if (num > maxnum)
                maxnum = num;
        }
        infile.close();
    }
    ambulanceCounter = maxnum;
}

void Ambulance::loadFromFile(ifstream& infile) {
    string avail;
    getline(infile, ambulanceId);
    getline(infile, avail);
    availability = (avail == "1");
    getline(infile, driverId);
    getline(infile, licensePlate);
    getline(infile, destination);
}

void Ambulance::saveToFile(string filename) {
    ofstream outfile(filename, ios::app);
    if (outfile.is_open()) {
        outfile << "----------" << endl;
        outfile << ambulanceId << endl;
        outfile << getAvailability() << endl; // Use the logic-enforced availability
        outfile << driverId << endl;
        outfile << licensePlate << endl;
        outfile << destination << endl;
        outfile.close();
    }
    else {
        cout << "Error opening file." << endl;
    }
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

Ambulance::~Ambulance(){};
int Ambulance::ambulanceCounter = 0;