#pragma once
#include<iostream>
#include<fstream>
using namespace std;

class Person{
    private:
    string CNIC;
    string Name;
    int Age;
    string Gender;
    string Phone_Num;
    string Email;
    string Address;
    public:
    static string To_Lower_Case(string str);
    Person();
    Person(string cnic,string name,int age,string gender,string phone,string email,string address);
    static bool Is_Valid_CNIC_Format(string cnic);
    static bool CNIC_Already_Exists(string cnic,string filename);
    static bool Is_Valid_Age(int age);
    static bool Is_Valid_Gender(string gender);
    static bool Is_Valid_Phone(string phone);
    static bool Is_Valid_Email(string email);
    static bool Is_Valid_Address(string address);
    static Person Get_Valid_Person_Input(string filename);
    string Get_CNIC() const;
    string Get_Name() const;
    int Get_Age() const;
    string Get_Gender() const;
    string Get_Phone_Num() const;
    string Get_Email() const;
    string Get_Address() const;
    void Set_Age(int age);
    void Set_Phone_Num(string phone);
    void Set_Email(string email);
    void Set_Address(string address);
    virtual void Display_Info() const;
    virtual void Save_To_File(ofstream& outfile);
    virtual void Load_From_File(ifstream& infile);
    virtual string Get_Role();
    void Save_Login_to_File(string username, string password, string role);
    virtual ~Person();
};