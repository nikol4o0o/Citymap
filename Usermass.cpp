#include "Usermass.h"

void Usermass::erase()
{
    delete[] this->users;
}

void Usermass::copy(const Usermass& other)
{
    this->size = other.size;
    this->capacity = other.capacity;
    this->users = new User[this->capacity];

    for (int i = 0; i < this->size; i++)
        {
            this->users[i] = other.users[i];
        }
}

void Usermass::resize()
{
    this->capacity *= 2;
    User* temp = new User[this->capacity];
    for (int i = 0; i < this->size; i++)
        {
            temp[i] = this->users[i];
        }
    this->erase();
    this->users = temp;
}


Usermass::Usermass()
{
    this->size = 0;
    this->capacity = 16;
    this->users = new User[this->capacity];
}

Usermass::Usermass(const Usermass& other)
{
    this->copy(other);
}

Usermass& Usermass::operator=(const Usermass& other)
{
    if (this != &other)
        {
            this->erase();
            this->copy(other);
        }
    return *this;
}

User& Usermass::operator[](int i)const
{
    if (i >= 0)
        {
            return users[i];
        }
    else
        {
            std::cerr << "No such boundary" << std::endl;
        }
}

Usermass& Usermass::AddUser(const User& newUser)
{
    if (this->size >= this->capacity)
        {
            this->resize();
        }
    this->users[size++] = newUser;
    return *this;
}

Usermass& Usermass::RemoveUser(std::string username)
{
    bool flag = false;
    if (size > 0)
        {
            for (int i = 0; i < this->size; i++)
                {
                    if (username == users[i].getUsername())
                        {
                            for (int j = i; j < this->size - 1; j++)
                                users[j] = users[j + 1];
                            flag = true;
                        }
                }
            size--;
        }
    if (flag == false)
        {
            std::cout << "There is no such user!" << std::endl;
        }
    else
        {
            std::cout << "Successfull!" << std::endl;
        }

    return *this;
}

std::ofstream& Usermass::saveUsers(std::ofstream& out)
{
    if (out.is_open())
        {
            out << this->size << std::endl;
            for (int i = 0; i < this->size; i++)
                {
                    this->users[i].saveUser(out);
                }
        }
    return out;
}

std::ifstream& Usermass::readUsers(std::ifstream& in)
{
    int size = 0;
    in >> size;
    for (int i = 0; i < size; i++)
        {
            User user;
            user.readUser(in);
            this->AddUser(user);
        }
    return in;
}

int Usermass::getSize()const
{
    return this->size;
}

bool Usermass::checkforUser(std::string username)
{
    bool flag = false;
    for (int i = 0; i < this->size; i++)
        {
            if (users[i].getUsername() == username)
                {
                    return true;
                }
        }
    return false;
}

Usermass::~Usermass()
{
    this->erase();
}

