#pragma once
#include<iostream>
#include "Person.h"
#include<fstream>
#include<string>
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
    string linkedCNIC;
	static int patientCounter;
	/*string admissionDate;
	string dischargeDate;*/
public:
	//constructors
	Patient();
	Patient(string cnic,string id, string blood, string type, double Height, double Weight, string contact, string status);
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
	string Get_Role() override;
	//setters
	void setPatientId(string id);
	void setBloodGroup(string blood);
	void setPatientType(string type);
	void setHeight(double h);
	void setWeight(double w);
	void setEmergencyContact(string contact);
	void setPatientStatus(string status);
	void setLinkedCNIC(string cnic);
	//file handling
	string generatePatientId();
	static void loadCounterFromFile(string filename);
	string getNameById(string patId);
	void Save_To_File(ofstream& outfile)const;
	void Load_From_File(ifstream& infile) override;
	string get_CNIC();

	void displayInfo() const ;


	~Patient();




};