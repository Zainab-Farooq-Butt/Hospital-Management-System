#include"Login.h"

void Login::Save_Login_to_File(string username, string password, string role, string cnic) {
    ofstream outfile("Users.txt", ios::app);
    outfile << "----------" << "\n";
    outfile << cnic     << "\n";
    outfile << username << "\n";
    outfile << password << "\n";
    outfile << role     << "\n";
    outfile.close();
}
string Login::authenticate(string username, string password) {
    if (username.empty() || password.empty()) {
        return "NONE";
    }

    ifstream infile("Users.txt");
    string line;

    while (getline(infile, line)) {
        if (line != "----------") continue;

        string cnic, u, p, r;
        getline(infile, cnic);  // skip CNIC
        getline(infile, u);     // username
        getline(infile, p);     // password
        getline(infile, r);     // role

        if (u == username && p == password) {
            return r;
        }
    }
    return "NONE";
}