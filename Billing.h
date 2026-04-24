#pragma once
#include<iostream>
#include<fstream>
#include<iomanip>
#include<string>
using namespace std;
class Billing{
private:
    string billId;
	string patientId;
	string doctorId;
    string recordId;
	double doctorFee;
	double roomFee;
	double treatmentCost;
    double totalAmount;
    string status;
	string billDate;
    static int billCounter;
public:
    Billing();
    Billing(string bID,string patID, string docID,string recID, double docfee, double roomfee, double tmentcost,string stat, string date);
    string generateBillId()const;
    //Validation
    bool isValidBillId(string id);
    bool billIdAlreadyExists(string id);
    bool isLeapYear(int year) const;
    bool isValidBillDate(string dt);
    //Getters
    string getBillId()const;
    string getPatientId()const;
    string getDoctorId()const;
    string getRecordId()const;
    double getDoctorFee()const;
    double getRoomFee()const;
    double getTreatmentCost()const;
    double getTotalAmount()const;
    string getStatus()const;
    string getBillDate()const;
    //Setters
    void setBillId(string id);
    void setPatientId(string id);
    void setDoctorId(string id);
    void setRecordId(string id);
    void setDoctorFee(double fee);
    void setRoomFee(double fee);
    void setTreatmentCost(double fee);
    void setTotalAmount();
    void setStatus(string id);
    void setBillDate(string id);
    //Display Functions
    void displayHeader()const;
    void display() const;
    void displayAllBills();
    //--------Managing Records--------
    void setBilling(string currentUser);
    void updateStatus(string currentUser);
    //Search Records
    bool searchByBillId(string id);
    bool searchByPatientId(string id);
    //File Handling
    void loadCounterFromFile();
    void saveToFile()const;
    void loadFromFile();

};