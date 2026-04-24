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
	//considering form A-000
	if (id == "")
		return false;
	if (id.length() != 5)
		return false;
	if (id[0] != 'A' || id[1] != '-')
		return false;
	if (!isdigit(id[2]) || !isdigit(id[3]) || !isdigit(id[4])) {
		return false;
	}
	return true;
}
bool Ambulance::isValidDriverId(string id) {
	//D-000
	if (id == "")
		return false;
	if (id.length() != 5)
		return false;
	if (id[0] != 'A' || id[1] != '-')
		return false;
	if (!isdigit(id[2]) || !isdigit(id[3]) || !isdigit(id[4])) {
		return false;
	}
	return true;
}

bool Ambulance:: isValidLicensePlate(string plate) {
	//ABC-123 or ABC-1234 > letters cannot be I,O or U
	if (plate.empty() || plate.length() < 7 || plate.length() > 8)
		return false;
	for (int i = 0; i < 3; i++) {
		if (plate[i] != isalpha())
			return false;
		if (toupper(plate[i]) == "I" || toupper(plate[i]) == "O" || toupper(plate[i]) == "U")
			return false;
	}
	if (plate[3] != "-")
		return false;
	for (int i = 4; i < plate.length(); i++{
		if(plate[i]!=isdigit())
			return false;
	}
	return true;
}
bool Ambulance:: isValidAddress(string location) {
	if(location=="")
		return false;
}

string Ambulance:: getAmbulanceId()const {
	return ambulanceId;
}
bool Ambulance::getAvailability()const {
	return availability;
}
bool Ambulance::getDriverId()const {
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
			if (isValidAmbulanceId(id)) {
				break;
			}
			cout << "Invalid ID. Must be in the format A-000. Try again. " << endl;
		}
		ambulanceId = id;
	}
	else
		ambulanceId = id;
}
void Ambulance::setAvailability(bool avail) {
	availaility = avail;
}
string Ambulance::setDriverId(string id) {
	if (!isValidDriverId(id)) {
		while (true) {
			cout << "Enter Driver ID: ";
			cin >> id;
			if (isValidDriverId(id)) {
				break;
			}
			cout << "Invalid ID. Must be in the format D-000. Try again. " << endl;
		}
		driverId = id;
	}
	else
		driverId = id;
}
string Ambulance::setLicensePlate(string plate) {
	if (!isValidLicensePlate(plate)) {
		while (true) {
			cout << "Enter License Plate: ";
			cin >> id;
			if (isValidLicensePlate(plate)) {
				break;
			}
			cout << "Invalid plate number. Must be in the format ABC-123 or ABC-1234. Try again. " << endl;
		}
		licensePlate = plate;
	}
	else
		licensePlate = plate;
}
string Ambulance::setAddress(string address) {
	if (isValidAddress(address))
		this->address = adrress;
}
void Ambulance::displayAmbulanceInfo() {
	cout << "-------------AMBULANCE DETAILS---------------" << endl;
	cout << "Ambulance ID: " << ambulanceId << endl;
	cout << "Availability: " << availability << endl;
	cout << "Driver ID: " << driverId << endl;
	cout << "License Plate: " << licensePlate << endl;
	cout << "Address: " << address << endl;
}
