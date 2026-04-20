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
	MedicalRecords();
	MedicalRecords(string recID,string patID,string docID,string diag,string t,double tcost,string d);
	bool isValidRecordId(string id);
	bool recordIdAlreadyExists(string id, string filename);
	//Getters
	string getRecordsId()const;
	string getPatientId()const;
	string getDoctorId()const;
	string getDiagnoses()const
	string getTreatment()const;
	string getTreatmentCost()const;
	string getDate()const;
	//Setters
	void setRecordsId(string id);
	void setPatientId(string id);
	void setDoctorId(string id);
	void setDiagnoses(string id);
	void setTreatment(string id);
	void setTreatmentCost(string id);
	void setDate(string id);
	//Display
	void DisplayHeader();
	void display();
	//File Handling
	void saveToFile(string filename)const;
	void loadFromFile(string filename);
	//Search Functions
	void searchByRecordId(string filename, string id);
	void searchByPatientId(string filename, string id);
	void searchByDoctorId(string filename, string id);
};



	