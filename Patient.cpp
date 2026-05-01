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
	linkedCNIC="";
}
Patient::Patient(string cnic, string id, string blood, string type, double Height, double Weight, string contact, string status):Person(cnic, "", -1, "", "", "", "") {
	patientId = id;
	bloodGroup = blood;
	patientType = type;
	height = Height;
	weight = Weight;
	emergencyContact = contact;
	patientStatus = status;
	linkedCNIC=cnic;
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
    ifstream infile(filename);
    if (!infile) return false;

    string separator, cnic, pid, blood, type, contact, status;
    double h, w;

    while (getline(infile, separator)) {
        if (separator != "----------") continue;
        getline(infile, cnic);      // ← read CNIC first
        getline(infile, pid);
        getline(infile, blood);
        getline(infile, type);
        infile >> h >> w;
        infile.ignore(1000, '\n');
        getline(infile, contact);
        getline(infile, status);

        if (pid == id)
            return true;
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
	patientId = id;
}
void Patient::setBloodGroup(string blood) {
	bloodGroup = blood;
}
void Patient::setPatientType(string type) {
	patientType = type;
}
void Patient::setHeight(double h) {
	if (isValidHeight(h)) {
		height = h;
	}
	else {
		height = 0;
	}
	
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
string Patient::getNameById(string patId) {
    string foundCnic = "";								//find CNIC from Patient.txt
    ifstream patient_infile("Patient.txt");
    string sep, cnic, pid, blood, type, contact, status;
    double h, w;
    while (getline(patient_infile, sep)) {
        if (sep != "----------") 
			continue;
        getline(patient_infile, cnic);
        getline(patient_infile, pid);
        getline(patient_infile, blood);
        getline(patient_infile, type);
        patient_infile >> h >> w;
        patient_infile.ignore(1000, '\n');
        getline(patient_infile, contact);
        getline(patient_infile, status);
        if (pid == patId) {
            foundCnic = cnic;
            break;
        }
    }
    patient_infile.close();
    if (foundCnic == "") 
		return patId; 

    ifstream person_infile("Person.txt");								//find name from Person.txt using CNIC
    string pcnic, name, age, gender, phone, email, address;
    while (getline(person_infile, sep)) {
        if (sep != "----------") 
			continue;
        getline(person_infile, pcnic);
        getline(person_infile, name);
        int a;
        person_infile >> a;
        person_infile.ignore(1000, '\n');
        getline(person_infile, gender);
        getline(person_infile, phone);
        getline(person_infile, email);
        getline(person_infile, address);
        if (pcnic == foundCnic) {
            person_infile.close();
            return name;
        }
    }
    person_infile.close();
    return patId;
}

void Patient::Save_To_File(ofstream& outfile) const {
    if (outfile.is_open()) {
        outfile << "----------" << "\n"
            << linkedCNIC << "\n"        
            << patientId << "\n"
            << bloodGroup << "\n"
            << patientType << "\n"
            << height << "\n"
            << weight << "\n"
            << emergencyContact << "\n"
            << patientStatus << "\n";
    }
}

void Patient::Load_From_File(ifstream& infile) {
	getline(infile, linkedCNIC);  
	getline(infile, patientId);
	getline(infile, bloodGroup);
	getline(infile, patientType);
	infile >> height;
	infile >> weight;
	infile.ignore(1000, '\n');
	getline(infile, emergencyContact);
	getline(infile, patientStatus);
}

string Patient::get_CNIC() {
	return linkedCNIC;
}
void Patient::setLinkedCNIC(string cnic){
	linkedCNIC=cnic;
}
string Patient::Get_Role() {
	return "Patient";
}

void Patient::displayInfo() const  {
	cout << "Patient ID: " << patientId << endl;
	cout << "Status:     [" << patientStatus << "]" << endl;
	cout << "Type:       " << patientType << endl;
	cout << "Blood Grp:  " << bloodGroup << endl;
	cout << "Height:     " << height << " cm | Weight: " << weight << " kg" << endl;
	cout << "Emergency Contact: " << emergencyContact << endl;
}


Patient::~Patient() {}