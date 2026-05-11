#include "RBAC.h"

bool RBAC::hasAccess(string role, string feature) {

    if (role == "ADMIN"){
        return true;
    } 

    if (role == "DOCTOR") {
        if (feature == "Appointments"){
            return true;
        } 
        if (feature == "Patient_Records"){
            return true;
        } 
    }

    if (role == "STAFF") {
        if (feature == "Inventory"){
            return true;
        } 
        if (feature == "Rooms"){
            return true;
        } 
    }

    if (role == "PATIENT") {
        if (feature == "View_Own_Record"){
            return true;
        } 
        if (feature == "Book_Appointment"){
            return true;
        } 
    }

    return false;
}