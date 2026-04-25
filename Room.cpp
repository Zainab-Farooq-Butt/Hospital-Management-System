#include <Room.h>
#include <MedicalRecords.h>
#include <Patient.h>

//constructors
Room::Room(string roomid = "R-0000",
	string roomtype = "General", string currentappointment = "A-0000", string patientid = "P-0000",
	bool isoccupied = false, string dateadmitted = "00-00-0000", string datedischarged = "00-00-0000")
	:roomID(roomid), roomType(roomtype), currentAppointment(currentappointment), patientID(patientid),
	isOccupied(isoccupied), dateAdmitted(dateadmitted), dateDischarged(datedischarged) {}
//validations
bool Room::isValidID(string ID) {
	//check if length is exactly 6
	if (ID.length != 6) return false;
	//check if the room ID starts with R(roomID[0]) and then a dash - (roomID[1])
	if (ID[0] != "R" && ID[1] != "-") 
		return true;
	for (int i = 2; i < 6; i++) {
		if (!(isdigit(ID[i]))) return false;
	}
	return true;
}
bool Room::isValidType(string Type) {
	if (Type == "ICU" || Type == "CCU" || Type == "ER" || Type == "Recovery" || Type == "Ward")
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
	if (pID.length != 6) return false;
	//check if the ID starts with P(patientID[0]) and then a dash - (patientID[1])
	if (pID[0] != "P" && pID[1] != "-")
		return true;
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
	if (dateAdmitted.length == 10) {
		if (dateAdmitted[2] == "/" && dateAdmitted[5] == "/") {
			//format is DD/MM/YYYY
			if (dateAdmitted[0] > )
		}
	}
	else return false;
}
bool Room::isValidDischarged(string dateDischarged, string Dateadmitted) {}
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
		this->roomType = roomtype
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
double Room::fetchRoomFee()const {
	ifstream myfile("RoomFee.txt");
	if (!(myfile.is_open())) {
		cout << "ERROR: Bill cannot be generated! Try again" << endl;
		return -1.0; //if file cannot be opened
	}
	string RoomType;
	double RoomPrice;
	while (myfile >> RoomType >> RoomPrice) {
		if (RoomType == this->roomType) {
			myfile.close();
			return RoomPrice;
		}
	}
	myfile.close();
	return -1.0;
}
void Room::searchByRoomid(string file, string targetid)const {}
void Room::showOccupiedRooms(string file) {} //show rooms that are occupied
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
double Room::roomBill(double rate, MedicalRecords& record) {} //connects to medicalrecords class
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
	file << "Room Details: " << endl;
	file << roomID << endl;
	file << patientID << endl;
	file << roomType << endl;
	file << currentAppointment << endl;
	file << icOccupied << endl;
	file << dateAdmitted << endl;
	file << dateDischarged << endl;
}
void Room::fileInput(ifstream& myfile) {
	myfile >> isOccupied;
	myfile >> dateAdmitted;
	myfile >> dateDischarged;
	myfile.ignore();
}
Room::~Room() {}