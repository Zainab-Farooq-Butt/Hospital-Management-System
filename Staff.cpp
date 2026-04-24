#include "Staff.h"

string Staff::To_Lower_Case(string str){
    for (int i = 0; i < str.length(); i++)
    str[i] = tolower(str[i]);   
    return str;
}

Staff::Staff() : staffId(""), department(""), jobTitle(""), shift(""), salary(0), joiningDate(""), employmentStatus(""), is_paid("Unpaid"), linkedCNIC("") {}

Staff::Staff(string id, string dept, string title, string sh, double sal, string date, string status, string paid)
    : staffId(id), department(dept), jobTitle(title), shift(sh), salary(sal), joiningDate(date), employmentStatus(status), is_paid(paid), linkedCNIC("") {}

// --- Validations ---

bool Staff::isValidStaffId(string id) {
    // format S-0001
    if (id.length() != 6) return false;
    if (id[0] != 'S' || id[1] != '-') return false;
    for (int i = 2; i < 6; i++)
        if (!isdigit(id[i])) return false;
    return true;
}

bool Staff::staffIdAlreadyExists(string id, string filename) {
    ifstream fin(filename);
    string line;
    while (getline(fin, line))
        if (line == id) return true;
    return false;
}

bool Staff::isValidDepartment(string dept) {
    return (To_Lower_Case(dept) == "hr" || To_Lower_Case(dept) == "it" || To_Lower_Case(dept) == "pharmacy" ||
    To_Lower_Case(dept) == "radiology" || To_Lower_Case(dept) == "laboratory" || To_Lower_Case(dept) == "administration");
}

bool Staff::isValidJobTitle(string job){
    if(job.length()<=0){
        return false;
    }
    return true;
}

bool Staff::isValidShift(string sh) {
    return (To_Lower_Case(sh) == "morning" || To_Lower_Case(sh) == "evening" || To_Lower_Case(sh) == "night");
}

bool Staff::isValidSalary(double sal) {
    return sal > 0 && sal <= 1000000;
}

bool Staff::isValidJoiningDate(string date){

        if (date.length() != 10) return false;

        // check slashes are in right positions
        if (date[2] != '/' || date[5] != '/') return false;
    
        // check all other characters are digits
        for (int i = 0; i < 10; i++) {
            if (i == 2 || i == 5) continue;
            if (!isdigit(date[i])) return false;
        }
    
        // extract day, month, year
        int day   = stoi(date.substr(0, 2));
        int month = stoi(date.substr(3, 2));
        int year  = stoi(date.substr(6, 4));
    
        // validate ranges
        if (month < 1 || month > 12) return false;
        if (day < 1 || day > 31)     return false;
        if (year < 1900 || year > 2025) return false;
    
        // months with 30 days
        if (month == 4 || month == 6 || month == 9 || month == 11)
            if (day > 30) return false;
    
        // february
        bool leapYear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
        if (month == 2) {
            if (leapYear  && day > 29) return false;
            if (!leapYear && day > 28) return false;
        }
    
        return true;
}

bool Staff::isValidEmploymentStatus(string status) {
    return (To_Lower_Case(status) == "active" || To_Lower_Case(status) == "on leave" || To_Lower_Case(status) == "terminated");
}

bool Staff::isValidPaid(string paid){
    return (To_Lower_Case(paid)=="paid" || To_Lower_Case(paid)=="unpaid");
}

// --- Getters ---

string Staff::getStaffId() const { 
    return staffId; 
}
string Staff::getDepartment() const { return department; }
string Staff::getJobTitle() const { return jobTitle; }
string Staff::getShift() const { return shift; }
double Staff::getSalary() const { return salary; }
string Staff::getJoiningDate() const { return joiningDate; }
string Staff::getEmploymentStatus() const { return employmentStatus; }
string Staff::Get_Is_Paid() const{
    return is_paid;
}

// --- Setters ---

void Staff::setStaffId(string id) { staffId = id; }
void Staff::setDepartment(string dept) { department = dept; }
void Staff::setJobTitle(string title) { jobTitle = title; }
void Staff::setShift(string sh) { shift = sh; }
void Staff::setSalary(double sal) { salary = sal; }
void Staff::setJoiningDate(string date) { joiningDate = date; }
void Staff::setEmploymentStatus(string status) { employmentStatus = status; }
void Staff::setLinkedCNIC(string cnic) { linkedCNIC = cnic; }
void Staff::Set_Is_Paid(string paid){
    is_paid=paid;
}
string Staff::get_CNIC() { return linkedCNIC; }

// --- File Handling ---

void Staff::Save_To_File(ofstream& outfile) const {
    outfile << "----------\n";
    outfile << linkedCNIC      << "\n";
    outfile << staffId         << "\n";
    outfile << department      << "\n";
    outfile << jobTitle        << "\n";
    outfile << shift           << "\n";
    outfile << salary          << "\n";
    outfile << joiningDate     << "\n";
    outfile << employmentStatus << "\n";
    outfile << is_paid << "\n";
}

void Staff::Load_From_File(ifstream& infile) {
    getline(infile, linkedCNIC);
    getline(infile, staffId);
    getline(infile, department);
    getline(infile, jobTitle);
    getline(infile, shift);
    string salStr;
    getline(infile, salStr);
    salary = stod(salStr);
    getline(infile, joiningDate);
    getline(infile, employmentStatus);
    getline(infile, is_paid);
    
}

// --- Display ---

void Staff::displayInfo() const {
    cout << "Staff ID:   " << staffId           << "\n";
    cout << "Department: " << department        << "\n";
    cout << "Job Title:  " << jobTitle          << "\n";
    cout << "Shift:      " << shift             << "\n";
    cout << "Salary:     " << salary            << "\n";
    cout << "Joined:     " << joiningDate       << "\n";
    cout << "Status:     " << employmentStatus  << "\n";
    cout << "Is Paid:    " << is_paid           << "\n";
}

Staff::~Staff() {}