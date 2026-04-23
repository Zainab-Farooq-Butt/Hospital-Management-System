#pragma once;
#include<iostream>
#include<fstream>
#include<iomanip>
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
	public:
		static int recordCounter;
	MedicalRecords();
	MedicalRecords(string recID,string patID,string docID,string diag,string t,double tcost,string d);
	string generateRecordId()const;
	bool isValidRecordId(string id);
	bool recordIdAlreadyExists(string filename, string id);
	bool isLeapYear(int year) const;
	bool isValidDate(string dt);
	void setMedicalRecords(Person* currentUser);
	//Getters
	string getRecordId()const;
	string getPatientId()const;
	string getDoctorId()const;
	string getDiagnoses()const;
	string getTreatment()const;
	string getTreatmentCost()const;
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
	//File Handling
	static void loadCounterFromFile(string filename);
	void saveToFile(string filename)const;
	void loadFromFile(string filename);
	//Search Functions
	void searchByRecordId(string filename, string id);
	void searchByPatientId(string filename, string id);
	void searchByDoctorId(string filename, string id);
	//Update/Delete Records
	void updateRecords();
	void deleteRecords();
	~MedicalRecords();
};



	