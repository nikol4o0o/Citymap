#pragma once
#include <iostream>
#include <cstring>
#include <fstream>

class User
{
private:
    std::string username;
    std::string password;
    bool isAdmin;

public:
    User();

    User(std::string username, std::string password);

    User(std::string username, std::string password, bool isAdmin);

    std::ofstream &saveUser(std::ofstream &os);

    std::ifstream &readUser(std::ifstream &is);

public:
    //Setters
    void setUsername(std::string userame);

    void setPassword(std::string password);

    void setisAdmin(bool isAdmin);

    //Getters
    std::string getUsername() const;

    std::string getPassword() const;

    bool getisAdmin() const;


};

