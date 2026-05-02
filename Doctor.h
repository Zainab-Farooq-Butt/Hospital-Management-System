#pragma once
#include "Person.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Doctor : public Person {
private:
    string doctorId;
    string specialization;
    string qualification;
    int    experienceYears;
    double consultationFee;
    string availability;        // e.g. "Mon-Fri 9AM-5PM"
    string availabilityStatus;  // "Available" / "Unavailable" / "On Leave"
    string linkedCNIC;
    static int doctorCounter;

public:
    // ── Utility ─────────────────────────────────────────────────────────────
    static string To_Lower_Case(string str);

    // ── Constructors ────────────────────────────────────────────────────────
    Doctor();
    Doctor(string id, string spec, string qual, int exp, double fee,
           string avail, string status);

    // ── Validators ──────────────────────────────────────────────────────────
    bool isValidDoctorId(string id);
    bool doctorIdAlreadyExists(string id, string filename);
    bool isValidSpecialization(string spec);
    bool isValidQualification(string qual);
    bool isValidExperience(int exp, int age);   // exp + 18 must be <= age
    bool isValidFee(double fee);
    bool isValidAvailability(string avail);
    bool isValidAvailabilityStatus(string status);

    // ── Input helper ────────────────────────────────────────────────────────
    Doctor Get_Valid_Doctor_Input(string filename);

    // ── ID generation ───────────────────────────────────────────────────────
    string generateDoctorId();
    static void loadCounterFromFile(string filename);

    // ── Lookup helpers ──────────────────────────────────────────────────────
    double fetchDoctorFee(string doctorId, string filename);
    string getNameById(string docId);

    // ── Getters ─────────────────────────────────────────────────────────────
    string getDoctorId()           const;
    string getSpecialization()     const;
    string getQualification()      const;
    int    getExperienceYears()    const;
    double getConsultationFee()    const;
    string getAvailability()       const;
    string getAvailabilityStatus() const;
    string get_CNIC();

    // ── Setters ─────────────────────────────────────────────────────────────
    void setDoctorId(string id);
    void setSpecialization(string spec);
    void setQualification(string qual);
    void setExperienceYears(int exp);
    void setConsultationFee(double fee);
    void setAvailability(string avail);
    void setAvailabilityStatus(string status);
    void setLinkedCNIC(string cnic);

    // ── Overrides from Person ────────────────────────────────────────────────
    void   Display_Info();
    void   Save_To_File(ofstream& outfile)  override;
    void   Load_From_File(ifstream& infile) override;
    string Get_Role()                       override;

    // ── Destructor ───────────────────────────────────────────────────────────
    ~Doctor();
};
