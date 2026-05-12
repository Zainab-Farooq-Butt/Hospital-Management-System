#pragma once
#include<iostream>
#include<fstream>
#include<string>
using namespace std;
class Ambulance {
private:
	string ambulanceId;
	bool availability;
	string driverId;
	string licensePlate;
<<<<<<< HEAD
	string address;
=======
	string destination;
>>>>>>> origin/zainab
	static int ambulanceCounter;
public:
	//Constructors
	Ambulance();
	Ambulance(string aId, bool avail, string dId, string plate, string location);
	//IDs
	string generateAmbulanceId();
	string generateDriverId();
	//Validations
	bool licensePlateAlreadyExists(string plate, string filename);
	bool isValidAmbulanceId(string id);
	bool isValidDriverId(string id);
	bool isValidLicensePlate(string plate);
<<<<<<< HEAD
	bool isValidAddress(string location);
=======
	bool isValidDestination(string location);
>>>>>>> origin/zainab
	//Getters
	string getAmbulanceId()const;
	bool getAvailability()const;
	string getDriverId()const;
	string getLicensePlate()const;
<<<<<<< HEAD
	string getAddress()const;
=======
	string getDestination()const;
>>>>>>> origin/zainab
	//Setters
	void setAmbulanceId(string id);
	void setAvailability(bool avail);
	void setDriverId(string id);
	void setLicensePlate(string plate);
<<<<<<< HEAD
	void setAddress(string address);
=======
	void setDestination(string destination);
>>>>>>> origin/zainab
	//Display
	void displayAmbulanceInfo();
	void displayAllAmbulances(string filename);
	//File Handling
	static void loadCounterFromFile(string filename);
	void saveToFile(string filename);
	void loadFromFile(ifstream& infile);
	bool ambulanceIdAlreadyExists(string id, string filename);
	//Destructor
	~Ambulance();
};