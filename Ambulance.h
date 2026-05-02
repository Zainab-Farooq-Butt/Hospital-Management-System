#pragma once
#include<iostream>
#include<fstream>
using namespace std;
class Ambulance {
	private:
	string ambulanceId;
	bool availability;
	string driverId;
	string licensePlate;
	string address;
	public:
	Ambulance();
	Ambulance(string aId, bool avail, string dId, string plate, string location);
	bool isValidAmbulanceId(string id);
	bool isValidDriverId(string id);
	bool isValidLicensePlate(string plate);
	bool isValidAddress(string location);
	string getAmbulanceId()const;
	bool getAvailability()const;
	string getDriverId()const;
	string getLicensePlate()const;
	string getAddress()const;
	void setAmbulanceId(string id);
	void setAvailability(bool avail);
	void setDriverId(string id);
	void setLicensePlate(string plate);
	void setAddress(string address);
	void displayAmbulanceInfo();
	void saveToFile(string filename);
	void loadFromFile(ifstream& infile);
	bool ambulanceIdAlreadyExists(string id, string filename);
	void displayAllAmbulances(string filename);
};