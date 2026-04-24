#pragma once
#include<iostream>
#include<fstream>
#include"Login.h"
using namespace std;


class SystemController {
    private:
    Login login;
    string role;
    void showLogin();
    void adminMenu();
    void doctorMenu();
    void patientMenu();
    public:
        void run();
    };