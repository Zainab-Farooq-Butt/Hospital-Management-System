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
    Person();
    Person(string cnic,string name,int age,string gender,string phone,string email,string address);
    bool Is_Valid_CNIC_Format(string cnic);
    bool CNIC_Already_Exists(string cnic,string filename);
    bool Is_Valid_Age(int age);
    bool Is_Valid_Phone(string phone);
    bool Is_Valid_Email(string email);
    Person Get_Valid_Person_Input(string filename);
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
    virtual void Display_Info();
    virtual void Save_To_File(ofstream& outfile);
    virtual void Load_From_File(ifstream& infile);
    virtual string Get_Role();
    virtual ~Person();
};