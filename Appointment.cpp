#include "Appointment.h"
#include<ctime>

Appointment::Appointment() {
    appointmentId = "";
    patientId     = "";
    doctorId      = "";
    date          = "";
    timeSlot      = "";
    reason        = "";
    status        = "";
}

Appointment::Appointment(string appId, string patId, string docId,
                         string d, string time, string rsn, string stat) {
    appointmentId = appId;
    patientId     = patId;
    doctorId      = docId;
    date          = d;
    timeSlot      = time;
    reason        = rsn;
    status        = stat;
}
bool Appointment::dateIsNotAPastDate(string date){
    int day   = stoi(date.substr(0, 2));
    int month = stoi(date.substr(3, 2));
    int year  = stoi(date.substr(6, 4));

    time_t t = time(0);
    tm* now = localtime(&t);
    int dateToday  = now->tm_mday;
    int monthToday = now->tm_mon + 1;
    int yearToday  = now->tm_year + 1900;

    if (year < yearToday)
        return false;
    else if (year == yearToday && month < monthToday)
        return false;
    else if (year == yearToday && month == monthToday && day < dateToday)
        return false;

    return true;
}
 bool Appointment:: timeIsNotPastTime(string timeStr){
        int enteredHour = stoi(timeStr.substr(0, 2));
        int enteredMin  = stoi(timeStr.substr(3, 2));
        time_t t = time(0);
        tm* now = localtime(&t);
        int hourNow    = now->tm_hour;  // 24 hour format
        int minNow     = now->tm_min;
        if (enteredHour < hourNow)
             return false;
        else if (enteredHour == hourNow && enteredMin < minNow)
             false;
        return true;
    }
bool Appointment::isValidAppointmentId(string id) {
    if (id.length() != 6)
        return false;
    if (id[0] != 'A' || id[1] != '-')
        return false;
    for (int i = 2; i < 6; i++) {
        if (!isdigit(id[i]))
            return false;
    }
    return true;
}

bool Appointment::appointmentIdAlreadyExists(string id, string filename) {
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

// Date format: DD/MM/YYYY  
bool Appointment::isValidDate(string date) {
    if (date.length() != 10)
        return false;
    if (date[2] != '/' || date[5] != '/')
        return false;
    for (int i = 0; i < 10; i++) {
        if (i == 2 || i == 5)
            continue;
        if (!isdigit(date[i]))
            return false;
    }
    int day   = stoi(date.substr(0, 2));
    int month = stoi(date.substr(3, 2));
    int year  = stoi(date.substr(6, 4));
    if (day   < 1  || day   > 31)  return false;
    if (month < 1  || month > 12)  return false;
    if (year  < 2000 || year > 2100) return false;
    
    return true;
}

// Time format: HH:MM  (24-hour)
bool Appointment::isValidTimeSlot(string time) {
    if (time.length() != 5)
        return false;
    if (time[2] != ':')
        return false;
    for (int i = 0; i < 5; i++) {
        if (i == 2) continue;
        if (!isdigit(time[i]))
            return false;
    }
    int hour   = stoi(time.substr(0, 2));
    int minute = stoi(time.substr(3, 2));
    if (hour < 0 || hour > 23)     return false;
    if (minute < 0 || minute > 59) return false;
    return true;
}

bool Appointment::isValidStatus(string status) {
    if (status == "Scheduled"  || status == "scheduled"  ||
        status == "Completed"  || status == "completed"  ||
        status == "Cancelled"  || status == "cancelled")
        return true;
    return false;
}

Appointment Appointment::Get_Valid_Appointment_Input(string filename) {
    string appId, patId, docId, d, time, rsn, stat;

    // --- Appointment ID ---
    while (true) {
        cout << "Enter Appointment ID (format: A-0001): ";
        cin  >> appId;
        if (!isValidAppointmentId(appId)) {
            cout << "Invalid Appointment ID format. Must be A-XXXX (4 digits). Try again." << endl;
        } else if (appointmentIdAlreadyExists(appId, filename)) {
            cout << "Appointment ID already exists. Try again." << endl;
        } else {
            break;
        }
    }

    // --- Patient ID ---
    while (true) {
        cout << "Enter Patient ID (format: P-0001): ";
        cin  >> patId;
        if (patId.length() > 0)
            break;
        cout << "Patient ID cannot be empty. Try again." << endl;
    }

    // --- Doctor ID ---
    while (true) {
        cout << "Enter Doctor ID (format: D-0001): ";
        cin  >> docId;
        if (docId.length() > 0)
            break;
        cout << "Doctor ID cannot be empty. Try again." << endl;
    }

    // --- Date ---
    while (true) {
        cout << "Enter Appointment Date (DD/MM/YYYY): ";
        cin  >> d;
        if (isValidDate(d))
            break;
        if (dateIsNotAPastDate(d)){
            break;
        }
        
        cout << "Invalid date format. Use DD/MM/YYYY and ensure values are in range. Date cannot be a past date." << endl;
    }
   
    // --- Time Slot ---
    while (true) {
        cout << "Enter Time Slot (HH:MM, 24-hour format): ";
        cin  >> time;
        if (isValidTimeSlot(time))
            break;
        if(timeIsNotPastTime(time))
        {
            break;
        }
        cout << "Invalid time. Use HH:MM (e.g. 09:30 or 14:00). Time slot cannot be a past time" << endl;
    }

    cin.ignore();

    // --- Reason ---
    while (true) {
        cout << "Enter Reason for Appointment: ";
        getline(cin, rsn);
        if (rsn.length() > 0)
            break;
        cout << "Reason cannot be empty. Try again." << endl;
    }

    // --- Status ---
    while (true) {
        cout << "Enter Status (Scheduled / Completed / Cancelled): ";
        getline(cin, stat);
        if (isValidStatus(stat))
            break;
        cout << "Invalid status. Enter Scheduled, Completed, or Cancelled." << endl;
    }

    return Appointment(appId, patId, docId, d, time, rsn, stat);
}


string Appointment::getAppointmentId() const { return appointmentId; }
string Appointment::getPatientId()     const { return patientId;     }
string Appointment::getDoctorId()      const { return doctorId;      }
string Appointment::getDate()          const { return date;          }
string Appointment::getTimeSlot()      const { return timeSlot;      }
string Appointment::getReason()        const { return reason;        }
string Appointment::getStatus()        const { return status;        }


void Appointment::setAppointmentId(string id)  { appointmentId = id;     }
void Appointment::setPatientId(string id)      { patientId     = id;     }
void Appointment::setDoctorId(string id)       { doctorId      = id;     }
void Appointment::setDate(string d)            { date          = d;      }
void Appointment::setTimeSlot(string time)     { timeSlot      = time;   }
void Appointment::setReason(string rsn)        { reason        = rsn;    }
void Appointment::setStatus(string stat)       { status        = stat;   }


void Appointment::displayHeader() const {
    cout << left;
    cout << setw(10) << "AppID"
         << setw(10) << "PatientID"
         << setw(10) << "DoctorID"
         << setw(14) << "Date"
         << setw(8)  << "Time"
         << setw(20) << "Reason"
         << setw(12) << "Status"
         << endl;
    cout << "------------------------------------------------------------------------" << endl;
    cout << right;
}

void Appointment::display() const {
    // Truncate long reason for console display
    string r = reason.substr(0, 18);
    if (reason.length() > 18)
        r += "..";

    cout << left;
    cout << setw(10) << appointmentId
         << setw(10) << patientId
         << setw(10) << doctorId
         << setw(14) << date
         << setw(8)  << timeSlot
         << setw(20) << r
         << setw(12) << status
         << endl;
    cout << right;
}

void Appointment::saveToFile(string filename) const {
    ofstream outfile(filename, ios::app);
    if (outfile.is_open()) {
        outfile << "-----------"   << endl;
        outfile << appointmentId   << endl;
        outfile << patientId       << endl;
        outfile << doctorId        << endl;
        outfile << date            << endl;
        outfile << timeSlot        << endl;
        outfile << reason          << endl;
        outfile << status          << endl;
        outfile.close();
    }
}

void Appointment::loadFromFile(string filename) {
    ifstream infile(filename);
    if (infile.is_open()) {
        string separator;
        getline(infile, separator);   
        getline(infile, appointmentId);
        getline(infile, patientId);
        getline(infile, doctorId);
        getline(infile, date);
        getline(infile, timeSlot);
        getline(infile, reason);
        getline(infile, status);
        infile.close();
    }
}


void Appointment::searchByAppointmentId(string filename, string id) {
    ifstream infile(filename);
    if (infile.is_open()) {
        string sep, aId, pId, dId, d, time, rsn, stat;
        while (getline(infile, sep)) {
            getline(infile, aId);
            getline(infile, pId);
            getline(infile, dId);
            getline(infile, d);
            getline(infile, time);
            getline(infile, rsn);
            getline(infile, stat);
            if (aId == id) {
                displayHeader();
                string r = rsn.substr(0, 18);
                if (rsn.length() > 18) r += "..";
                cout << left;
                cout << setw(10) << aId  << setw(10) << pId  << setw(10) << dId
                     << setw(14) << d    << setw(8)  << time << setw(20) << r
                     << setw(12) << stat << endl;
                cout << right;
                infile.close();
                return;
            }
        }
        infile.close();
        cout << "Appointment Not Found." << endl;
    }
}

void Appointment::searchByPatientId(string filename, string id) {
    bool found = false;
    ifstream infile(filename);
    if (infile.is_open()) {
        string sep, aId, pId, dId, d, time, rsn, stat;
        bool headerPrinted = false;
        while (getline(infile, sep)) {
            getline(infile, aId);
            getline(infile, pId);
            getline(infile, dId);
            getline(infile, d);
            getline(infile, time);
            getline(infile, rsn);
            getline(infile, stat);
            if (pId == id) {
                if (!headerPrinted) { displayHeader(); headerPrinted = true; }
                found = true;
                string r = rsn.substr(0, 18);
                if (rsn.length() > 18) r += "..";
                cout << left;
                cout << setw(10) << aId  << setw(10) << pId  << setw(10) << dId
                     << setw(14) << d    << setw(8)  << time << setw(20) << r
                     << setw(12) << stat << endl;
                cout << right;
            }
        }
        infile.close();
    }
    if (!found)
        cout << "No appointments found for Patient ID: " << id << endl;
}

void Appointment::searchByDoctorId(string filename, string id) {
    bool found = false;
    ifstream infile(filename);
    if (infile.is_open()) {
        string sep, aId, pId, dId, d, time, rsn, stat;
        bool headerPrinted = false;
        while (getline(infile, sep)) {
            getline(infile, aId);
            getline(infile, pId);
            getline(infile, dId);
            getline(infile, d);
            getline(infile, time);
            getline(infile, rsn);
            getline(infile, stat);
            if (dId == id) {
                if (!headerPrinted) { displayHeader(); headerPrinted = true; }
                found = true;
                string r = rsn.substr(0, 18);
                if (rsn.length() > 18) r += "..";
                cout << left;
                cout << setw(10) << aId  << setw(10) << pId  << setw(10) << dId
                     << setw(14) << d    << setw(8)  << time << setw(20) << r
                     << setw(12) << stat << endl;
                cout << right;
            }
        }
        infile.close();
    }
    if (!found)
        cout << "No appointments found for Doctor ID: " << id << endl;
}

void Appointment::searchByDate(string filename, string searchDate) {
    bool found = false;
    ifstream infile(filename);
    if (infile.is_open()) {
        string sep, aId, pId, dId, d, time, rsn, stat;
        bool headerPrinted = false;
        while (getline(infile, sep)) {
            getline(infile, aId);
            getline(infile, pId);
            getline(infile, dId);
            getline(infile, d);
            getline(infile, time);
            getline(infile, rsn);
            getline(infile, stat);
            if (d == searchDate) {
                if (!headerPrinted) { displayHeader(); headerPrinted = true; }
                found = true;
                string r = rsn.substr(0, 18);
                if (rsn.length() > 18) r += "..";
                cout << left;
                cout << setw(10) << aId  << setw(10) << pId  << setw(10) << dId
                     << setw(14) << d    << setw(8)  << time << setw(20) << r
                     << setw(12) << stat << endl;
                cout << right;
            }
        }
        infile.close();
    }
    if (!found)
        cout << "No appointments found for Date: " << searchDate << endl;
}

Appointment::~Appointment() {}
