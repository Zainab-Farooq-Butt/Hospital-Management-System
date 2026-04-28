#pragma once;
#include<iostream>
#include<fstream>
#include<iomanip>
#include<string>
using namespace std;
class MedicalRecords {
private:
	string recordId;
	string patientId;
	string doctorId;
	string diagnoses;
	string treatment;
	double treatmentCost;
	string date;
	static int recordCounter;
	public:
	MedicalRecords();
	MedicalRecords(string recID,string patID,string docID,string diag,string t,double tcost,string d);
	string generateRecordId()const;
	//Validations
	bool isValidRecordId(string id);
	bool recordIdAlreadyExists(string id);
	bool isLeapYear(int year) const;
	bool isValidDate(string dt);
	//Getters
	string getRecordId()const;
	string getPatientId()const;
	string getDoctorId()const;
	string getDiagnoses()const;
	string getTreatment()const;
	double getTreatmentCost()const;
	string getDate()const;
	//Setters
	void setRecordId(string id);
	void setPatientId(string id);
	void setDoctorId(string id);
	void setDiagnoses(string id);
	void setTreatment(string id);
	void setTreatmentCost(double tcost);
	void setDate(string id);
	//Display
	void displayHeader();
	void display()const;
	//----Managing Records--------
	void fetchFromFile(string id);
	//Search Functions
	void displayAllRecords();
	bool searchByRecordId(string id);
	bool searchByPatientId(string id);
	bool searchByDoctorId(string id);
	//Add/Update/Delete Records
	void setMedicalRecords(string currentUser);
	void updateRecords(string currentUser);
	void deleteRecords(string currentuser);
	//File Handling
	static void loadCounterFromFile();
	void saveToFile()const;
	void loadFromFile();
	~MedicalRecords();
};




	