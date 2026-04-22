#pragma once
#include<iostream>
#include "Person.h"
#include<fstream>
using namespace std;

class Patient :public Person {
private:
	string patientId;
	string bloodGroup;
	string patientType;
	double height;
	double weight;
	string emergencyContact;
	string patientStatus;
	/*string admissionDate;
	string dischargeDate;*/
public:
	//constructors
	Patient();
	Patient(string id, string blood, string type, double Height, double Weight, string contact, string status);
	//validations
	bool isValidPatientId(string id);
	bool patientIdAlreadyExists(string id,string filename);
	bool isValidBloodGroup (string bloodGroup);
	bool isValidPatientType(string patientType);
	bool isValidHeight(double h);
	bool isValidWeight(double w);
	bool isValidContact(string contact);
	bool isValidStatus(string status);
	//getters
	string getPatientId()const;
	string getBloodGroup() const;
	string getPatientType()const;
	double getHeight()const;
	double getWeight()const;
	string getEmergencyContact()const;
	string getPatientStatus()const;
	string Patient::getRole();
	//setters
	void setPatientId(string id);
	void setBloodGroup(string blood);
	void setPatientType(string type);
	void setHeight(double h);
	void setWeight(double w);
	void setEmergencyContact(string contact);
	void setPatientStatus(string status);
	//file handling
	void Save_To_File(ofstream& outfile)const;
	void Load_From_File(ifstream& infile);

	void displayInfo() const ;


	~Patient();




};