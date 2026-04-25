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
    void doctorMenu(string user);
    void patientMenu(string user);
    public:
        void run();
    };