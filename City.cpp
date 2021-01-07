#include <iostream>
#include"Graph.h"
#include"Edge.h"
#include <string>
#include <fstream>
#include <algorithm>
#include <vector>
#include "User.h"
#include "Usermass.h"



using namespace std;

void lowerString(std::string& str)
{
    std::transform(str.begin(), str.end(),str.begin(), ::tolower);
}

bool checkforName(const std::string cityName, std::vector<string> cityNames)
{
    int size = cityNames.size();
    for(int i = 0; i < size; i++)
        {
            if(cityNames[i] == cityName)
                {
                    return true;
                }
        }
        return false;
}

int main()
{
    Graph map;
     //ofstream output("input.txt");

     map.readFromFile("input.txt");
     cout<<map.isWay("C", "A");
     cout<<endl;
     //cout<<map.isRouteToEverySingleVertex("A");
     cout<<endl;
     map.printAllFinals();
     cout<<"Hello world\n";
     cout<<endl;

    char username[256];
    char password[256];
    char command[32];
    string choice;
    bool isUser = false;
    bool isAdmin = false;
    bool isOpen = false;
    Usermass users;
    Usermass defaults;
    //User nikola("nikola", "nikola123");
    vector<string> cityNames;
    cityNames.push_back("sofia");
    cityNames.push_back("pernik");
    cityNames.push_back("burgas");


    //Default testing...
    //users.AddUser(nikola);
    ifstream Usersinput("Users.txt");
    users.readUsers(Usersinput);
    cout<<users.getSize()<<endl;

//Initial check, if missing you cannot start the app!
    while(!isOpen)
    {
        printf("You need to choose which city you want to visit : Sofia/Burgas/Pernik");
        cin >> choice;
        lowerString(choice);
        bool result = checkforName(choice, cityNames);
        if(result)
            {
                cout<<"Successfully loaded file from directory...\n";
                cout<<"If you are new you can just type 'help' now...\n";
                isOpen = true;
            }
    }



    while (strcmp(command, "exit") != 0)
    {
            if (strcmp(command, "help") == 0)
                {

                }
            if ((strcmp(command, "login") == 0) && isOpen)
                {
                    cout << "Enter username: " << endl;
                    cin >> username;
                    cout << "Enter password" << endl;
                    cin>>password;

                    if (((strcmp(username, "admin") == 0) && ((strcmp(password, "i<3c++") == 0))))
                        {
                            isUser = true;
                            isAdmin = true;
                            cout << "Welcome, Admin!" << endl;

                        }
                        else
                        {
                            bool flag1 = false;
                            for (int i = 0; i < users.getSize(); i++)
                                {
                                    if (((strcmp(username, users[i].getUsername()) == 0) &&
                                         ((strcmp(password, users[i].getPassword()) == 0))))
                                        {
                                            isUser = true;
                                            cout << "Welcome" << ", " << username << endl;
                                            flag1 = true;
                                        }
                                }
                            if (!flag1)
                                {
                                    cout << "No such user, contact admin! " << endl;
                                }
                        }


                }

            if (strcmp(command, "logout") == 0 && isUser)
                {
                    isUser = false;
                    isAdmin = false;
                    cout << "Logout successfull! See ya'! " << endl;
                }
            if ((strcmp(command, "logout") == 0 && (!isUser)))
                {
                    cout << "You need to login to continue!" << endl;
                }


            if ((strcmp(command, "users add") == 0) && isAdmin)
                {
                    cout << "Enter the username: " << endl;
                    cin >> username;
                    cout << "Enter the password: " << endl;
                    cin >> password;
                    if (!users.checkforUser(username))
                        {
                            User user1(username, password);
                            users.AddUser(user1);
                            cout << "Successfull!" << endl;
                        } else
                        {
                            cout << "The user already exists" << endl;
                        }


                }
            if ((strcmp(command, "users add") == 0) && !isAdmin)
                {
                    cout << "No such permissions, you are not admin!" << endl;
                }


            if ((strcmp(command, "users remove") == 0) && isAdmin)
                {
                    cout << "Enter the username to be deleted: " << endl;
                    cin >> username;
                    users.RemoveUser(username);

                }
            if ((strcmp(command, "users remove") == 0) && !isAdmin)
                {
                    cout << "No such permissions, you are not admin!" << endl;
                }

            if (strcmp(command, "location") == 0 && isUser)
                {
                    cout<<"The current location is: "<<map.searchTheList(map.getLocation());
                }
            if (strcmp(command, "location") == 0 && !isUser)
                {
                    cout<<"You need to login first!"<<endl;
                }


            if (strcmp(command, "change") == 0 && isUser)
                {
                    string inp;
                    cout<<"Where you want to move on?"<<endl;
                    cin >> inp;
                    map.moveOn(inp);

                }






            cin.getline(command, 31);

    }
    ofstream Usersoutput("Users.txt");
    users.saveUsers(Usersoutput);

    Usersoutput.close();
    Usersinput.close();
    users.saveUsers(Usersoutput);


}

