#pragma once
#include <iostream>
#include <cstring>
#include <fstream>
//Lichni failove on OOP
using namespace std;

class User
{
private:
    char username[256];
    char password[256];
    bool isAdmin;

public:
    User();

    User(const char *username, const char *password);

    User(const char *username, const char *password, bool isAdmin);

    ofstream &saveUser(ofstream &os);

    ifstream &readUser(ifstream &is);

public:
    //Setters
    void setUsername(const char *userame);

    void setPassword(const char *password);

    void setisAdmin(bool isAdmin);

    //Getters
    const char *getUsername() const;

    const char *getPassword() const;

    bool getisAdmin() const;


};

