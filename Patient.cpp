#include"Person.h"
#include"Patient.h"

Patient::Patient() {
	patientId = "";
	bloodGroup = "";
	patientType = "";
	height = 0;
	weight = 0;
	emergencyContact = "";
	patientStatus = "";
}
Patient::Patient(string id, string blood, string type, double Height, double Weight, string contact, string status) {
	patientId = id;
	bloodGroup = blood;
	patientType = type;
	height = Height;
	weight = Weight;
	emergencyContact = contact;
	patientStatus = status;
}

bool Patient::isValidPatientId(string id) {
	if (id == "")
		return false;
	// considering patient id format is P - 0000, P - 0001...
	if (id.length() != 6)
		return false;
	if (id[0] != 'P' || id[1] != '-')
		return false;
	if (!isdigit(id[2]) || !isdigit(id[3]) || !isdigit(id[4]) || !isdigit(id[5])) {
		return false;
	}
	return true;
}
bool Patient::patientIdAlreadyExists(string id, string filename) {

}
bool Patient::isValidBloodGroup(string bloodGroup) {
	if (bloodGroup == "") {
		return false;
	}
	if (bloodGroup != "A+" && bloodGroup != "A-" && bloodGroup != "B+" && bloodGroup != "B-" && 
		bloodGroup != "B-" && bloodGroup != "AB+" && bloodGroup != "AB-" && bloodGroup != "O+" && bloodGroup != "O-") {
		return false;
	}
	return true;
}
bool Patient::isValidPatientType(string patientType) {
	if (patientType == "") {
		return false;
	}
	if (patientType != "Inpatient" && patientType != "Outpatient" && patientType != "Emergency" && patientType != "inpatient" && patientType != "outpatient" && patientType != "emergency") {
		return false;
	}
	return true;
}
bool Patient::isValidHeight(double h) {
	if (h <= 0)
	{
		return false;
	}
	if (h <= 50 || h >= 250) {
		return false;
	}
	return true;
}
bool Patient::isValidWeight(double w) {
	if (w <=0 ) {
		return false;
	}
	if (w <= 1 || w >= 300) {
		return false;
	}
	return true;
}
bool Patient::isValidContact(string contact) {
	if (contact.length() != 11)
		return false;
	bool allZeroes = true;
	for (int i = 0; i < contact.length() != 11; i++) {
		if (contact[i] != '0')
			allZeroes = false;
	}
	if (allZeroes)
		return false;
	if (contact[0] == '-')
		return false;
	return true;
}
bool Patient::isValidStatus(string status) {
	//Must be one of your defined values only — admitted / discharged / under observation
	//Should not be set to discharged if no admission date exists
	if (status != "Admitted" && status != "Discharged" && status != "admitted" && status != "discharged")
		return false;
	return true;

}

string Patient::getPatientId()const {
	return patientId;
}
string Patient::getBloodGroup() const {
	return bloodGroup;
}
string Patient::getPatientType()const {
	return patientType;
}
double Patient::getHeight()const {
	return height;
}
double Patient::getWeight()const {
	return weight;
}
string Patient::getEmergencyContact()const {
	return emergencyContact;
}
string Patient::getPatientStatus()const {
	return patientStatus;
}
void Patient::setPatientId(string id) {
	patientId = id;
}
void Patient::setBloodGroup(string blood) {
	bloodGroup = blood;
}
void Patient::setPatientType(string type) {
	patientType = type;
}
void Patient::setHeight(double h) {
	height = h;
}
void Patient::setWeight(double w) {
	weight = w;
}
void Patient::setEmergencyContact(string contact) {
	emergencyContact = contact;
}
void Patient::setPatientStatus(string status) {
	patientStatus = status;
}

void Patient:: Save_To_File(ofstream& outfile)const {
	if (outfile.is_open()) {
		outfile << "Patient File: " << endl;
		outfile << patientId << endl;
		outfile << bloodGroup << endl;
		outfile << patientType << endl;
		outfile << height << endl;
		outfile << weight << endl;
		outfile << emergencyContact << endl;
		outfile << patientStatus << endl;
	}
}
void Patient::Load_From_File(ifstream& infile) {
	if (infile.is_open()) {
		getline(infile, patiendId);
		getline(infile, bloodGroup);
		getline(infile, patientType);
		infile >> height;
		infile >> weight;
		infile.ignore();
		getline(infile, emergencyContact);
		getline(infile, patientStatus);
	}
}
string Patient::getRole() {
	return "Patient";
}

Patient::~Patient() {}