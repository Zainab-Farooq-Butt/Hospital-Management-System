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
Patient::Patient(string id, string blood, string type, double Height, double Weight, string contact, string status):Person() {
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
	ifstream infile;
	infile.open(filename, ios::in);
	if (infile.is_open()) {
		string line;
		while (getline(infile, line)) {
			if (line == id)
			{
				infile.close();
				return true;
			}
		}
	}
	return false;
}
bool Patient::isValidBloodGroup(string bloodGroup) {
	if (bloodGroup == "") {
		return false;
	}
	if (bloodGroup != "A+" && bloodGroup != "A-" && bloodGroup != "B+"  && bloodGroup != "B-" && bloodGroup != "AB+" &&
		bloodGroup != "AB-" && bloodGroup != "O+" && bloodGroup != "O-") {
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
	if (h <= 50 || h >= 250) {
		return false;
	}
	return true;
}
bool Patient::isValidWeight(double w) {
	if (w <= 1 || w >= 300) {
		return false;
	}
	return true;
}
bool Patient::isValidContact(string contact) {
	if (contact.length() != 11)
		return false;
	bool allZeroes = true;
	for (int i = 0; i < (int)contact.length(); i++) {
		if (contact[i] != '0')
			allZeroes = false;
		if (!isdigit(contact[i]))
			return false;
	}
	if (allZeroes)
		return false;
	return true;
}
bool Patient::isValidStatus(string status) {
	//Must be one of your defined values only — admitted / discharged / under observation
	//Should not be set to discharged if no admission date exists
	if (status != "Admitted" && status != "Discharged" && status != "admitted" && status != "discharged"&&status!="under observation"&&status!="Under Observation")
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
	if (!isValidPatientId(id)) {
		while (true) {
			cout << "Enter patient ID: ";
			cin >> id;
			if (isValidPatientId(id))
				break;
			cout << "Invalid patient ID. Should be in format P-0000. Try again." << endl;
		}
		patientId = id;
	}

	else
		patientId = id;
}
void Patient::setBloodGroup(string blood) {
	if (!isValidBloodGroup(blood)) {
		while (true) {
			cout << "Enter blood group: ";
			cin >> blood;
			if (isValidBloodGroup(blood))
				break;
			cout << "Invalid blood group. Should be one of A+, A-, B+, B-, AB+, AB-, O+, O-. Try again." << endl;
		}
		bloodGroup = blood;
	}

	else
		bloodGroup = blood;
	
}
void Patient::setPatientType(string type) {
	if (!isValidPatientType(type)) {
		while (true) {
			cout << "Enter patient type: ";
			cin >> type;
			if (isValidPatientType(type))
				break;
			cout << "Invalid patient type. Should be inpatient, outpatient or emergency. Try again." << endl;
		}
		patientType = type;
	}

	else
		patientType = type;
}



void Patient::setHeight(double h) {
	if (!isValidHeight(h)) {
		while (true) {
			cout << "Enter height: ";
			cin >> h;
			if (isValidHeight(h))
				break;
			cout << "Invalid height. Should be between 50 and 250 cm. Try again. " << endl;
		}
		height = h;
	}

	else
		height = h;
}
void Patient::setWeight(double w) {
	if (!isValidWeight(w)) {
		while (true) {
			cout << "Enter weight: ";
			cin >> w;
			if (isValidWeight(h))
				break;
			cout << "Invalid weight. Should be between 1 and 300 kg. Try again. " << endl;
		}
		weight = w;
	}

	else
		weight = w;
}
void Patient::setEmergencyContact(string contact) {
	
	if (!isValidContact(contact)) {
		while (true) {
			cout << "Enter emergency contact number: ";
			cin >> contact;
			if (isValidContact(contact))
				break;
			cout << "Invalid contact number. Should have 11 digits, cannot be all zeroes. Try again." << endl;
		}
		emergencyContact = contact;
	}

	else
		emergencyContact = contact;
}
void Patient::setPatientStatus(string status) {
	if (!isValidStatus(status)) {
		while (true) {
			cout << "Enter patient status: ";
			cin >> status;
			if (isValidStatus(status))
				break;
			cout << "Invalid patient status. Should be admitted, discharged or under observation. Try again." << endl;
		}
		patientStatus = status;
	}

	else
		patientStatus = status;
}

void Patient::Save_To_File(ofstream& outfile) const {
	if (outfile.is_open()) {
		outfile << patientId << "\n"
			<< bloodGroup << "\n"
			<< patientType << "\n"
			<< height << "\n"
			<< weight << "\n"
			<< emergencyContact << "\n"
			<< patientStatus << endl;
	}
}

void Patient::Load_From_File(ifstream& infile) {
	getline(infile, patientId);
	getline(infile, bloodGroup);
	getline(infile, patientType);
	infile >> height;
	infile >> weight;
	infile.ignore(1000, '\n');
	getline(infile, emergencyContact);
	getline(infile, patientStatus);
}
string Patient::getRole() {
	return "Patient";
}

void Patient::displayInfo() const {
	Person::Display_Info << end;
	cout << "Patient ID: " << patientId << endl;
	cout << "Status:     [" << patientStatus << "]" << endl;
	cout << "Type:       " << patientType << endl;
	cout << "Blood Grp:  " << bloodGroup << endl;
	cout << "Height:     " << height << " cm | Weight: " << weight << " kg" << endl;
	cout << "Emergency Contact: " << emergencyContact << endl;
}


Patient::~Patient() {}

