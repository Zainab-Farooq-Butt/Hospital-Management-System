#include "Person.h"
#include "Doctor.h"

// ---------------------------------------------------------------------------
// Constructors
// ---------------------------------------------------------------------------

Doctor::Doctor() : Person() {
    doctorId           = "";
    specialization     = "";
    qualification      = "";
    experienceYears    = 0;
    consultationFee    = 0.0;
    availability       = "";
    availabilityStatus = "";
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
}

// ---------------------------------------------------------------------------
// Validators
// ---------------------------------------------------------------------------

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
    if (spec == "Cardiology"  || spec == "cardiology"  ||
        spec == "Neurology"   || spec == "neurology"   ||
        spec == "Orthopedics" || spec == "orthopedics" ||
        spec == "Pediatrics"  || spec == "pediatrics"  ||
        spec == "Dermatology" || spec == "dermatology" ||
        spec == "Oncology"    || spec == "oncology"    ||
        spec == "Radiology"   || spec == "radiology"   ||
        spec == "Psychiatry"  || spec == "psychiatry"  ||
        spec == "General"     || spec == "general"     ||
        spec == "Surgery"     || spec == "surgery")
        return true;
    return false;
}

bool Doctor::isValidExperience(int exp) {
    return (exp >= 0 && exp <= 60);
}

bool Doctor::isValidFee(double fee) {
    return (fee > 0 && fee <= 1000000);
}

bool Doctor::isValidAvailabilityStatus(string status) {
    if (status == "Available"   || status == "available"   ||
        status == "Unavailable" || status == "unavailable" ||
        status == "On Leave"    || status == "on leave")
        return true;
    return false;
}

// Enforces the format:  Day[-Day] H[H][:MM]AM|PM-H[H][:MM]AM|PM
// Valid examples : "Mon-Fri 9AM-5PM"   "Sat 10:30AM-2:00PM"   "Sun 1PM-5PM"
// Invalid examples: "Mon-Fri 9-5"  "Mon-Fri 5am-3"  "Monday 9AM-5PM"
bool Doctor::isValidAvailability(string avail) {

    // ── 1. Split on the single space that divides days from times ──────────
    size_t spacePos = avail.find(' ');
    if (spacePos == string::npos) return false;

    string daysPart = avail.substr(0, spacePos);
    string timePart = avail.substr(spacePos + 1);

    if (daysPart.empty() || timePart.empty()) return false;

    // ── 2. Validate days portion ───────────────────────────────────────────
    const string validDays[] = {"Mon","Tue","Wed","Thu","Fri","Sat","Sun"};
    auto isValidDay = [&](const string& d) -> bool {
        for (const string& vd : validDays)
            if (d == vd) return true;
        return false;
    };

    size_t dashInDays = daysPart.find('-');
    if (dashInDays == string::npos) {
        // Single day e.g. "Sat"
        if (!isValidDay(daysPart)) return false;
    } else {
        // Day range e.g. "Mon-Fri"
        string day1 = daysPart.substr(0, dashInDays);
        string day2 = daysPart.substr(dashInDays + 1);
        if (!isValidDay(day1) || !isValidDay(day2)) return false;
    }

    // ── 3. Helper: validate a single time token e.g. "9AM" "10:30PM" ──────
    auto isValidTime = [](const string& t) -> bool {
        // Accept AM/PM in any case (AM, am, Am, aM)
        size_t apPos = string::npos;
        for (size_t i = 0; i + 1 < t.length(); i++) {
            char c0 = tolower(t[i]);
            char c1 = tolower(t[i + 1]);
            if ((c0 == 'a' || c0 == 'p') && c1 == 'm') {
                apPos = i;
                break;
            }
        }
        if (apPos == string::npos)        return false;   // no AM/PM found
        if (apPos + 2 != t.length())      return false;   // garbage after AM/PM

        string numPart = t.substr(0, apPos);
        if (numPart.empty())              return false;

        string hourStr, minStr;
        size_t colonPos = numPart.find(':');

        if (colonPos != string::npos) {
            // Has minutes  e.g. "10:30"
            hourStr = numPart.substr(0, colonPos);
            minStr  = numPart.substr(colonPos + 1);

            if (minStr.length() != 2)     return false;
            for (char c : minStr)
                if (!isdigit(c))          return false;
            int mn = stoi(minStr);
            if (mn < 0 || mn > 59)        return false;
        } else {
            hourStr = numPart;
        }

        if (hourStr.empty() || hourStr.length() > 2) return false;
        for (char c : hourStr)
            if (!isdigit(c))              return false;
        int hr = stoi(hourStr);
        if (hr < 1 || hr > 12)           return false;

        return true;
    };

    // ── 4. Split time part into two tokens at the '-' between them ─────────
    //       The first token ends right after its AM or PM (any case).
    size_t firstEnd = string::npos;
    for (size_t i = 0; i + 1 < timePart.length(); i++) {
        char c0 = tolower(timePart[i]);
        char c1 = tolower(timePart[i + 1]);
        if ((c0 == 'a' || c0 == 'p') && c1 == 'm') {
            firstEnd = i + 2;
            break;
        }
    }
    if (firstEnd == string::npos) return false;   // no AM/PM anywhere

    // The character right after the first token must be '-'
    if (firstEnd >= timePart.length() || timePart[firstEnd] != '-') return false;

    string time1 = timePart.substr(0, firstEnd);
    string time2 = timePart.substr(firstEnd + 1);

    return isValidTime(time1) && isValidTime(time2);
}

// ---------------------------------------------------------------------------
// Input
// ---------------------------------------------------------------------------

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
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Please enter a number." << endl;
            continue;
        }
        if (isValidExperience(exp))
            break;
        cout << "Invalid experience. Must be between 0 and 60. Try again." << endl;
    }

    // --- Consultation Fee ---
    while (true) {
        cout << "Enter Consultation Fee (PKR): ";
        cin  >> fee;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Please enter a number." << endl;
            continue;
        }
        if (isValidFee(fee))
            break;
        cout << "Invalid fee. Must be a positive value up to 1,000,000. Try again." << endl;
    }

    cin.ignore();

    // --- Availability Schedule ---
    cout << "Availability format : Day[-Day] StartAM/PM-EndAM/PM  (AM/PM case-insensitive)" << endl;
    cout << "Examples            : Mon-Fri 9AM-5PM   |   Sat 10:30AM-2:00PM   |   Sun 1PM-5PM" << endl;
    while (true) {
        cout << "Enter Availability Schedule: ";
        getline(cin, avail);
        if (isValidAvailability(avail))
            break;
        cout << "Invalid format. Use e.g. \"Mon-Fri 9AM-5PM\" or \"Sat 10:30AM-2:00PM\"." << endl;
        cout << "  - Days must be: Mon Tue Wed Thu Fri Sat Sun" << endl;
        cout << "  - Hours must be 1-12, followed by am/pm (any case)." << endl;
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

// ---------------------------------------------------------------------------
// fetchDoctorFee
// Scans the data file for a record whose Doctor ID matches the given id.
// ---------------------------------------------------------------------------

double Doctor::fetchDoctorFee(string doctorId, string filename) {
    ifstream infile(filename);
    if (!infile.is_open())
        return -1.0;

    string line;
    while (getline(infile, line)) {
        if (line == "Doctor File:") {
            string fileId;
            if (!getline(infile, fileId))
                break;

            if (fileId == doctorId) {
                string spec, qual;
                getline(infile, spec);
                getline(infile, qual);

                int    exp;
                double fee;
                infile >> exp;
                infile >> fee;

                infile.close();
                return fee;
            }
        }
    }

    infile.close();
    return -1.0;   // Doctor not found
}

// ---------------------------------------------------------------------------
// Getters
// ---------------------------------------------------------------------------

string Doctor::getDoctorId()           const { return doctorId;           }
string Doctor::getSpecialization()     const { return specialization;     }
string Doctor::getQualification()      const { return qualification;      }
int    Doctor::getExperienceYears()    const { return experienceYears;    }
double Doctor::getConsultationFee()    const { return consultationFee;    }
string Doctor::getAvailability()       const { return availability;       }
string Doctor::getAvailabilityStatus() const { return availabilityStatus; }

// ---------------------------------------------------------------------------
// Setters
// ---------------------------------------------------------------------------

void Doctor::setDoctorId(string id)          { doctorId           = id;   }
void Doctor::setSpecialization(string spec)  { specialization     = spec; }
void Doctor::setQualification(string qual)   { qualification      = qual; }
void Doctor::setExperienceYears(int exp)     { experienceYears    = exp;  }
void Doctor::setConsultationFee(double fee)  { consultationFee    = fee;  }
void Doctor::setAvailability(string avail)   { availability       = avail;}
void Doctor::setAvailabilityStatus(string s) { availabilityStatus = s;    }

// ---------------------------------------------------------------------------
// Overrides
// ---------------------------------------------------------------------------

void Doctor::Display_Info() {
    Person::Display_Info();
    cout << "Doctor ID         : " << doctorId           << endl;
    cout << "Specialization    : " << specialization     << endl;
    cout << "Qualification     : " << qualification      << endl;
    cout << "Experience (yrs)  : " << experienceYears    << endl;
    cout << "Consultation Fee  : " << consultationFee    << endl;
    cout << "Availability      : " << availability       << endl;
    cout << "Status            : " << availabilityStatus << endl;
}

void Doctor::Save_To_File(ofstream& outfile) {
    if (outfile.is_open()) {
        Person::Save_To_File(outfile);
        outfile << "Doctor File:"      << endl;
        outfile << doctorId            << endl;
        outfile << specialization      << endl;
        outfile << qualification       << endl;
        outfile << experienceYears     << endl;
        outfile << consultationFee     << endl;
        outfile << availability        << endl;
        outfile << availabilityStatus  << endl;
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
