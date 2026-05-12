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
    double remainingAmount;
    string status;
	string billDate;
    static int billCounter;
public:
    Billing();
    Billing(string bID,string patID, string docID,string recID, double docfee, double roomfee, double tmentcost,double remaining,string stat, string date);
    string generateBillId();
    //Validation
    bool isValidBillId(string id);
    bool billIdAlreadyExists(string id);
    bool isLeapYear(int year) const;
    bool isValidBillDate(string dt);
    static bool isDateBefore(string d1, string d2);
    //Getters
    string getBillId()const;
    string getPatientId()const;
    string getDoctorId()const;
    string getRecordId()const;
    double getDoctorFee()const;
    double getRoomFee()const;
    double getTreatmentCost()const;
    double getTotalAmount()const;
    double getRemainingAmount() const;
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
    void setRemainingAmount(double amount);
    void setStatus(string id);
    void setBillDate(string id);
    //Display Functions
    void displayHeader()const;
    void display() const;
    void displayAllBills();
    //--------Managing Records--------
    void setBilling(string currentUser,string pid);
    void updateStatus(string currentUser,string pid);
    //Search Records
    bool searchByBillId(string id);
    bool searchByPatientId(string id);
    void displayAllPatientBills();
    //File Handling
    static void loadCounterFromFile(string filename);
    void saveToFile()const;
    void loadFromFile();
    bool Patient_has_RID(string patientid,string recordid);
    bool billExistsForThisRecord(string recId);
    bool Patient_has_BID(string patientid,string billid);
    ~Billing();

};