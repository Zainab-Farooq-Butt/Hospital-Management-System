#include"Person.h"

Person::Person(){
    CNIC="";
    Name="";
    Age=-1;
    Gender="";
    Phone_Num="";
    Email="";
    Address="";
}
Person::Person(string cnic,string name,int age,string gender,string phone,string email,string address){
    CNIC=cnic;
    Name=name;
    Age=age;
    Gender=gender;
    Phone_Num=phone;
    Email=email;
    Address=address;

}
bool Person::Is_Valid_CNIC_Format(string cnic){
    if(cnic.length()!=15){
        return false;
    }
    if(cnic[5]!='-' || cnic[13]!='-'){
        return false;
    }
    for(int i=0;i<15;i++){
        if(i==5 || i==13){
            continue;
        }
        if(isdigit(cnic[i])==false){
            return false;
        }
    }
    return true;
}
bool Person::CNIC_Already_Exists(string cnic,string filename){
    ifstream infile;
    infile.open(filename,ios::in);
    if(infile.is_open()){
        string line;
        while(getline(infile,line)){
            if(line==cnic){
                infile.close();
                return true;
            }
        }
        infile.close();
        return false;
    }
    return false;
}
bool Person::Is_Valid_Age(int age){
    if(age<0 || age>120){
        return false;
    }
    return true;
}
bool Person::Is_Valid_Phone(string phone){
    if(phone.length()!=11){
        return false;
    }
    if(phone[0]!='0' || phone[1]!='3'){
        return false;
    }
    for(int i=0;i<phone.length();i++){
        if(isdigit(phone[i])==false){
            return false;
        }
    }
    return true;
}
bool Person::Is_Valid_Email(string email){
    int atPos=email.find('@');
    if(atPos==string::npos){
        return false;
    }
    int dotPos=email.find('.',atPos);
    if(dotPos==string::npos){
        return false;
    }
    return true;
}
Person Person::Get_Valid_Person_Input(string filename){
    string cnic,name,gender,phone,email,address;
    int age;
    while(true){
        cout<<"Enter CNIC (format: 42101-1234567-1): ";
        cin>>cnic;
        if(Is_Valid_CNIC_Format(cnic)==false){
            cout<<"Invalid CNIC format. Try again."<<endl;
        }else if(CNIC_Already_Exists(cnic,filename)==true){
            cout<<"This CNIC is already registered. Try again."<<endl;
        }else{
            break;
        }
    }
    cin.ignore();
    while(true){
        cout<<"Enter Name: ";
        getline(cin,name);
        if(name.length()>0){
            break;
        }
        cout<<"Name cannot be empty. Try again."<<endl;
    }
    while(true){
        cout<<"Enter Age: ";
        cin>>age;
        if(Is_Valid_Age(age)==true){
            break;
        }
        cout<<"Invalid age. Must be between 0 and 120. Try again."<<endl;
    }
    while(true){
        cout<<"Enter Gender (Male/Female): ";
        cin>>gender;
        if(gender=="Male" || gender=="Female" || gender=="male" || gender=="female" || gender=="Other" || gender=="other"){
            break;
        }
        cout<<"Invalid. Enter Male,Female or Other  only."<<endl;
    }
    while(true){
        cout<<"Enter Phone (03XXXXXXXXX): ";
        cin>>phone;
        if(Is_Valid_Phone(phone)==true){
            break;
        }
        cout<<"Invalid phone. Must be 11 digits starting with 03."<<endl;
    }
    while(true){
        cout<<"Enter Email: ";
        cin>>email;
        if(Is_Valid_Email(email)==true){
            break;
        }
        cout<<"Invalid email. Must contain @ and a dot after it."<<endl;
    }
    cin.ignore();
    while(true){
        cout<<"Enter Address: ";
        getline(cin,address);
        if(address.length()>0){
            break;
        }
        cout<<"Address cannot be empty. Try again."<<endl;
    }
    return Person(cnic,name,age,gender,phone,email,address);
}
string Person::Get_CNIC() const{
    return CNIC;
}
string Person::Get_Name() const{
    return Name;
}
int Person::Get_Age() const{
    return Age;
}
string Person::Get_Gender() const{
    return Gender;
}
string Person::Get_Phone_Num() const{
    return Phone_Num;
}
string Person::Get_Email() const{
    return Email;
}
string Person::Get_Address() const{
    return Address;
}
void Person::Set_Age(int age){
    if(Is_Valid_Age(age)==false){
        while(true){
            cout<<"Enter Age: ";
            cin>>age;
            if(Is_Valid_Age(age)==true){
                break;
            }
            cout<<"Invalid age. Must be between 0 and 120. Try again."<<endl;
        }
        Age=age;
    }
    else{
        Age=age;
    }
}
void Person::Set_Phone_Num(string phone){
    if(Is_Valid_Phone(phone)==false){
        while(true){
            cout<<"Enter Phone (03XXXXXXXXX): ";
            cin>>phone;
            if(Is_Valid_Phone(phone)==true){
                break;
            }
            cout<<"Invalid phone. Must be 11 digits starting with 03."<<endl;
        }
        Phone_Num=phone;
    }
    else{
        Phone_Num=phone;
    }
}
void Person::Set_Email(string email){
    if(Is_Valid_Email(email)==false){
        while(true){
            cout<<"Enter Email: ";
            cin>>email;
            if(Is_Valid_Email(email)==true){
                break;
            }
            cout<<"Invalid email. Must contain @ and a dot after it."<<endl;
        }
        Email=email;
    }
    else{
        Email=email;
    }
}
void Person::Set_Address(string address){
    if(address.length()<=0){
        while(true){
            cout<<"Enter Address: ";
            getline(cin,address);
            if(address.length()>0){
                break;
            }
            cout<<"Address cannot be empty. Try again."<<endl;
        }
        Address=address;
    }
    else{
        Address=address;
    }
}
void Person::Display_Info() const{
    cout<<"CNIC: "<<CNIC<<endl;
    cout<<"Name: "<<Name<<endl;
    cout<<"Age: "<<Age<<endl;
    cout<<"Gender: "<<Gender<<endl;
    cout<<"Phone Number: "<<Phone_Num<<endl;
    cout<<"Email: "<<Email<<endl;
    cout<<"Address: "<<Address<<endl;
}
void Person::Save_To_File(ofstream& outfile){
    if(outfile.is_open()){
        outfile<<"----------"<<endl;
        outfile<<CNIC<<endl;
        outfile<<Name<<endl;
        outfile<<Age<<endl;
        outfile<<Gender<<endl;
        outfile<<Phone_Num<<endl;
        outfile<<Email<<endl;
        outfile<<Address<<endl;
    }
}
void Person::Load_From_File(ifstream& infile){
    if(infile.is_open()){
        getline(infile,CNIC);
        getline(infile,Name);
        infile>>Age;
        infile.ignore();
        getline(infile,Gender);
        getline(infile,Phone_Num);
        getline(infile,Email);
        getline(infile,Address);
    }
}
//  string Person::Get_Role(){
//     return "Person";
// }

























Person::~Person(){}