#pragma once
#include "Person.h"
#include <iostream>
#include <fstream>
using namespace std;

class Doctor : public Person {
private:
    string doctorId;
    string specialization;
    string qualification;
    int    experienceYears;
    double consultationFee;
    string availability;       // e.g. "Mon-Fri 9AM-5PM"
    string availabilityStatus; // "Available" / "Unavailable" / "On Leave"

public:
    // ── Constructors ────────────────────────────────────────────────────────
    Doctor();
    Doctor(string id, string spec, string qual, int exp, double fee,
           string avail, string status);

    // ── Validators ──────────────────────────────────────────────────────────
    static bool isValidDoctorId(string id);
    static bool doctorIdAlreadyExists(string id, string filename);
    static bool isValidSpecialization(string spec);
    static bool isValidExperience(int exp);
    static bool isValidFee(double fee);
    static bool isValidAvailability(string avail);
    static bool isValidAvailabilityStatus(string status);

    // ── Input helper ────────────────────────────────────────────────────────
    static Doctor Get_Valid_Doctor_Input(string filename);

    // ── Fee lookup ──────────────────────────────────────────────────────────
    // Searches filename for doctorId and returns its fee; -1.0 if not found.
    static double fetchDoctorFee(string doctorId, string filename);

    // ── Getters ─────────────────────────────────────────────────────────────
    string getDoctorId()           const;
    string getSpecialization()     const;
    string getQualification()      const;
    int    getExperienceYears()    const;
    double getConsultationFee()    const;
    string getAvailability()       const;
    string getAvailabilityStatus() const;

    // ── Setters ─────────────────────────────────────────────────────────────
    void setDoctorId(string id);
    void setSpecialization(string spec);
    void setQualification(string qual);
    void setExperienceYears(int exp);
    void setConsultationFee(double fee);
    void setAvailability(string avail);
    void setAvailabilityStatus(string status);

    // ── Overrides from Person ────────────────────────────────────────────────
    void   Display_Info()              override;
    void   Save_To_File(ofstream& outfile)  override;
    void   Load_From_File(ifstream& infile) override;
    string Get_Role()                  override;

    // ── Destructor ───────────────────────────────────────────────────────────
    ~Doctor();
};
