#include<Person.h>
#include<Patient.h>
#include<MedicalRecords.h>

MedicalRecords::MedicalRecords() {
	recordId = "";
	patientId = "";
	doctorId = "";
	diagnoses = "";
	treatment = "";
	treatmentCost = 0;
	date = "1/1/2000";
}
MedicalRecords::MedicalRecords(string recID, string patID, string docID, string diag, string t, double tcost, string d) {  //string t is for treatment(used like this everywhere else as well)
	recordId = recID;
	patientId = patID;
	doctorId = docID;
	diagnoses = diag;
	treatment = t;
	treatmentCost = tcost;
	date = d;
}
//Helper Function
string MedicalRecords::generateRecordId()const {
	recordCounter++;
	string num = to_string(recordCounter);
	while (num.length() < 4) {
		num = "0" + num;
	}
	string id = "R-" + num;
	return id;
}
//Validating Record ID
bool MedicalRecords::isValidRecordId(string id) {
	if (id == "")
		return false;
	int len = 0;
	for (int i = 0; id[i] != '\0'; i++) {
		len++;
	}
	if (id[0] != 'R' || id[1] != '-'|| len!=6)
		return false;
	for (int i = 2; id[i] != '\0'; i++) {
		if (isdigit(id[i])==false)
			return false;
	}
	return true;
}
bool MedicalRecords::recordIdAlreadyExists(string id,string filename) {
	ifstream infile(filename);
	if (infile.is_open()) {
		string sep,rId;
		while (getline(infile, sep)) {
			getline(infile, rId);
			if (rId == id)
				return true;
			string skip;								//Skipping the rest(Only need RecordID)
			for (int i = 0; i < 6; i++) {
				getline(infile, skip);
			}
		}
		infile.close();
		return false;
	}
	return false;
}
//Validating Date
bool MedicalRecords::isLeapYear(int year) const {
	return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}
bool MedicalRecords::isValidDate(string dt) {
	int firstSlash=dt.find('/');
	if (firstSlash == string::npos)	//npos means NOT FOUND
		return false;
	int secondSlash = dt.find('/',firstSlash+1);
	if (secondSlash == string::npos)	
		return false;
	int date = stoi(dt.substr(0,firstSlash));
	int month = stoi(dt.substr(firstSlash+1,secondSlash-firstSlash-1));
	int year = stoi(dt.substr(secondSlash+1));
	if (year < 1900 || year>2100)
		return false;
	if (month < 1 || month>12)
		return false;
	if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) {
		if (date < 1 || date>31)
			return false;
	}
	else if (month == 4 || month == 6 || month == 9 || month == 11) {
		if (date < 1 || date>30)
			return false;
	}
	else {
		if (isLeapYear(year)) {
			if (date < 1 || date>29)
				return false;
		}
		else {
			if (date < 1 || date>28)
				return false;
		}
	} 
	return true;
}
void MedicalRecords::setMedicalRecords(Person* currentUser) {
	if (currentUser->Get_Role() == "doctor") {
		recordId = generateRecordId();
		Doctor* doc = dynamic_cast<Doctor*>(currentUser);
		doctorId = doc->getDoctorId();
		while (true) {
			cout << "Enter Patient ID (format P-0001)" << endl;
			cin >> patientId;
			if (!isValidPatientId(patientId)) {
				cout << "Invalid Patient ID.Try Again" << endl;
			}
			else if (!patientIdAlreadyExists(patientId, filename)) {
				cout << "Invalid! Patient ID Already Exists.Try Again" << endl;
			}
			else {
				break;
			}
		}	
		cin.ignore();
		cout << "Enter Diagnoses" << endl;
		getline(cin,diagnoses);
		cout << "Enter Treatment" << endl;
		getline(cin, treatment);
		cout << "Enter Treatment Cost" << endl;
		cin >> treatmentCost;
		while (treatmentCost < 0) {
			cout << "Invalid input! Try Again" << endl;
			cin >> treatmentCost;
		}
		cin.ignore();
		while (true) {
			cout << "Enter Date (format 1/1/2000)" << endl;
			getline(cin, date);
			if (!isValidDate(date)) {
				cout << "Invalid! Try Again" << endl;
			}
			else
				break;
		}
	}
}
//Getter Functions
string MedicalRecords::getRecordId()const {
	return recordId;
}
string MedicalRecords::getPatientId()const {
	return patientId;
}
string MedicalRecords::getDoctorId()const {
	return doctorId;
}
string MedicalRecords::getDiagnoses()const {
	return diagnoses;
}
string MedicalRecords::getTreatment()const {
	return treatment;
}
double MedicalRecords::getTreatmentCost()const {
	return treatmentCost;
}
string MedicalRecords::getDate()const {
	return date;
}
//Setter Functions
void MedicalRecords::setRecordId(string id) {
	recordId = id;
}
void MedicalRecords::setPatientId(string id) {
	patientId = id;
}
void MedicalRecords::setDoctorId(string id) {
	doctorId = id;
}
void MedicalRecords::setDiagnoses(string diag) {
	diagnoses = diag;
}
void MedicalRecords::setTreatment(string t) {
	treatment = t;
}
void MedicalRecords::setTreatmentCost(double tcost) {
	treatmentCost = tcost;
}
void MedicalRecords::setDate(string d) {
	date = d;
}
//When calling from main call this one 1 time and then the normal display function
void MedicalRecords::displayHeader() {
	cout << left;
	cout<< setw(12) << "RecordID"<< setw(12) << "PatientID"<< setw(12) << "DoctorID"<< setw(15) << "Diagnoses"<< setw(15) << "Treatment"<< setw(10) << "Cost"<< setw(12) << "Date" << endl;
	cout << "----------------------------------------------------------------------" << endl;
	cout << right;
}
void MedicalRecords::display() const {
	//Treatment can be something long(using ... to show)
	//This is just for this console, GUI will automatically handle this 
	string t = treatment.substr(0, 13);
	if (treatment.length() > 13)
		t += "...";
	cout << left;
	cout<< setw(12) << recordId<< setw(12) << patientId<< setw(12) << doctorId<< setw(15) << diagnoses<< setw(15) << t<< setw(10) << treatmentCost<< setw(12) << date << endl;
	cout << right;
}
//File Handling
void MedicalRecord::loadCounterFromFile(string filename) {		//Static Function
	ifstream infile(filename);
	int maxnum = 0;
	int num = 0;
	string sep, rId;
	if (infile.is_open()) {
		while (getline(infile, sep)) {
			getline(infile, rId);
			int num = stoi(rId.substr(2));				//stoi converts string to int
			if (maxnum < num)
				maxnum = num;
			string skip;								//Skipping the rest(Only need RecordID)
			for (int i = 0; i < 6; i++) {
				getline(infile, skip);
			}
		}
		infile.close();
	}
	recordCounter = maxnum;
}
void MedicalRecords::saveToFile(string filename)const {
	ofstream outfile(filename, ios::app);
	if (outfile.is_open()) {
		outfile << "-----------" << endl;
		outfile << recordId << endl;
		outfile << patientId << endl;
		outfile << doctorId << endl;
		outfile << diagnoses << endl;
		outfile << treatment << endl;
		outfile << treatmentCost << endl;
		outfile << date << endl;
	}
}
void MedicalRecords::loadFromFile(string filename) {
	ifstream infile(filename);
	if (infile.is_open()) {
		string seperator;
		getline(infile, seperator);
		getline(infile, recordId);
		getline(infile, patientId);
		getline(infile, doctorId);
		getline(infile, diagnoses);
		getline(infile, treatment);
		infile >> treatmentCost;
		infile.ignore();
		getline(infile,date);
	}
}
//----Managing Records-----
//Search Functions
void MedicalRecords::searchByRecordId(string filename,string id) {
	ifstream infile(filename);
	if (infile.is_open()) {
		string sep, rId, pId, dId, diag,tment,d;
		double tcost;
		while (getline(infile, sep)) {
			getline(infile, rId);
			getline(infile, pId);
			getline(infile, dId);
			getline(infile, diag);
			getline(infile, tment);
			infile >> tcost;
			infile.ignore();
			getline(infile, d);
			if (rId == id) {
				string t = tment.substr(0, 13);
				if (tment.length() > 13)
					t += "...";
				cout << left;
				cout << setw(12) << rId << setw(12) << pId << setw(12) << dId << setw(15) << diag << setw(15) << t << setw(10) << tcost << setw(12) << d << endl;
				cout << right;
				infile.close();
				return;
			}
		}
		infile.close();
		cout << "Record Not Found" << endl;
	}
}
void MedicalRecords::searchByPatientId(string filename, string id) {
	bool found = false;
	ifstream infile(filename);
	if (infile.is_open()) {
		string sep, rId, pId, dId, diag, tment, d;
		double tcost;
		while (getline(infile, sep)) {
			getline(infile, rId);
			getline(infile, pId);
			getline(infile, dId);
			getline(infile, diag);
			getline(infile, tment);
			infile >> tcost;
			infile.ignore();
			getline(infile, d);
			if (pId == id) {
				found = true;
				string t = tment.substr(0, 13);
				if (tment.length() > 13)
					t += "...";
				cout << left;
				cout << setw(12) << rId << setw(12) << pId << setw(12) << dId << setw(15) << diag << setw(15) << t << setw(10) << tcost << setw(12) << d << endl;
				cout << right;
			}
		}
		infile.close();
		if(found)
			return;
	}
	cout << "Record Not Found" << endl;
}
void MedicalRecords::searchByDoctorId(string filename, string id) {
	bool found = false;
	ifstream infile(filename);
	if (infile.is_open()) {
		string sep, rId, pId, dId, diag, tment, d;
		double tcost;
		while (getline(infile, sep)) {
			getline(infile, rId);
			getline(infile, pId);
			getline(infile, dId);
			getline(infile, diag);
			getline(infile, tment);
			infile >> tcost;
			infile.ignore();
			getline(infile, d);
			if (dId == id) {
				found = true;
				string t = tment.substr(0, 13);
				if (tment.length() > 13)
					t += "...";
				cout << left;
				cout << setw(12) << rId << setw(12) << pId << setw(12) << dId << setw(15) << diag << setw(15) << t << setw(10) << tcost << setw(12) << d << endl;
				cout << right;
			}
		}
		infile.close();
		if (found)
			return;
	}
	cout << "Record Not Found" << endl;
}
//Update/Delete Records
void MedicalRecords::updateRecords() {

}
void MedicalRecords::deleteRecords() {

}
MedicalRecords::~MedicalRecords(){}
int MedicalRecords::recordCounter = 0;		//IMP NOTE:IN MAIN DO THIS----> MedicalRecords::loadCounterFromFile("MedicalRecords.txt")