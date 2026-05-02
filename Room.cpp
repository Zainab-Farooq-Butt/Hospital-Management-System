#include "Room.h"
#include "MedicalRecords.h"
#include "Patient.h"
#include "Billing.h"
#include "Appointment.h"

string Room::To_Lower_Case(string str){
    for (int i = 0; i < str.length(); i++)
    str[i] = tolower(str[i]);   
    return str;
}

//constructors
Room::Room(string roomid,
	string roomtype, string currentappointment , string patientid ,
	bool isoccupied , string dateadmitted , string datedischarged )
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
	Type=To_Lower_Case(Type);
	if (Type == "icu" || Type == "ccu" || Type == "er" || Type == "recovery" || Type == "ward"|| Type=="isolation" || Type=="private")
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
		patientID = ""; //if room is not occupied
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
	if (isValidAdmitted(datedischarged)) {
		this->dateDischarged = datedischarged;
	}
	return *this;
}
//other functions
double Room::fetchRoomFee(string patientid) {
    // Step 1: find the room for this patient
    ifstream roomFile("Room.txt");
    if (!roomFile.is_open()) {
        cout << "ERROR: Cannot open Room.txt!" << endl;
        return 0.0;
    }

    string line, roomID, patientID, roomType;
    int isOccupied;
    string dateAdmitted, dateDischarged;
    bool found = false;

    while (getline(roomFile, line)) {
        if (line == "----------") {
            getline(roomFile, roomID);
            getline(roomFile, patientID);
            getline(roomFile, roomType);
            roomFile >> isOccupied;
            roomFile.ignore();
            getline(roomFile, dateAdmitted);
            getline(roomFile, dateDischarged);

            if (patientID == patientid) {
                found = true;
                break;
            }
        }
    }
    roomFile.close();

    if (!found) {
        cout << "No room found for patient " << patientid << endl;
        return 0.0;
    }

    // Step 2: look up fee by room type
    // RoomFee.txt has type on one line, fee on next line
    ifstream feeFile("RoomFee.txt");
    if (!feeFile.is_open()) {
        cout << "ERROR: Cannot open RoomFee.txt!" << endl;
        return 0.0;
    }

    string feeType;
    double rate = -1.0;

    while (getline(feeFile, feeType)) {
        // trim trailing whitespace/\r from feeType
        while (!feeType.empty() && (feeType.back() == ' ' || feeType.back() == '\r'))
            feeType.pop_back();

        string rateStr;
        getline(feeFile, rateStr);

        // compare case-insensitively
        if (To_Lower_Case(feeType) == To_Lower_Case(roomType)) {
            rate = stod(rateStr);
            break;
        }
    }
    feeFile.close();

    if (rate == -1.0) {
        cout << "No fee found for room type: " << roomType << endl;
        return 0.0;
    }

    // Step 3: calculate days
    // if not discharged yet, use 1 day minimum
    int days = 0;
    if (dateDischarged != "-" && dateAdmitted != "-") {
        // reuse numberOfDaysinRoom logic directly
        int day1 = stoi(dateAdmitted.substr(0, 2));
        int month1 = stoi(dateAdmitted.substr(3, 2));
        int year1 = stoi(dateAdmitted.substr(6, 4));
        int day2 = stoi(dateDischarged.substr(0, 2));
        int month2 = stoi(dateDischarged.substr(3, 2));
        int year2 = stoi(dateDischarged.substr(6, 4));

        int Month[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
        long days1 = year1 * 365 + day1;
        for (int i = 1; i < month1; i++) days1 += Month[i];
        long days2 = year2 * 365 + day2;
        for (int i = 1; i < month2; i++) days2 += Month[i];
        days = days2 - days1;
    }

    if (days <= 0) days = 1; // minimum 1 day charge

    // Step 4: return total
    cout << "Room Type: " << roomType << endl;
    cout << "Days Stayed: " << days << endl;
    cout << "Rate per Day: " << rate << endl;
    cout << "Total Room Fee: " << days * rate << endl;

    return days * rate;
}

double Room::roomBill(MedicalRecords& record) {
    double total = fetchRoomFee(patientID);
    if (total == 0.0) {
        cout << "Could not calculate room bill." << endl;
    }
    return total;
}
void Room::searchByRoomid(string file, string targetid)const {
	ifstream myfile("Room.txt");
	Room buffer;
	bool found = false;
	while (!myfile.eof()) {
		buffer.fileInput(myfile);
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
	ifstream myfile("Room.txt");
	Room buffer; //checking for number of rooms occupied
	cout << "=====Rooms currently Occupied=====" << endl;
	while (!myfile.eof()) {
		buffer.fileInput(myfile);
		if (buffer.isOccupied) {
			buffer.displayRoomDetails();
		}
	}
	myfile.close();
} //show rooms that are occupied












 //transferring a patient to another room
void Room::transferPatient(string file,string newroomid) {
	if (!isValidID(newroomid)) {
		cout << "Fail: " << newroomid << " is not a valid Room ID." << endl;
		return;
	}
	if (!this->isOccupied) {
		cout << "Fail: Current room " << this->roomID << " is already Occupied." << endl;
		return;
	}
	ifstream myfile("Room.txt");
	Room buffer;
	ofstream temp("temp.txt");
	bool found = false;
	while (!myfile.eof()) {
		buffer.fileInput(myfile);
		if (buffer.getId() == newroomid) {
			//method chaining
			buffer.setpID("P-0000")
				.setAppointment("A-0000")
				.setOccupied(false)
				.setAdmitted("00-00-0000")
				.setDischarged("00-00-0000");
			found = true;
		}
		//current room
		else if (buffer.getId() == this->roomID) {
			buffer.setpID("P-0000")
				.setAppointment("A-0000")
				.setOccupied(false)
				.setAdmitted("00-00-0000")
				.setDischarged("00-00-0000");
		}
		buffer.fileOutput(temp);
	}
	myfile.close();
	temp.close();
	if (found==true) {
		remove("room.txt");
		rename("temp.txt", "room.txt");
		this->setpID("P-0000").setOccupied(false);
		cout << "Patient moved to Room " << newroomid << endl;
	}
	else {
		remove("temp.txt"); //cleaning up if target is not found
		cout << "Transfer Failed: Target room " << newroomid << " does not exist." << endl;
	}
}
int Room::numberOfDaysinRoom() const {
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

double Room::roomBill(MedicalRecords& record) {
	double roomRate = fetchRoomFee(patientID);
	if (roomRate == -1.0) {
		cout << "Room type for the given fee not Found!" << endl;
		return 0.0;
	}
	int daysSpent = numberOfDaysinRoom();
	if (daysSpent == 0 && isOccupied) daysSpent = 1;
	double TotalCost = daysSpent * roomRate;
	return TotalCost;

	//at least one day
} //connects to medicalrecords class
//display
void Room::displayRoomDetails()const {
	cout << "=======DISPLAYING ALL ROOM DETAILS=======" << endl;
	cout << "Room ID: " << roomID << endl;
	cout << "Room Type: " << roomType << endl;
	cout << "Patient Id: " << patientID << endl;
	cout << "Room Occupied?: " << isOccupied << endl;
	cout << "Date Admitted: " << dateAdmitted << endl;
	cout << "Date Discharged: " << dateDischarged << endl;
}
//file handling
void Room::fileOutput(ofstream& file)const {
	file << "----------" << endl;
	file << roomID << endl;
	file << patientID << endl;
	file << roomType << endl;
	file << isOccupied << endl;
	file << dateAdmitted << endl;
	file << dateDischarged << endl;
}
void Room::fileInput(ifstream& myfile) {
	string extra;
	
	getline(myfile,extra);
	getline(myfile, roomID);
	getline(myfile, patientID);
	getline(myfile, roomType);
	myfile >> isOccupied;
	myfile.ignore();
	//clearing newline

	getline(myfile, dateAdmitted); 
	getline(myfile, dateDischarged);
}
Room::~Room() {}

bool Room::displayAvailableRoomsByType(string type) {
    ifstream file("Room.txt",ios::in);
    if (!file) {
        cout << "Error opening file!" << endl;
        return false;
    }

    string line, roomID, patientID, roomType;
    int isOccupied;
    string dateAdmitted, dateDischarged;
	bool available=false;

    while (getline(file, line)) {
        if (line == "----------") {

            getline(file, roomID);
            getline(file, patientID);
            getline(file, roomType);

            file >> isOccupied;
            file.ignore(); // skip newline

            getline(file, dateAdmitted);
            getline(file, dateDischarged);

            // Check conditions
            if (roomType == type && isOccupied == 0) {
                cout << "Available Room: " << roomID << endl;
				available=true;
            }
        }
    }
    file.close();
	if(available){
		return true;
	}
	else{
		return false;
	}
}

bool Room::Check_occupied_by_roomID(string roomid, string roomtype){
	ifstream file("Room.txt",ios::in);
    if (!file) {
        cout << "Error opening file!" << endl;
        return false;
    }

    string line, roomID, patientID, roomType;
    int isOccupied;
    string dateAdmitted, dateDischarged;

    while (getline(file, line)) {
        if (line == "----------") {

            getline(file, roomID);
            getline(file, patientID);
            getline(file, roomType);

            file >> isOccupied;
            file.ignore(); // skip newline

            getline(file, dateAdmitted);
            getline(file, dateDischarged);

            // Check conditions
            if (roomID == roomid && isOccupied == 0 && roomType==roomtype) {
			   file.close();
               return true;
            }
        }
    }
    file.close();
	return false;
}
void Room::updatePatientID(string targetRoomID, string newPatientID) {

	string filename="Room.txt";
    ifstream inFile(filename);
    ofstream outFile("temp.txt");

    string line, roomID, patientID, roomType;
    int isOccupied;
    string dateAdmitted, dateDischarged;

    while (getline(inFile, line)) {
        if (line == "----------") {
            outFile << line << endl;

            getline(inFile, roomID);
            getline(inFile, patientID);
            getline(inFile, roomType);

            inFile >> isOccupied;
            inFile.ignore();

            getline(inFile, dateAdmitted);
            getline(inFile, dateDischarged);

            if (roomID == targetRoomID) {
                patientID = newPatientID;
            }

            outFile << roomID << endl;
            outFile << patientID << endl;
            outFile << roomType << endl;
            outFile << isOccupied << endl;
            outFile << dateAdmitted << endl;
            outFile << dateDischarged << endl;
        }
    }

    inFile.close();
    outFile.close();

    remove("Room.txt");
    rename("temp.txt", "Room.txt");
}
void Room::updateOccupancy(string targetRoomID, bool newStatus) {
	string filename="Room.txt";
    ifstream inFile(filename);
    ofstream outFile("temp.txt");

    string line, roomID, patientID, roomType;
    int isOccupied;
    string dateAdmitted, dateDischarged;

    while (getline(inFile, line)) {
        if (line == "----------") {
            outFile << line << endl;

            getline(inFile, roomID);
            getline(inFile, patientID);
            getline(inFile, roomType);

            inFile >> isOccupied;
            inFile.ignore();

            getline(inFile, dateAdmitted);
            getline(inFile, dateDischarged);

            if (roomID == targetRoomID) {
                isOccupied = newStatus;
            }

            outFile << roomID << endl;
            outFile << patientID << endl;
            outFile << roomType << endl;
            outFile << isOccupied << endl;
            outFile << dateAdmitted << endl;
            outFile << dateDischarged << endl;
        }
    }

    inFile.close();
    outFile.close();

    remove("Room.txt");
    rename("temp.txt", "Room.txt");
}
void Room::updateDateAdmitted(string targetRoomID, string newDate) {
    ifstream inFile("Room.txt");
    ofstream outFile("temp.txt");

    string line, roomID, patientID, roomType;
    int isOccupied;
    string dateAdmitted, dateDischarged;

    while (getline(inFile, line)) {
        if (line == "----------") {
            outFile << line << endl;

            getline(inFile, roomID);
            getline(inFile, patientID);
            getline(inFile, roomType);

            inFile >> isOccupied;
            inFile.ignore();

            getline(inFile, dateAdmitted);
            getline(inFile, dateDischarged);

            if (roomID == targetRoomID) {
                dateAdmitted = newDate;
            }

            outFile << roomID << endl;
            outFile << patientID << endl;
            outFile << roomType << endl;
            outFile << isOccupied << endl;
            outFile << dateAdmitted << endl;
            outFile << dateDischarged << endl;
        }
    }

    inFile.close();
    outFile.close();

    remove("Room.txt");
    rename("temp.txt", "Room.txt");
}