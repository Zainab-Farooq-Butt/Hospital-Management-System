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
	//Validations
	bool isValidRecordId(string id);
	bool recordIdAlreadyExists(string id,string filename);
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
	//Search Functions
	void displayAllRecords(string filename);
	bool searchByRecordId(string id, string filename);
	bool searchByPatientId(string id, string filename);
	bool searchByDoctorId(string id, string filename);
	//Add/Update/Delete Records
	void setMedicalRecords(Person* currentUser, string filename);
	void updateRecords(Person* currentUser, string filename);
	void deleteRecords(Person* currentuser, string filename);
	//File Handling
	static void loadCounterFromFile(string filename);
	void saveToFile(string filename)const;
	void loadFromFile(string filename);
	~MedicalRecords();
};




	