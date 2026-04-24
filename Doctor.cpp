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

Doctor Doctor::Get_Valid_Doctor_Input(string filename) {
    string id, spec, qual, avail, status;
    int exp;
    double fee;

    // --- Doctor ID ---
    while (true) {
        cout << "Enter Doctor ID (format: D-XXXX): ";
        cin >> id;

        if (!isValidDoctorId(id)) {
            cout << "Invalid format. Must be D-XXXX." << endl;
        }
        else if (doctorIdAlreadyExists(id, filename)) {
            cout << "Doctor ID already exists. Try again." << endl;
        }
        else {
            break;
        }
    }

    cin.ignore();

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

void Doctor::Display_Info() {
    cout << "Doctor ID         : " << doctorId          << endl;
    cout << "Specialization    : " << specialization    << endl;
    cout << "Qualification     : " << qualification     << endl;
    cout << "Experience (yrs)  : " << experienceYears   << endl;
    cout << "Consultation Fee  : " << consultationFee   << endl;
    cout << "Availability      : " << availability      << endl;
    cout << "Status            : " << availabilityStatus << endl;
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
