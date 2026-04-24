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
	bool isValidAddress(string idlocation;

	string getAmbulanceId()const;
	bool getAvailability()const;
	bool getDriverId()const;
	string getLicensePlate()const;
	string getAddress()const;

	
	void setAmbulanceId(string id);
	void setAvailability(bool avail);
	string setDriverId(string id);
	string setLicensePlate(string plate);
	string setAddress(string address);

	
	void displayAmbulanceInfo();

	


};