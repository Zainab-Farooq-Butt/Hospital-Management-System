#include"Login.h"

void Login::Save_Login_to_File(string username, string password,string role){   
    ofstream outfile("Users.txt",ios::app);
    outfile<<"----------"<<endl;
    outfile<<username<<endl;
    outfile<<password<<endl;
    outfile<<role<<endl;
}
string Login::authenticate(string username, string password) {
    if (username.empty() || password.empty()) {
        return "NONE";
    }
    ifstream infile("Users.txt");
    string line;
    while (getline(infile, line)) {
        if (line == "----------"){
            continue;
        } 
        string u = line;          
        string p, r;
        getline(infile, p);         
        getline(infile, r);         
        if (u == username && p == password) {
            return r;            
        }
    }
    return "NONE"; 
}