#include <iostream>
#include"Graph.h"
#include"Edge.h"
#include <string>
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
    //cout<<map.isWay("C", "A");
    cout<<endl;
    //cout<<map.isRouteToEverySingleVertex("A");
    cout<<endl;
   // map.printAllFinals();
    cout<<"Hello world\n";
    cout<<endl;

    char username[256];
    char password[256];
    string command;
    string choice;
    bool isUser = false;
    bool isAdmin = false;
    bool isOpen = false;
    Usermass users;
    Usermass defaults;
    vector<string> cityNames;
    cityNames.emplace_back("sofia");
    cityNames.emplace_back("pernik");
    cityNames.emplace_back("burgas");


    //Default testing...
    //users.AddUser(nikola);
    //User nikola("nikola", "nikola123");
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



    while (command != "exit" )
        {
            cin>>command;
            lowerString(command);
            if (command == "help")
                {
                    cout<<"The supported commands are: "<<endl;
                    cout<<"'login', logs you in the system, without it you will not be able to operate!"<<endl;
                    cout<<"'logout', logs you out of the system current User"<<endl;
                    cout<<"'location', reveals your current location on the map"<<endl;
                    cout<<"'change', changes the current location on the map"<<endl;
                    cout<<"'open', opens the current intersection"<<endl;
                    cout<<"'close', closes the current intersection"<<endl;
                    cout<<"'way', cheks for way between two points"<<endl;
                }
            else if (command == "login" && isOpen)
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

            else if (command == "logout" && isUser)
                {
                    isUser = false;
                    isAdmin = false;
                    cout << "Logout successfull! See ya'! " << endl;
                }
            else if (command == "logout"&& !isUser)
                {
                    cout << "You need to be logged into the system to operate!" << endl;
                }


            else if ((command == "users add" == 0) && isAdmin)
                {
                    cout << "Enter the username: " << endl;
                    cin >> username;
                    cout << "Enter the password: " << endl;
                    cin >> password;
                    if (!users.checkforUser(username))
                        {
                            User user1(username, password);
                            users.AddUser(user1);
                            cout << "Successful!" << endl;
                        } else
                        {
                            cout << "The user already exists" << endl;
                        }


                }
            else if (command == "users add" && !isAdmin)
                {
                    cout << "No such permissions, you are not admin!" << endl;
                }


            else if (command == "users remove" && isAdmin)
                {
                    cout << "Enter the username to be deleted: " << endl;
                    cin >> username;
                    users.RemoveUser(username);

                }
            else if (command == "users remove" && !isAdmin)
                {
                    cout << "No such permissions, you are not admin!" << endl;
                }

            else if (command == "location" && isUser)
                {
                    cout<<"The current location is: "<<map.searchTheList(map.getLocation())<<endl;
                }
            else if (command == "location" && !isUser)
                {
                    cout<<"You need to login first!"<<endl;
                }


            else if (command == "change" && isUser)
                {
                    string inp;
                    cout<<"Where you want to move on?"<<endl;
                    cin >> inp;
                    map.moveOn(inp);

                }
            else if (command == "change" && !isUser)
                {
                    cout<<"You need to login first!"<<endl;
                }


            else if (command == "neighbours" && isUser)
                {
                    cout<<"The neighbours are:";
                    map.findNeighbours();
                }
            else if (command == "neighbours" && !isUser)
                {
                    cout<<"You need to login first!"<<endl;
                }


            else if (command == "open" && isUser)
                {
                    map.open();
                 }
            else if (command == "open" && !isUser)
                {
                    cout<<"You need to login first"<<endl;
                }

            else if (command == "close" && isUser)
                {
                    map.close();
                }
            else if (command == "close" && !isUser)
                {
                   cout<<"You need to login first"<<endl;
                }

            else if (command == "way" && isUser)
                {
                    string inp1, inp2;
                    cout<<"Enter the start point"<<endl;
                    cin>>inp1;
                    cout<<"Enter the end point"<<endl;
                    cin>>inp2;
                    bool check = map.isConnectionBtwTwo(map.returnStarttoInt(inp1), map.returnEndtoInt(inp2));
                    if(check)
                        {
                            cout<<"There is a way between: "<<inp1<<" and "<<inp2<<"!"<<endl;
                        }
                    else
                        {
                            cout<<"There is no way :("<<endl;
                        }
                }
           else if (command == "way" && !isUser)
                {
                    cout<<"You need to login first"<<endl;
                }
           else
                {
                    cout<<"Invalid command"<<endl;
                }


        }
        cout<<"Exiting the program..."<<endl;
        cout<<"Good bye, see ya! :)"<<endl;
    ofstream Usersoutput("Users.txt");
    users.saveUsers(Usersoutput);

    Usersoutput.close();
    Usersinput.close();
    users.saveUsers(Usersoutput);


}

