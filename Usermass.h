#pragma once
#include "User.h"
//Lichni failove ot OOP
using namespace std;

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
    Usermass& RemoveUser(string username);
    ofstream& saveUsers(ofstream& out);
    ifstream& readUsers(ifstream& in);
    bool checkforUser(string username);
    int getSize()const;
};

