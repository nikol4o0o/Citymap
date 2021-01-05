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
		cerr << "No such boundary" << endl;
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

Usermass& Usermass::RemoveUser(const char* username)
{
	bool flag = false;
	if (size > 0)
	{
		for (int i = 0; i < this->size; i++)
		{
			if (strcmp(username, users[i].getUsername()) == 0)
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
		cout << "There is no such user!" << endl;
	}
	else
	{
		cout << "Successfull!" << endl;
	}

	return *this;
}

ofstream& Usermass::saveUsers(ofstream& out)
{
	if (out.is_open())
	{
		out << this->size << endl;
		for (int i = 0; i < this->size; i++)
		{
			this->users[i].saveUser(out);
		}
	}
	return out;
}

ifstream& Usermass::readUsers(ifstream& in)
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

bool Usermass::checkforUser(const char* username, const char* password)
{
	bool flag = false;
	for (int i = 0; i < this->size; i++)
	{
		if ((strcmp(users[i].getUsername(), username) == 0) && (strcmp(users[i].getPassword(), password) == 0))
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