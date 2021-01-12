// Created by Nikola Kirilov on 5.01.21.


#include "User.h"

User::User()
{
    setUsername("");
    setPassword("");
    setisAdmin(false);
}

User::User(string username, string password)
{
    setUsername(username);
    setPassword(password);
    setisAdmin(false);
}

User::User(string, string password, bool isAdmin)
{
    setUsername(username);
    setPassword(password);
    setisAdmin(isAdmin);
}

ofstream& User::saveUser(ofstream& os)
{
    if (os.is_open())
        {
            os << this->username << endl;
            os << this->password << endl;
        }
    else
        {
            cout << "Cannot open stream for saving user!" << endl;
        }
    return os;
}

ifstream& User::readUser(ifstream& is)
{
    if (is.is_open())
        {
            is >> this->username;
            is >> this->password;
        }
    return is;

}

string User::getUsername()const
{
    return this->username;
}

string User::getPassword()const
{
    return this->password;
}

bool User::getisAdmin()const
{
    return this->isAdmin;
}

void User::setUsername(string username)
{
    this->username = username;
}

void User::setPassword(string password)
{
    this->password = password;
}
void User::setisAdmin(bool isAdmin)
{
    this->isAdmin = isAdmin;
}

