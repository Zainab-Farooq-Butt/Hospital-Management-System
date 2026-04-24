#include "Person.h"
#include "Doctor.h"
Doctor::Doctor() : Person() {
    doctorId          = "";
    specialization    = "";
    qualification     = "";
    experienceYears   = 0;
    consultationFee   = 0.0;
    availability      = "";
    availabilityStatus = "";
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
    // Accepted specializations
    if (spec == "Cardiology"    || spec == "cardiology"    ||
        spec == "Neurology"     || spec == "neurology"     ||
        spec == "Orthopedics"   || spec == "orthopedics"   ||
        spec == "Pediatrics"    || spec == "pediatrics"    ||
        spec == "Dermatology"   || spec == "dermatology"   ||
        spec == "Oncology"      || spec == "oncology"      ||
        spec == "Radiology"     || spec == "radiology"     ||
        spec == "Psychiatry"    || spec == "psychiatry"    ||
        spec == "General"       || spec == "general"       ||
        spec == "Surgery"       || spec == "surgery")
        return true;
    return false;
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

bool Doctor::isValidAvailabilityStatus(string status) {
    if (status == "Available"     || status == "available"     ||
        status == "Unavailable"   || status == "unavailable"   ||
        status == "On Leave"      || status == "on leave")
        return true;
    return false;
}

Doctor Doctor::Get_Valid_Doctor_Input(string filename) {
    string id, spec, qual, avail, status;
    int    exp;
    double fee;

    // --- Doctor ID ---
    while (true) {
        cout << "Enter Doctor ID (format: D-0001): ";
        cin  >> id;
        if (!isValidDoctorId(id)) {
            cout << "Invalid Doctor ID format. Must be D-XXXX (4 digits). Try again." << endl;
        } else if (doctorIdAlreadyExists(id, filename)) {
            cout << "Doctor ID already exists. Try again." << endl;
        } else {
            break;
        }
    }

    cin.ignore();

    // --- Specialization ---
    cout << "Available specializations: Cardiology, Neurology, Orthopedics, Pediatrics," << endl;
    cout << "  Dermatology, Oncology, Radiology, Psychiatry, General, Surgery" << endl;
    while (true) {
        cout << "Enter Specialization: ";
        getline(cin, spec);
        if (isValidSpecialization(spec))
            break;
        cout << "Invalid specialization. Please choose from the list above." << endl;
    }

    // --- Qualification ---
    while (true) {
        cout << "Enter Qualification (e.g. MBBS, MD, FCPS): ";
        getline(cin, qual);
        if (qual.length() > 0)
            break;
        cout << "Qualification cannot be empty. Try again." << endl;
    }

    // --- Experience ---
    while (true) {
        cout << "Enter Years of Experience (0-60): ";
        cin  >> exp;
        if (isValidExperience(exp))
            break;
        cout << "Invalid experience. Must be between 0 and 60. Try again." << endl;
    }

    // --- Consultation Fee ---
    while (true) {
        cout << "Enter Consultation Fee (PKR): ";
        cin  >> fee;
        if (isValidFee(fee))
            break;
        cout << "Invalid fee. Must be a positive value. Try again." << endl;
    }

    cin.ignore();

    // --- Availability schedule ---
    while (true) {
        cout << "Enter Availability Schedule (e.g. Mon-Fri 9AM-5PM): ";
        getline(cin, avail);
        if (avail.length() > 0)
            break;
        cout << "Availability cannot be empty. Try again." << endl;
    }

    // --- Availability Status ---
    while (true) {
        cout << "Enter Availability Status (Available / Unavailable / On Leave): ";
        getline(cin, status);
        if (isValidAvailabilityStatus(status))
            break;
        cout << "Invalid status. Enter Available, Unavailable, or On Leave." << endl;
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


void Doctor::setDoctorId(string id)           { doctorId          = id;     }
void Doctor::setSpecialization(string spec)   { specialization    = spec;   }
void Doctor::setQualification(string qual)    { qualification     = qual;   }
void Doctor::setExperienceYears(int exp)      { experienceYears   = exp;    }
void Doctor::setConsultationFee(double fee)   { consultationFee   = fee;    }
void Doctor::setAvailability(string avail)    { availability      = avail;  }
void Doctor::setAvailabilityStatus(string s)  { availabilityStatus = s;     }

void Doctor::Display_Info() {
    Person::Display_Info();
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
        Person::Save_To_File(outfile);          
        outfile << "Doctor File:" << endl;
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
        Person::Load_From_File(infile);         
        string marker;
        getline(infile, marker);                
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
