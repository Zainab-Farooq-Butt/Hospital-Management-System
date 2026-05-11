#include "Person.h"
#include "Doctor.h"

string Doctor::To_Lower_Case(string str) {
    for (int i = 0; i < (int)str.length(); i++)
        str[i] = tolower(str[i]);
    return str;
}

Doctor::Doctor() : Person() {
    doctorId           = "";
    specialization     = "";
    qualification      = "";
    experienceYears    = 0;
    consultationFee    = 0.0;
    availability       = "";
    availabilityStatus = "";
    linkedCNIC         = "";
}

Doctor::Doctor(string id, string spec, string qual, int exp, double fee,
               string avail, string status) : Person() {
    doctorId           = id;
    specialization     = spec;
    qualification      = qual;
    experienceYears    = exp;
    consultationFee    = fee;
    availability       = avail;
    availabilityStatus = status;
    linkedCNIC         = "";
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
    if (!infile.is_open()) return false;
    string sep, cnic, did;
    while (getline(infile, sep)) {
        if (sep != "----------") continue;
        getline(infile, cnic);
        getline(infile, did);
        if (did == id) { infile.close(); return true; }
        string skip;
        for (int i = 0; i < 6; i++) getline(infile, skip);
    }
    infile.close();
    return false;
}

bool Doctor::isValidSpecialization(string spec) {
    if (spec.length() == 0)
        return false;
    spec = To_Lower_Case(spec);
    return (spec == "cardiology"  ||
            spec == "neurology"   ||
            spec == "orthopedics" ||
            spec == "pediatrics"  ||
            spec == "dermatology" ||
            spec == "oncology"    ||
            spec == "radiology"   ||
            spec == "psychiatry"  ||
            spec == "general"     ||
            spec == "surgery");
}

bool Doctor::isValidQualification(string qual) {
    qual = To_Lower_Case(qual);
    return (qual == "mbbs"      ||
            qual == "md"        ||
            qual == "bds"       ||
            qual == "fcps"      ||
            qual == "mcps"      ||
            qual == "phd"       ||
            qual == "ms"        ||
            qual == "m.phil");
}

// age is passed in explicitly so Get_Age() timing issues don't cause loops
bool Doctor::isValidExperience(int exp, int age) {
    if (exp < 0 || exp > 60)
        return false;
    // doctor must be at least 23 to have any experience (18 + ~5 yrs med school)
    if (age < 23)
        return exp == 0;
    if (exp > (age - 23))
        return false;
    return true;
}

bool Doctor::isValidFee(double fee) {
    return (fee > 0 && fee <= 1000000);
}

// Accepts any of these formats:
//   Single day:          Mon
//   Day range:           Mon-Thu  or  Mon-Fri
//   Day + time:          Mon 9am-5pm
//   Day range + time:    Mon-Fri 9am-5pm
bool Doctor::isValidAvailability(string avail) {
    if (avail.length() == 0)
        return false;

    string lower = To_Lower_Case(avail);

    string validDays[] = {"mon","tue","wed","thu","fri","sat","sun"};

    // Split on space to separate day part from optional time part
    size_t spacePos = lower.find(' ');
    string dayPart  = (spacePos == string::npos) ? lower : lower.substr(0, spacePos);
    string timePart = (spacePos == string::npos) ? ""    : lower.substr(spacePos + 1);

    // --- Validate day part ---
    size_t dayDash = dayPart.find('-');

    if (dayDash == string::npos) {
        // Single day e.g. "Mon"
        bool found = false;
        for (int i = 0; i < 7; i++)
            if (dayPart == validDays[i]) { found = true; break; }
        if (!found) return false;
    } else {
        // Day range e.g. "Mon-Fri"
        string startDay = dayPart.substr(0, dayDash);
        string endDay   = dayPart.substr(dayDash + 1);
        int startIdx = -1, endIdx = -1;
        for (int i = 0; i < 7; i++) {
            if (startDay == validDays[i]) startIdx = i;
            if (endDay   == validDays[i]) endIdx   = i;
        }
        if (startIdx == -1 || endIdx == -1) return false;
        if (startIdx >= endIdx)             return false;
    }

    // --- Validate time part (optional) ---
    if (timePart.empty())
        return true;  // no time given, that's fine

    size_t firstAm = timePart.find("am");
    size_t firstPm = timePart.find("pm");

    if (firstAm == string::npos && firstPm == string::npos)
    return false;
    size_t firstMark = min(firstAm, firstPm);
    size_t timeDash  = timePart.find('-', firstMark + 2);
    if (timeDash == string::npos)
        return false;

    string startTime = timePart.substr(0, timeDash);
    string endTime   = timePart.substr(timeDash + 1);

    if (startTime.length() < 3) return false;
    string startSuffix = startTime.substr(startTime.length() - 2);
    if (startSuffix != "am" && startSuffix != "pm") return false;

    if (endTime.length() < 3) return false;
    string endSuffix = endTime.substr(endTime.length() - 2);
    if (endSuffix != "am" && endSuffix != "pm") return false;

    bool startHasDigit = false, endHasDigit = false;
    for (char c : startTime) if (isdigit(c)) { startHasDigit = true; break; }
    for (char c : endTime)   if (isdigit(c)) { endHasDigit   = true; break; }

    return (startHasDigit && endHasDigit);
}

bool Doctor::isValidAvailabilityStatus(string status) {
    status = To_Lower_Case(status);
    return (status == "available"   ||
            status == "unavailable" ||
            status == "on leave");
}

string Doctor::generateDoctorId() {
    doctorCounter++;
    string num = to_string(doctorCounter);
    while (num.length() < 4)
        num = "0" + num;
    return "D-" + num;
}

int Doctor::getAgeFromPersonFile(string cnic) {
    ifstream infile("Person.txt");
    if (!infile.is_open())
        return -1;
    string sep, pcnic, name, gender, phone, email, address;
    int age;
    while (getline(infile, sep)) {
        if (sep != "----------") continue;
        getline(infile, pcnic);
        getline(infile, name);
        infile >> age;
        infile.ignore(1000, '\n');
        getline(infile, gender);
        getline(infile, phone);
        getline(infile, email);
        getline(infile, address);
        if (pcnic == cnic) {
            infile.close();
            return age;
        }
    }
    infile.close();
    return -1;
}

Doctor Doctor::Get_Valid_Doctor_Input(string filename, string cnic) {
    string id, spec, qual, avail, status;
    int    exp;
    double fee;

    id         = generateDoctorId();
    linkedCNIC = cnic;

    // fetch age from Person.txt using the cnic
    int age = getAgeFromPersonFile(cnic);
    if (age == -1) age = 25;  // fallback if not found

    cin.clear();
    cin.sync();

    // --- Specialization ---
    cout << "Available specializations: Cardiology, Neurology, Orthopedics, Pediatrics," << endl;
    cout << "Dermatology, Oncology, Radiology, Psychiatry, General, Surgery" << endl;
    while (true) {
        cout << "Enter Specialization: ";
        getline(cin, spec);
        if (isValidSpecialization(spec)) break;
        cout << "Invalid specialization. Try again." << endl;
    }

    // --- Qualification ---
    while (true) {
        cout << "Enter Qualification (MBBS, MD, FCPS, Bachelors, Masters, PhD etc): ";
        getline(cin, qual);
        if (isValidQualification(qual)) break;
        cout << "Invalid qualification. Try again." << endl;
    }

    // --- Experience ---
    int maxExp = (age >= 23) ? (age - 23) : 0;
    while (true) {
        cout << "Enter Years of Experience (0-" << maxExp << " for age " << age << "): ";
        cin >> exp;
        if (isValidExperience(exp, age)) break;
        if (exp < 0 || exp > 60)
            cout << "Invalid. Experience must be between 0 and 60." << endl;
        else
            cout << "Invalid. Doctor aged " << age << " cannot have " << exp
                 << " yrs experience. Max allowed: " << maxExp << " yrs." << endl;
    }

    // --- Fee ---
    while (true) {
        cout << "Enter Consultation Fee: ";
        cin >> fee;
        if (isValidFee(fee)) break;
        cout << "Invalid fee. Must be > 0 and <= 1000000." << endl;
    }

    cin.ignore();

    // --- Availability ---
    cout << "Accepted formats:" << endl;
    cout << "  Single day          : Mon" << endl;
    cout << "  Day range           : Mon-Thu" << endl;
    cout << "  Day + time          : Mon 9am-5pm" << endl;
    cout << "  Day range + time    : Mon-Fri 9am-5pm" << endl;
    while (true) {
        cout << "Enter Availability: ";
        getline(cin, avail);
        if (isValidAvailability(avail)) break;
        cout << "Invalid format. Examples: Mon  |  Mon-Thu  |  Mon-Fri 9am-5pm" << endl;
    }

    // --- Status ---
    while (true) {
        cout << "Enter Status (Available / Unavailable / On Leave): ";
        getline(cin, status);
        if (isValidAvailabilityStatus(status)) break;
        cout << "Invalid status. Try again." << endl;
    }

    return Doctor(id, spec, qual, exp, fee, avail, status);
}

string Doctor::getDoctorId()           const { return doctorId;           }
string Doctor::getSpecialization()     const { return specialization;     }
string Doctor::getQualification()      const { return qualification;      }
int    Doctor::getExperienceYears()    const { return experienceYears;    }
double Doctor::getConsultationFee()    const { return consultationFee;    }
string Doctor::getAvailability()       const { return availability;       }
string Doctor::getAvailabilityStatus() const { return availabilityStatus; }
string Doctor::get_CNIC()                    { return linkedCNIC;         }

void Doctor::setDoctorId(string id)          { doctorId           = id;   }
void Doctor::setSpecialization(string spec)  { specialization     = spec; }
void Doctor::setQualification(string qual)   { qualification      = qual; }
void Doctor::setExperienceYears(int exp)     { experienceYears    = exp;  }
void Doctor::setConsultationFee(double fee)  { consultationFee    = fee;  }
void Doctor::setAvailability(string avail)   { availability       = avail;}
void Doctor::setAvailabilityStatus(string s) { availabilityStatus = s;    }
void Doctor::setLinkedCNIC(string cnic)      { linkedCNIC         = cnic; }

double Doctor::fetchDoctorFee(string doctorId, string filename) {
    ifstream infile(filename);
    if (!infile.is_open()) return -1.0;
    string sep, cnic, did, spec, qual;
    int exp;
    double fee;
    while (getline(infile, sep)) {
        if (sep != "----------") continue;
        getline(infile, cnic);
        getline(infile, did);
        getline(infile, spec);
        getline(infile, qual);
        infile >> exp >> fee;
        infile.ignore(1000, '\n');
        string skip;
        getline(infile, skip); // availability
        getline(infile, skip); // status
        if (did == doctorId) {
            infile.close();
            return fee;
        }
    }
    infile.close();
    return -1.0;
}

string Doctor::getNameById(string docId) {
    string foundCnic = "";
    ifstream infile("Doctor.txt");
    string sep, cnic, did, spec, qual, avail, stat;
    int exp;
    double fee;
    while (getline(infile, sep)) {
        if (sep != "----------") continue;
        getline(infile, cnic);
        getline(infile, did);
        getline(infile, spec);
        getline(infile, qual);
        infile >> exp >> fee;
        infile.ignore(1000, '\n');
        getline(infile, avail);
        getline(infile, stat);
        if (did == docId) { foundCnic = cnic; break; }
    }
    infile.close();
    if (foundCnic == "") return docId;

    ifstream personFile("Person.txt");
    string pcnic, name, gender, phone, email, address;
    int a;
    while (getline(personFile, sep)) {
        if (sep != "----------") continue;
        getline(personFile, pcnic);
        getline(personFile, name);
        personFile >> a;
        personFile.ignore(1000, '\n');
        getline(personFile, gender);
        getline(personFile, phone);
        getline(personFile, email);
        getline(personFile, address);
        if (pcnic == foundCnic) { personFile.close(); return name; }
    }
    personFile.close();
    return docId;
}

void Doctor::Display_Info() {
    cout << "Doctor ID         : " << doctorId           << endl;
    cout << "Specialization    : " << specialization     << endl;
    cout << "Qualification     : " << qualification      << endl;
    cout << "Experience (yrs)  : " << experienceYears    << endl;
    cout << "Consultation Fee  : " << consultationFee    << endl;
    cout << "Availability      : " << availability       << endl;
    cout << "Status            : " << availabilityStatus << endl;
}

void Doctor::loadCounterFromFile(string filename) {
    ifstream infile(filename);
    int maxnum = 0;
    string sep, cnic, did;
    if (infile.is_open()) {
        while (getline(infile, sep)) {
            if (sep != "----------") continue;
            getline(infile, cnic);
            getline(infile, did);
            if (did.length() < 3) continue;
            int num = stoi(did.substr(2));
            if (num > maxnum) maxnum = num;
            string skip;
            for (int i = 0; i < 6; i++)
                getline(infile, skip);
        }
        infile.close();
    }
    doctorCounter = maxnum;
}

void Doctor::Save_To_File(ofstream& outfile) {
    if (outfile.is_open()) {
        outfile << "----------\n";
        outfile << linkedCNIC         << "\n";
        outfile << doctorId           << "\n";
        outfile << specialization     << "\n";
        outfile << qualification      << "\n";
        outfile << experienceYears    << "\n";
        outfile << consultationFee    << "\n";
        outfile << availability       << "\n";
        outfile << availabilityStatus << "\n";
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
int Doctor::doctorCounter = 0;