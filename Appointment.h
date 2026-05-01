#pragma once
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

class Appointment {
private:
    string appointmentId;
    string patientId;
    string doctorId;
    string date;        // format: DD/MM/YYYY
    string timeSlot;    // format: HH:MM  (24-hr)
    string reason;
    string status;      // "Scheduled" / "Completed" / "Cancelled"
    static int appointmentCounter;

public:
    // Constructors
    Appointment();
    Appointment(string appId, string patId, string docId,
                string date, string time, string reason, string status);

    // Validations
    bool isValidAppointmentId(string id);
    bool appointmentIdAlreadyExists(string id, string filename);
    bool isValidDate(string date);
    bool isValidTimeSlot(string time);
    bool isValidStatus(string status);

    // Input helper  (schedule / add a new appointment)
    Appointment Get_Valid_Appointment_Input(string filename);

    // Getters
    string getAppointmentId() const;
    string getPatientId()     const;
    string getDoctorId()      const;
    string getDate()          const;
    string getTimeSlot()      const;
    string getReason()        const;
    string getStatus()        const;

    // Setters  (modification support)
    void setAppointmentId(string id);
    void setPatientId(string id);
    void setDoctorId(string id);
    void setDate(string date);
    void setTimeSlot(string time);
    void setReason(string reason);
    void setStatus(string status);

    // Display
    void displayHeader() const;
    void display()       const;

    // File handling
    static void loadCounterFromFile(string filename);
    void saveToFile(string filename)  const;
    void loadFromFile(string filename);

    // Search
    void searchByAppointmentId(string filename, string id);
    void searchByPatientId(string filename,     string id);
    void searchByDoctorId(string filename,      string id);
    void searchByDate(string filename,          string date);

    ~Appointment();
};
