#include <Room.h>
#include <MedicalRecords.h>
#include <Patient.h>
#include <Billing.h>

//constructors
Room::Room(string roomid = "",
	string roomtype = "", string currentappointment = "", string patientid = "",
	bool isoccupied = false, string dateadmitted = "", string datedischarged = "")
	:roomID(roomid), roomType(roomtype), currentAppointment(currentappointment), patientID(patientid),
	isOccupied(isoccupied), dateAdmitted(dateadmitted), dateDischarged(datedischarged) {}
//validations
bool Room::isValidID(string ID) {
	//check if length is exactly 6
	if (ID.length() != 6) return false;
	//check if the room ID starts with R(roomID[0]) and then a dash - (roomID[1])
	if (ID[0] != 'R' && ID[1] != '-')
		return false;
	for (int i = 2; i < 6; i++) {
		if (!(isdigit(ID[i]))) return false;
	}
	return true;
}
bool Room::isValidType(string Type) {
	if (Type == "ICU" || Type == "CCU" || Type == "ER" || Type == "Recovery" || Type == "Ward"||Type=="Isolation")
		return true;
	return false;
}
bool Room::isValidAppointment(string Appointment) {
	//check if length is exactly 6
	if (Appointment.length() != 6) return false;
	if (Appointment[0] != 'A' || Appointment[1] != '-') return false;
	for (int i = 2; i < 6; i++) {
		if (!isdigit(Appointment[i])) return false;
	}
	return true;
}
bool Room::isValidpID(string pID) {
	//check if length is exactly 6
	if (pID.length() != 6) return false;
	//check if the ID starts with P(patientID[0]) and then a dash - (patientID[1])
	if (pID[0] != 'P' && pID[1] != '-')
		return false;
	for (int i = 2; i < 6; i++) {
		if (!(isdigit(pID[i]))) return false;
	}
	return true;
}
bool Room::isValidOccupied(bool isOccupied) {
	if (isOccupied) return true;
	else return false;
}
bool Room::isValidAdmitted(string dateAdmitted) {
	if (dateAdmitted.length() != 10) return false;
	if (dateAdmitted[2] != '-' || dateAdmitted[5] != '-') return false;
	int day = stoi(dateAdmitted.substr(0,2));
	int month = stoi(dateAdmitted.substr(3,2));
	int year = stoi(dateAdmitted.substr(6,4));
	if (month < 1 || month>12) return false;
	if (day < 1 || day>31) return false;
	if (year<2000) return false;
	
	return true;
}
bool Room::isValidDischarged(string dateDischarged, string Dateadmitted) {
		if (!isValidAdmitted(dateDischarged)) return false;
		int day1 = stoi(Dateadmitted.substr(0, 2));
		int month1 = stoi(Dateadmitted.substr(3, 2));
		int year1 = stoi(Dateadmitted.substr(6, 4));
		int day2 = stoi(dateDischarged.substr(0, 2));
		int month2 = stoi(dateDischarged.substr(3, 2));
		int year2 = stoi(dateDischarged.substr(6, 4));

	if (year2 < year1) return false;
	if (year2 == year1 && month2 < month1) return false;
	if (year2 == year1 && month2 == month1 && day2 < day1) return false;
	return true;
}
//getters
string Room::getId()const {
	return roomID;
}
string Room::getType()const {
	return roomType;
}
string Room::getAppointment()const {
	return currentAppointment;
}
string Room::getpID()const {
	return patientID;
}
string Room::getDateAdmitted()const {
	return dateAdmitted;
}
string Room::getDateDischarged()const {
	return dateDischarged;
}
//setters
Room& Room::setId(string roomid) {
	if (isValidID(roomid)) {
		this->roomID = roomid;
	}
	return *this;
}
Room& Room::setType(string roomtype) {
	if (isValidType(roomtype)) {
		this->roomType = roomtype;
	}
	else
		roomType = "General Ward";
	return *this;
}
Room& Room::setAppointment(string currentappointment) {
	if (isValidAppointment(currentappointment)) {
		this->currentAppointment = currentappointment;
	}
	return *this;
}
Room& Room::setpID(string patientid) {
	if (isValidpID(patientid)) {
		this->patientID = patientid;
	}
	return *this;
}
Room& Room::setOccupied(bool isoccupied) {
	if (!(isValidOccupied(isoccupied))) {
		patientId = ""; //if room is not occupied
	}this->isOccupied = isoccupied;
	return *this;
}
Room& Room::setAdmitted(string dateadmitted) {
	if (isValidAdmitted(dateadmitted)) {
		this->dateAdmitted = dateadmitted;
	}
	return *this;
}
Room& Room::setDischarged(string datedischarged) {
	if (isValidAdmitted(dateadischarged)) {
		this->dateDischarged = datedischarged;
	}
	return *this;
}
//other functions
double Room::fetchRoomFee(string patientID)const {
	ifstream myfile("Room.txt");
	if (!(myfile.is_open())) {
		cout << "ERROR: Bill cannot be generated! Try again" << endl;
		return -1.0; //if file cannot be opened
	}
	Room buffer;
	bool found = false;
	while (buffer.fileInput(myfile)) {
		if (buffer.patientID==patientid) {
			myfile.close();
			found = true;
			break;
		}
	}
	myfile.close();
	if (!found) {
		cout << "No room found for patient " << patientId << endl;
		return 0.0;
	}
	ifstream FeeFile("RoomFee.txt");
	if (!FeeFile.is_open()) {
		cout << "ERROR: Cannot open File!" << endl;
		return -1.0;
	}
	string type;
	double rate = -1.0;
	while (FeeFile >> type >> rate) {
		if (buffer.roomType == type) {
			break;
		}
	}
	if (rate == -1.0) {
		cout << "No Room type!" << endl;
		return 0.0;
	}
	int days = buffer.numberOfdaysinRoom();
	if (days == 0 && buffer.isOccupied) days = 1;
	return days * rate;
	return -1.0;
}
void Room::searchByRoomid(string file, string targetid)const {
	ifstream myfile(file);
	Room buffer;
	bool found = false;
	while (buffer.fileInput(myfile)) {
		if (buffer.getId() == targetid) {
			buffer.displayRoomDetails();
			found = true;
			break;
		}
	}
	if (!found) cout << "Room Id: " << targetid << " not found." << endl;
	myfile.close();
}
void Room::showOccupiedRooms(string file) {
	ifstream myfile(file);
	Room buffer; //checking for number of rooms occupied
	cout << "=====Rooms currently Occupied=====" << endl;
	while (buffer.fileInput(myfile)) {
		if (buffer.isOccupied) {
			buffer.displayRoomDetails();
		}
	}
	myfile.close();
} //show rooms that are occupied
void Room::transferPatient(string file, string newroomid) {} //transferring a patient to another room
int Room::numberOfdaysinRoom() {
	if (dateAdmitted == "" || dateDischarged == "") return 0;
	int day1 = stoi(dateAdmitted.substr(0, 2)); //0 is the position and 2 is the number of characters starting from 0
	int month1 = stoi(dateAdmitted.substr(3,2));
	int year1 = stoi(dateAdmitted.substr(6,4));
	int day2 = stoi(dateDischarged.substr(0, 2));
	int month2 = stoi(dateDischarged.substr(3,2));
	int year2 = stoi(dateDischarged.substr(6,4));
	int Month[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	long days1 = year1 * 365 + day1;
	for (int i = 1; i < month1; i++) days1 += Month[i];
	long days2 = year2 * 365 + day2;
	for (int i = 1; i < month2; i++) days2 += Month[i];
	int difference = days2 - days1;
	if (difference <= 0) return 0;
	return difference;} //discharged-admitted
double Room::roomBill(double rate, MedicalRecords& record) {
	double roomRate = fetchRoomFee();
	if (roomRate == -1.0) {
		cout << "Room type for the given fee not Found!" << endl;
		return 0.0
	}
	int daysSpent = numberOfDaysinRoom();
	if (daysSpent == 0 && isOccupied) daysSpent = 1;
	double TotalCost = daysSpent * roomRate;

	//at least one day
} //connects to medicalrecords class
//display
void Room::displayRoomDetails()const {
	cout << "=======DISPLAYING ALL ROOM DETAILS=======" << endl;
	cout << "Room ID: " << roomID << endl;
	cout << "Room Type: " << roomType << endl;
	cout << "Patient Id: " << patientID << endl;
	cout << "Current Appointment: " << currentAppointment << endl;
	cout << "Room Occupied?: " << isOccupied << endl;
	cout << "Date Admitted: " << dateAdmitted << endl;
	cout << "Date Discharged: " << dateDischarged << endl;
	cout << "=======DISPLAYING ALL ROOM DETAILS=======" << endl;
}
//file handling
void Room::fileOutput(ofstream& file)const {
	file << roomID << endl;
	file << patientID << endl;
	file << roomType << endl;
	file << currentAppointment << endl;
	file << icOccupied << endl;
	file << dateAdmitted << endl;
	file << dateDischarged << endl;
}
void Room::fileInput(ifstream& myfile) {
	getline(myfile, roomID);
	getline(myfile, patientID);
	getline(myfile, roomType);
	getline(myfile, currentAppointment);
	myfile >> isOccupied;
	myfile.ignore();
	//clearing newline

	getline(myfile, dateAdmitted); 
	getline(myfile, dateDischarged);
}
Room::~Room() {}