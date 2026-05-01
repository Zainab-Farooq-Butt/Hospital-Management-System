#include "Person.h"
#include "Patient.h"
#include "Doctor.h"
#include "MedicalRecords.h"

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
bool MedicalRecords::recordIdAlreadyExists(string id) {
	ifstream infile("MedicalRecords.txt");
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
	if (isValidRecordId(id))
		recordId = id;
	else
		cout << "Invalid Record Id" << endl;
}
void MedicalRecords::setPatientId(string id) {
	Patient p;
	if (p.isValidPatientId(id))
		patientId = id;
	else
		cout << "Invalid Patient Id" << endl;
}
void MedicalRecords::setDoctorId(string id) {
	Doctor d;
	if (d.isValidDoctorId(id))
		doctorId = id;
	else
		cout << "Invalid Doctor Id" << endl;
}
void MedicalRecords::setDiagnoses(string diag) {
	if (diag != "")
		diagnoses = diag;
	else
		cout << "Diagnoses cannot be empty." << endl;
}
void MedicalRecords::setTreatment(string t) {
	if (t != "")
		treatment = t;
	else
		cout << "Treatment cannot be empty." << endl;
}
void MedicalRecords::setTreatmentCost(double tcost) {
	if (tcost >= 0)
		treatmentCost = tcost;
	else
		cout << "Treatment cost cannot be negative." << endl;
}
void MedicalRecords::setDate(string d) {
	if (isValidDate(d))
		date = d;
	else
		cout << "Invalid date." << endl;
}
//When calling from main call this one 1 time and then the normal display function
void MedicalRecords::displayHeader() {
    cout << left;
    cout << setw(12) << "RecordID"
         << setw(20) << "Patient"
         << setw(20) << "Doctor"
         << setw(15) << "Diagnoses"
         << setw(15) << "Treatment"
         << setw(10) << "Cost"
         << setw(12) << "Date" << endl;
    cout << string(104, '-') << endl;
    cout << right;
}
//Displays 1 Record(Used as helper)
void MedicalRecords::display() const {
	//Treatment can be something long(using ... to show)
	//This is just for this console, GUI will automatically handle this 
	Patient p;
    Doctor d;
    string t = treatment.substr(0, 13);
    if (treatment.length() > 13)
        t += "...";
    cout << left;
    cout << setw(12) << recordId
         << setw(20) << p.getNameById(patientId)
         << setw(20) << d.getNameById(doctorId)
         << setw(15) << diagnoses
         << setw(15) << t
         << setw(10) << treatmentCost
         << setw(12) << date << endl;
    cout << right;
}
//----Managing Records-----
//Display/Search Functions
void MedicalRecords::displayAllRecords(string filename) {
	ifstream infile(filename);
	if (!infile.is_open()) {
		cout << "Error Opening File" << endl;
		return;
	}
	string sep;
	bool empty = true;
	displayHeader();
	while (getline(infile, sep)) {
		getline(infile, recordId);
		getline(infile, patientId);
		getline(infile, doctorId);
		getline(infile, diagnoses);
		getline(infile, treatment);
		infile >> treatmentCost;
		infile.ignore();
		getline(infile, date);
		empty = false;
		display();
	}
	infile.close();
	if (empty)
		cout << "Records not found" << endl;
}
bool MedicalRecords::searchByRecordId(string id,string filename) {
	bool found = false;
	ifstream infile(filename);
	if (infile.is_open()) {
		displayHeader();
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
   				found = true;
   				recordId=rId,patientId=pId,doctorId=dId,diagnoses=diag,treatment=tment,treatmentCost=tcost,date=d;
    			display();
   				infile.close();
    			return found;
			}
		}
		infile.close();
	}
	return found;
}
bool MedicalRecords::searchByPatientId(string id,string filename) {
	bool found = false;
	ifstream infile(filename);
	if (infile.is_open()) {
		displayHeader();
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
   				recordId=rId,patientId=pId,doctorId=dId,diagnoses=diag,treatment=tment,treatmentCost=tcost,date=d;
    			display();
			}
		}
		infile.close();
	}
	return found;
}
bool MedicalRecords::searchByDoctorId(string id,string filename) {
	bool found = false;
	ifstream infile(filename);
	if (infile.is_open()) {
		displayHeader();
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
   				recordId=rId,patientId=pId,doctorId=dId,diagnoses=diag,treatment=tment,treatmentCost=tcost,date=d;
    			display();
			}
		}
		infile.close();
	}
	return found;
}
void MedicalRecords::fetchFromFile(string id){
	ifstream infile("MedicalRecords.txt");
	if(infile.is_open()){
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
			if(rId==id){
				recordId=rId;
				patientId=pId;
				doctorId=dId;
				treatmentCost=tcost;
				infile.close();
				return;
			}
		}
		infile.close();
	}
}
//Add/Update/Delete Records
void MedicalRecords::setMedicalRecords(string currentUser,string filename) {
	if (currentUser != "Doctor") {
		cout<<"Access Denied"<<endl;
		return;
	}
	recordId = generateRecordId();
	string docId;
	Doctor d;
	while(true){
		cout << "Enter your Doctor ID: " << endl;
    	cin >> docId;
		if (!d.isValidDoctorId(docId)) {
			cout << "Invalid doctor ID.Try Again" << endl;
		}
		else if (!d.doctorIdAlreadyExists(docId, filename)) {
			cout << "This doctor doesn't exist.Try Again" << endl;
			}
		else 
			break;
	}
	while (true) {
		cout << "Enter Patient ID (format P-0001)" << endl;
		cin >> patientId;
		Patient p;
		if (!p.isValidPatientId(patientId)) {
			cout << "Invalid patient ID.Try Again" << endl;
		}
		else if (!p.patientIdAlreadyExists(patientId, filename)) {
			cout << "This patient doesn't exist.Try Again" << endl;
		}
		else {
			break;
		}
	}
	cin.ignore();
	cout << "Enter Diagnoses" << endl;
	getline(cin, diagnoses);
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
void MedicalRecords::updateRecords(string currentUser, string filename) {
	if (currentUser != "DOCTOR") {
		cout << "Access Denied." << endl;
		return;
	}
	string docId,recId;
	Doctor d;
	while(true){
		cout << "Enter your Doctor ID: " << endl;
   		cin >> docId;
		if (!d.isValidDoctorId(docId)) {
			cout << "Invalid doctor ID.Try Again" << endl;
		}
		else if (!d.doctorIdAlreadyExists(docId, filename)) {
			cout << "This doctor doesn't exist.Try Again" << endl;
			}
		else 
			break;
	}
	searchByDoctorId(docId, filename);
	string rIds[100], dIds[100], pIds[100], diags[100], ts[100], dates[100];
	double tcosts[100];
	string sep;
	int count = 0;
	ifstream infile(filename);
	if (!infile.is_open()) {
		cout << "Error Opening File" << endl;
		return;
	}
	while (getline(infile, sep)) {
		getline(infile, rIds[count]);
		getline(infile, pIds[count]);
		getline(infile, dIds[count]);
		getline(infile, diags[count]);
		getline(infile, ts[count]);
		infile >> tcosts[count];
		infile.ignore();
		getline(infile, dates[count]);
		count++;
	}
	infile.close();
	cout << "Enter Record ID of the record you want to update" << endl;
	cin >> recId;
	while (!isValidRecordId(recId)) {
		cout << "Incorrect Record ID.Try Again" << endl;
		cin >> recId;
	}
	int index = -1;
	for (int i = 0; i < count; i++) {
		if (recId == rIds[i] && docId == dIds[i]) {
			index = i;
			break;
		}
	}
	if (index == -1) {
		cout << "Record not found or doesn't belong to you" << endl;
		return;
	}
	cin.ignore();
	cout << "Update Diagnoses" << endl;
	getline(cin, diags[index]);
	cout << "Update Treatment" << endl;
	getline(cin, ts[index]);
	cout << "Enter Treatment Cost" << endl;
	cin >> tcosts[index];
	while (tcosts[index] < 0) {
		cout << "Invalid input! Try Again" << endl;
		cin >> tcosts[index];
	}
	cin.ignore();
	while (true) {
		cout << "Update Date (format 1/1/2000)" << endl;
		getline(cin, dates[index]);
		if (!isValidDate(dates[index])) {
			cout << "Invalid! Try Again" << endl;
		}
		else
			break;
	}
	ofstream outfile(filename);
	if (!outfile.is_open()) {
		cout << "Error writing to file" << endl;
		return;
	}
	for (int i = 0; i < count; i++) {
		outfile << "-----------" << endl;
		outfile << rIds[i] << endl;
		outfile << pIds[i] << endl;
		outfile << dIds[i] << endl;
		outfile << diags[i] << endl;
		outfile << ts[i] << endl;
		outfile << tcosts[i] << endl;
		outfile << dates[i] << endl;
	}
	outfile.close();
	cout << "Record Updated Succesfully!" << endl;
}
void MedicalRecords::deleteRecords(string currentUser,string filename) {
	if (currentUser!= "ADMIN") {
		cout << "Access Denied.Only Admin can delete records" << endl;
		return;
	}
	displayAllRecords(filename);
	string recId;
	cout << "Enter Record ID of the record you want to delete" << endl;
	cin >> recId;
	while (!isValidRecordId(recId)) {
		cout << "Incorrect Record ID\nTry Again" << endl;
		cin >> recId;
	}
	string rIds[100], dIds[100], pIds[100], diags[100], ts[100], dates[100];
	double tcosts[100];
	string sep;
	int count = 0;
	ifstream infile(filename);
	if (!infile.is_open()) {
		cout << "Error Opening File" << endl;
		return;
	}
	while (getline(infile, sep)) {
		getline(infile, rIds[count]);
		getline(infile, pIds[count]);
		getline(infile, dIds[count]);
		getline(infile, diags[count]);
		getline(infile, ts[count]);
		infile >> tcosts[count];
		infile.ignore();
		getline(infile, dates[count]);
		count++;
	}
	infile.close();
	int index = -1;
	for (int i = 0; i < count; i++) {
		if (recId == rIds[i]) {
			index = i;
			break;
		}
	}
	if (index == -1) {
		cout << "Record not found" << endl;
		return;
	}
	for (int i = index; i < count - 1; i++) {
		rIds[i] = rIds[i + 1];
		pIds[i] = pIds[i + 1];
		dIds[i] = dIds[i + 1];
		diags[i] = diags[i + 1];
		ts[i] = ts[i + 1];
		tcosts[i] = tcosts[i + 1];
		dates[i] = dates[i + 1];
	}
	count--;
	ofstream outfile(filename);
	if (!outfile.is_open()) {
		cout << "Error writing to file" << endl;
		return;
	}
	for (int i = 0; i < count; i++) {
		outfile << "-----------" << endl;
		outfile << rIds[i] << endl;
		outfile << pIds[i] << endl;
		outfile << dIds[i] << endl;
		outfile << diags[i] << endl;
		outfile << ts[i] << endl;
		outfile << tcosts[i] << endl;
		outfile << dates[i] << endl;
	}
	outfile.close();
	cout << "Record Deleted Succesfully!" << endl;
}
//File Handling
void MedicalRecords::loadCounterFromFile(string filename) {		//Static Function
	ifstream infile(filename);
	int maxnum = 0;
	int num = 0;
	string sep, rId;
	if (infile.is_open()) {
		while (getline(infile, sep)) {
			getline(infile, rId);
			if(rId.length() < 3) 
                continue;
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
		getline(infile, date);
	}
}
MedicalRecords::~MedicalRecords(){}
int MedicalRecords::recordCounter = 0;		