#pragma once
#include "MedicalRecords.h"
#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;
class Room {
protected:
    string roomID;
    string roomType;
    string currentAppointment;
    string patientID;
    bool isOccupied;
    string dateAdmitted;
    string dateDischarged;
public:
    //constructors
    Room(string roomid = "", string roomtype = "", string currentappointment = "", string patientid = "", bool isoccupied = false, string dateadmitted = "", string datedischarged = "");
    ~Room();
    string To_Lower_Case(string str);
    //validations
    bool isValidID(string ID);
    bool isValidType(string Type);
    bool isValidAppointment(string Appointment);
    bool isValidpID(string pID);
    bool isValidOccupied(bool isOccupied);
    bool isValidAdmitted(string dateAdmitted);
    bool isValidDischarged(string dateDischarged, string Dateadmitted);
    //getters
    string getId()const;
    string getType()const;
    string getAppointment()const;
    string getpID()const;
    string getDateAdmitted()const;
    string getDateDischarged()const;
    //setters
    Room& setId(string roomid);
    Room& setType(string roomtype);
    Room& setAppointment(string currentappointment);
    Room& setpID(string patientid);
    Room& setOccupied(bool isoccupied);
    Room& setAdmitted(string dateadmitted);
    Room& setDischarged(string datedischarged);
    //other functions
    double fetchRoomFee(string patientid)const;
    void searchByRoomid(string file, string targetid)const;
    void showOccupiedRooms(string file); //show rooms that are occupied
    void transferPatient(string file, string newroomid); //transferring a patient to another room
    int numberOfDaysinRoom()const ; //discharged-admitted
    double roomBill(MedicalRecords& record); //connects to medicalrecords class
    //display
    void displayRoomDetails()const;
    //file handling
    void fileOutput(ofstream& file)const;
    void fileInput(ifstream& myfile);

    bool displayAvailableRoomsByType(string type);
    bool Check_occupied_by_roomID(string roomid,string roomtype);
    void updatePatientID(string targetRoomID, string newPatientID);
    void updateOccupancy(string targetRoomID, bool newStatus);
    void updateDateAdmitted(string targetRoomID, string newDate);
};