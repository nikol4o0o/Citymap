#pragma once
#include <iostream>
#include <cstring>
#include <fstream>
//Lichni failove on OOP
using namespace std;

class User
{
private:
    string username;
    string password;
    bool isAdmin;

public:
    User();

    User(string username, string password);

    User(string username, string password, bool isAdmin);

    ofstream &saveUser(ofstream &os);

    ifstream &readUser(ifstream &is);

public:
    //Setters
    void setUsername(string userame);

    void setPassword(string password);

    void setisAdmin(bool isAdmin);

    //Getters
    string getUsername() const;

    string getPassword() const;

    bool getisAdmin() const;


};

