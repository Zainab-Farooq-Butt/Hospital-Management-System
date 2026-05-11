#pragma once
#include <iostream>
#include "Person.h"
#include <fstream>
#include <string>
using namespace std;

class Staff : public Person {
private:
    string staffId;
    string department;
    string jobTitle;
    string shift;
    double salary;
    string joiningDate;
    string employmentStatus;
    string is_paid;
    string linkedCNIC;
    static int staffCounter;

public:

    static string To_Lower_Case(string str);

    // constructors
    Staff();
    Staff(string id, string dept, string title, string shift, double salary, string joiningDate, string status, string paid);

    //Helper
    string generateStaffId();

    // validations
    bool isValidStaffId(string id);
    bool staffIdAlreadyExists(string id, string filename);
    bool isValidDepartment(string dept);
    bool isValidJobTitle(string job);
    bool isValidShift(string shift);
    bool isValidSalary(double salary);
    bool isValidJoiningDate(string date);
    bool isValidEmploymentStatus(string status);
    bool isValidPaid(string paid);

    // getters
    string getStaffId() const;
    string getDepartment() const;
    string getJobTitle() const;
    string getShift() const;
    double getSalary() const;
    string getJoiningDate() const;
    string getEmploymentStatus() const;
    string Get_Is_Paid() const;

    // setters
    void setStaffId(string id);
    void setDepartment(string dept);
    void setJobTitle(string title);
    void setShift(string shift);
    void setSalary(double salary);
    void setJoiningDate(string date);
    void setEmploymentStatus(string status);
    void setLinkedCNIC(string cnic);
    void Set_Is_Paid(string paid);

    // file handling
    static void loadCounterFromFile(string filename);
    void Save_To_File(ofstream& outfile) const;
    void Load_From_File(ifstream& infile);
    string get_CNIC();

    // display
    void displayInfo() const;

    ~Staff();
};