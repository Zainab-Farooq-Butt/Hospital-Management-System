#include "Person.h"
#include "Doctor.h"

string Doctor::To_Lower_Case(string str){
    for (int i = 0; i < str.length(); i++)
    str[i] = tolower(str[i]);   
    return str;
}

Doctor::Doctor() : Person() {
    doctorId          = "";
    specialization    = "";
    qualification     = "";
    experienceYears   = 0;
    consultationFee   = 0.0;
    availability      = "";
    availabilityStatus = "";
    linkedCNIC ="";
}

Doctor::Doctor(string id, string spec, string qual, int exp, double fee,
               string avail, string status) : Person() {
    doctorId          = id;
    specialization    = spec;
    qualification     = qual;
    experienceYears   = exp;
    consultationFee   = fee;
    availability      = avail;
    availabilityStatus = status;
    linkedCNIC="";
}
bool Doctor::isValidDoctorId(string id) {
    if (id.length() != 6)
        return false;

    if (id[0] != 'D' || id[1] != '-')
        return false;

    for (int i = 2; i < 6; i++) {
        if (!isdigit(id[i]))
            return false;
    }

    return true;
}
bool Doctor::doctorIdAlreadyExists(string id, string filename) {
    ifstream infile(filename);
    if (infile.is_open()) {
        string line;
        while (getline(infile, line)) {
     
            if (line == id) {
                infile.close();
                return true;
            }
        }
        infile.close();
    }
    return false;
}

bool Doctor::isValidSpecialization(string spec) {
    if (spec.length() == 0)
        return false;

    spec = To_Lower_Case(spec);

    if (spec == "cardiology"   ||
        spec == "neurology"    ||
        spec == "orthopedics"  ||
        spec == "pediatrics"   ||
        spec == "dermatology"  ||
        spec == "oncology"     ||
        spec == "radiology"    ||
        spec == "psychiatry"   ||
        spec == "general"      ||
        spec == "surgery")
        return true;

    return false;
}

bool Doctor::isValidQualification(string qual) {
    qual = To_Lower_Case(qual);

    return (
        qual == "o levels" ||
        qual == "matric" ||
        qual == "a levels" ||
        qual == "fsc" ||
        qual == "ics" ||
        qual == "bachelors" ||
        qual == "masters" ||
        qual == "phd" ||
        qual == "mbbs" ||
        qual == "md" ||
        qual == "fcps"
    );
}

bool Doctor::isValidExperience(int exp) {
    if (exp < 0 || exp > 60)
        return false;
    return true;
}

bool Doctor::isValidFee(double fee) {
    if (fee <= 0 || fee > 1000000)
        return false;
    return true;
}

bool Doctor::isValidAvailability(string availability) {
    if (availability.length() == 0)
        return false;

    string lower = To_Lower_Case(availability);

    // must contain a range like "-"
    if (lower.find('-') == string::npos)
        return false;

    // must contain AM or PM
    if (lower.find("am") == string::npos &&
        lower.find("pm") == string::npos)
        return false;

    // must contain at least one digit
    for (char c : availability) {
        if (isdigit(c))
            return true;
    }

    return false;
}

bool Doctor::isValidAvailabilityStatus(string status) {
    status = To_Lower_Case(status);

    if (status == "available"   ||
        status == "unavailable" ||
        status == "on leave")
        return true;

    return false;
}

string Doctor::generateDoctorId() {
    doctorCounter++;
    string num = to_string(doctorCounter);
    while (num.length() < 4) {
        num = "0" + num;
    }
    return "D-" + num;
}

Doctor Doctor::Get_Valid_Doctor_Input(string filename) {
    string id, spec, qual, avail, status;
    int exp;
    double fee;

    // --- Doctor ID ---
    id=generateDoctorId();
    cin.clear();
    cin.sync();
    // --- Specialization ---
    cout << "Available specializations: Cardiology, Neurology, Orthopedics, Pediatrics," << endl;
    cout << "Dermatology, Oncology, Radiology, Psychiatry, General, Surgery" << endl;

    while (true) {
        cout << "Enter Specialization: ";
        getline(cin, spec);

        if (isValidSpecialization(spec))
            break;

        cout << "Invalid specialization. Try again." << endl;
    }

    // --- Qualification ---
    while (true) {
        cout << "Enter Qualification (MBBS, MD, FCPS, Bachelors, Masters, PhD etc): ";
        getline(cin, qual);

        if (isValidQualification(qual))
            break;

        cout << "Invalid qualification. Try again." << endl;
    }

    // --- Experience ---
    while (true) {
        cout << "Enter Years of Experience (0-60): ";
        cin >> exp;

        if (isValidExperience(exp))
            break;

        cout << "Invalid experience. Must be 0-60." << endl;
    }

    // --- Fee ---
    while (true) {
        cout << "Enter Consultation Fee: ";
        cin >> fee;

        if (isValidFee(fee))
            break;

        cout << "Invalid fee. Must be > 0 and reasonable." << endl;
    }

    cin.ignore();

    // --- Availability ---
    while (true) {
        cout << "Enter Availability (e.g. Mon-Fri 9AM-5PM): ";
        getline(cin, avail);

        if (isValidAvailability(avail))
            break;

        cout << "Invalid format. Example: Mon-Fri 9AM-5PM" << endl;
    }

    // --- Status ---
    while (true) {
        cout << "Enter Status (Available / Unavailable / On Leave): ";
        getline(cin, status);

        if (isValidAvailabilityStatus(status))
            break;

        cout << "Invalid status. Try again." << endl;
    }

    return Doctor(id, spec, qual, exp, fee, avail, status);
}

string Doctor::getDoctorId() const        { return doctorId;          }
string Doctor::getSpecialization() const  { return specialization;    }
string Doctor::getQualification() const   { return qualification;     }
int    Doctor::getExperienceYears() const { return experienceYears;   }
double Doctor::getConsultationFee() const { return consultationFee;   }
string Doctor::getAvailability() const    { return availability;      }
string Doctor::getAvailabilityStatus() const { return availabilityStatus; }
string Doctor::get_CNIC() { return linkedCNIC; }


void Doctor::setDoctorId(string id)           { doctorId          = id;     }
void Doctor::setSpecialization(string spec)   { specialization    = spec;   }
void Doctor::setQualification(string qual)    { qualification     = qual;   }
void Doctor::setExperienceYears(int exp)      { experienceYears   = exp;    }
void Doctor::setConsultationFee(double fee)   { consultationFee   = fee;    }
void Doctor::setAvailability(string avail)    { availability      = avail;  }
void Doctor::setAvailabilityStatus(string s)  { availabilityStatus = s;     }
void Doctor::setLinkedCNIC(string cnic) { linkedCNIC = cnic; };

double Doctor::fetchDoctorFee(string doctorId, string filename) {
    ifstream infile(filename);
    if (!infile.is_open())
        return 0.0;

    string line;

    while (getline(infile, line)) {

        if (line == "----------") {

            string cnic, fileId, spec, qual, exp, fee;

            getline(infile, cnic);
            getline(infile, fileId);

            if (fileId == doctorId) {

                getline(infile, spec);
                getline(infile, qual);
                getline(infile, exp);
                getline(infile, fee);

                infile.close();
                return stod(fee);
            }
            else {
                // skip remaining lines of this doctor block
                for (int i = 0; i < 5; i++)
                    getline(infile, line);
            }
        }
    }

    infile.close();
    return -1.0;
}
string Doctor::getNameById(string docId) {
    string foundCnic = "";                          // find CNIC from Doctor.txt
    ifstream infile("Doctor.txt");
    string sep, cnic, did, spec, qual, avail, stat;
    int exp;
    double fee;
    while (getline(infile, sep)) {
        if (sep != "----------") 
            continue;
        getline(infile, cnic);
        getline(infile, did);
        getline(infile, spec);
        getline(infile, qual);
        infile >> exp >> fee;
        infile.ignore(1000, '\n');
        getline(infile, avail);
        getline(infile, stat);
        if (did == docId) {
            foundCnic = cnic;
            break;
        }
    }
    infile.close();
    if (foundCnic == "") 
        return docId;

    ifstream personFile("Person.txt");              // find name from Person.txt using CNIC
    string pcnic, name, gender, phone, email, address;
    int a;
    while (getline(personFile, sep)) {
        if (sep != "----------") 
            continue;
        getline(personFile, pcnic);
        getline(personFile, name);
        personFile >> a;
        personFile.ignore(1000, '\n');
        getline(personFile, gender);
        getline(personFile, phone);
        getline(personFile, email);
        getline(personFile, address);
        if (pcnic == foundCnic) {
            personFile.close();
            return name;
        }
    }
    personFile.close();
    return docId;
}
void Doctor::Display_Info() {
    cout << "Doctor ID         : " << doctorId          << endl;
    cout << "Specialization    : " << specialization    << endl;
    cout << "Qualification     : " << qualification     << endl;
    cout << "Experience (yrs)  : " << experienceYears   << endl;
    cout << "Consultation Fee  : " << consultationFee   << endl;
    cout << "Availability      : " << availability      << endl;
    cout << "Status            : " << availabilityStatus << endl;
}

void Doctor::loadCounterFromFile(string filename) {
    ifstream infile(filename);
    int maxnum = 0;
    string sep, cnic, did;
    if (infile.is_open()) {
        while (getline(infile, sep)) {
            if (sep != "----------") 
                continue;
            getline(infile, cnic);   
            getline(infile, did);    
            if (did.length() < 3) continue;
            int num = stoi(did.substr(2));  // strips "D-"
            if (num > maxnum)
                maxnum = num;
            string skip;
            for (int i = 0; i < 6; i++)    // skip remaining 6 fields
                getline(infile, skip);
        }
        infile.close();
    }
    doctorCounter = maxnum;
}

void Doctor::Save_To_File(ofstream& outfile) {
    if (outfile.is_open()) {
        outfile << "----------\n";
        outfile << linkedCNIC      << "\n";
        outfile << doctorId           << endl;
        outfile << specialization     << endl;
        outfile << qualification      << endl;
        outfile << experienceYears    << endl;
        outfile << consultationFee    << endl;
        outfile << availability       << endl;
        outfile << availabilityStatus << endl;
    }
}

void Doctor::Load_From_File(ifstream& infile) {
    if (infile.is_open()) { 
        getline(infile, linkedCNIC);     
        getline(infile, doctorId);
        getline(infile, specialization);
        getline(infile, qualification);
        infile >> experienceYears;
        infile >> consultationFee;
        infile.ignore();
        getline(infile, availability);
        getline(infile, availabilityStatus);
    }
}

string Doctor::Get_Role() { return "Doctor"; }

Doctor::~Doctor() {}
int Doctor::doctorCounter=0;