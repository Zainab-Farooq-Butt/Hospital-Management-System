Hospital Management System — OOP Project (BS-SE 2B, Team 6)

A C++ desktop application built as part of our Object-Oriented Programming course. 
The system digitizes and automates core hospital operations across 10 modules.

Built with: C++ | Winforms (cross-platform GUI) | fstream file handling

Core OOP concepts demonstrated:
- Inheritance     : Patient, Doctor, Staff all derive from a common Person base class
- Encapsulation   : All personal and medical data is private, accessed via getters/setters
- Polymorphism    : Virtual functions (DisplayInfo, SaveToFile, GetRole) overridden per role
- Abstraction     : Each module (Billing, Pharmacy, Rooms) exposes a clean public interface
- File Handling   : Persistent storage via fstream, no external database required

Modules:
Patient Management | Doctor Management | Staff Management | Appointments
Medical Records | Billing | Pharmacy | Room & Bed Management
Ambulance & Emergency | Role-Based Access Control (RBAC)

Role-based access: Admin / Doctor / Staff / Patient each see a different dashboard
with permissions strictly scoped to their role.

Team: Zainab Farooq (Lead) · Aliha Saeed · Zuha Shahzad · M. Mueez Ashfaq · Shauzab Mukhtar
Institution: FAST NUCES Lahore · Semester 2 · 2026
