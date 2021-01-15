#pragma once
#include "User.h"
//Lichni failove ot OOP

class Usermass
{
private:
    User* users;
    int size;
    int capacity;
private:
    void copy(const Usermass& other);
    void resize();
    void erase();
public:
    Usermass();
    Usermass(const Usermass& other);
    Usermass& operator=(const Usermass& other);
    User& operator[](int i)const;
    ~Usermass();
    Usermass& AddUser(const User& newUser);
    Usermass& RemoveUser(std::string username);
    std::ofstream& saveUsers(std::ofstream& out);
    std::ifstream& readUsers(std::ifstream& in);
    bool checkforUser(std::string username);
    int getSize()const;
};

