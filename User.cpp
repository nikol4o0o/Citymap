// Created by Nikola Kirilov on 5.01.21.


#include "User.h"

User::User()
{
    setUsername("");
    setPassword("");
    setisAdmin(false);
}

User::User(std::string username, std::string password)
{
    setUsername(username);
    setPassword(password);
    setisAdmin(false);
}

User::User(std::string, std::string password, bool isAdmin)
{
    setUsername(username);
    setPassword(password);
    setisAdmin(isAdmin);
}

std::ofstream& User::saveUser(std::ofstream& os)
{
    if (os.is_open())
        {
            os << this->username << std::endl;
            os << this->password << std::endl;
        }
    else
        {
            std::cout << "Cannot open stream for saving user!" << std::endl;
        }
    return os;
}

std::ifstream& User::readUser(std::ifstream& is)
{
    if (is.is_open())
        {
            is >> this->username;
            is >> this->password;
        }
    return is;

}

std::string User::getUsername()const
{
    return this->username;
}

std::string User::getPassword()const
{
    return this->password;
}

bool User::getisAdmin()const
{
    return this->isAdmin;
}

void User::setUsername(std::string username)
{
    this->username = username;
}

void User::setPassword(std::string password)
{
    this->password = password;
}
void User::setisAdmin(bool isAdmin)
{
    this->isAdmin = isAdmin;
}

