
#pragma once
#include<iostream>
#include<fstream>
using namespace std;


class Login {
    public:
    static void Save_Login_to_File(string username, string password, string role, string cnic);
    static string authenticate(string username, string password);
};