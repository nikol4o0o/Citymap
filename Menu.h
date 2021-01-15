#include <iostream>
#include"Graph.h"
#include"Edge.h"
#include <string>
#include <algorithm>
#include <vector>
#include "User.h"
#include "Usermass.h"


void lowerString(std::string& str)
{
    std::transform(str.begin(), str.end(), str.begin(), ::toupper);
}

bool checkforName(const std::string cityName, std::vector<std::string> cityNames)
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

void addTheTxt(std::string &input)
{
    input += ".txt";
}

bool checkMapWay(Graph map,bool check, std::string inp1, std::string inp2)
{
    if(check)
        {
            std::cout<<"There is a way between: "<<inp1<<" and "<<inp2<<"!"<<std::endl;
        }
    else
        {
            std::cout<<"There is no way :("<<std::endl;
        }
}

void Menu()
{
    Graph map;
    //ofstream output("input.txt");
    // map.printAllFinals();

    std::string username;
    std::string password;
    std::string command;
    std::string choice;
    bool isUser = false;
    bool isAdmin = false;
    bool isOpen = false;
    Usermass users;
    Usermass defaults;
    std::vector<std::string> cityNames;
    cityNames.emplace_back("SOFIA");
    cityNames.emplace_back("PERNIK");
    cityNames.emplace_back("BURGAS");


    //Default testing...
    //users.AddUser(nikola);
    //User nikola("nikola", "nikola123");
    std::ifstream Usersinput("Users.txt");
    users.readUsers(Usersinput);
    //cout<<users.getSize()<<endl;
    printf("Welcome to the CityMap©\n");
    printf("Nikola Kirilov Labs©\n");

//Initial check, if missing you cannot start the app!
    while(!isOpen)
        {
            printf("You need to choose which city you want to visit : Sofia/Burgas/Pernik\n");
            std::cin >> choice;
            lowerString(choice);
            bool result = checkforName(choice, cityNames);
            addTheTxt(choice);
            if(result)
                {
                    std::cout<<"Successfully loaded file from directory...\n";
                    std::cout<<"If you are new you can just type 'help' now...\n";
                    isOpen = true;
                }
            map.readFromFile(choice);

        }


    while (command != "EXIT")
        {

        getline(std::cin, command);
        lowerString(command);
            if (command == "HELP")
                {
                    std::cout<<"The supported commands are: "<<std::endl;
                    std::cout<<"'login', logs you in the system, without it you will not be able to operate!"<<std::endl;
                    std::cout<<"'logout', logs you out of the system current User"<<std::endl;
                    std::cout<<"'location', reveals your current location on the map"<<std::endl;
                    std::cout<<"'change', changes the current location on the map"<<std::endl;
                    std::cout<<"'open', opens the current intersection"<<std::endl;
                    std::cout<<"'close', closes the current intersection"<<std::endl;
                    std::cout<<"'way', checks for a way between two points"<<std::endl;
                    std::cout<<"'waytoall, checks if is there a way from a startpoint to every single vertex'"<<std::endl;
                    std::cout<<"'neighbours', shows the neighbours"<<std::endl;
                    std::cout<<"'tour', makes a tourist cycling around the town"<<std::endl;
                    std::cout<<"'closed', shows all the deadends in the city"<<std::endl;
                    std::cout<<"'three', shows the 3 smallest im meters edges to the place you want"<<std::endl;
                    std::cout<<"'printall', shows all the intersection we've read"<<std::endl;
                }
            else if (command == "LOGIN" && isOpen)
                {
                    std::cout << "Enter username: " << std::endl;
                    std::cin >> username;
                    std::cout << "Enter password" << std::endl;
                    std::cin>>password;

                    if (username == "admin" && password == "admin123")
                        {
                            isUser = true;
                            isAdmin = true;
                            std::cout << "Welcome, Admin!" << std::endl;

                        }
                    else
                        {
                            bool flag1 = false;
                            for (int i = 0; i < users.getSize(); i++)
                                {
                                    if (username == users[i].getUsername() && password ==users[i].getPassword())
                                        {
                                            isUser = true;
                                            std::cout << "Welcome" << ", " << username << std::endl;
                                            flag1 = true;
                                        }
                                }
                            if (!flag1)
                                {
                                    std::cout << "No such user, contact admin! " << std::endl;
                                }
                        }
                  

                }

            else if ((command == "LOGOUT") && isUser)
                {
                    isUser = false;
                    isAdmin = false;
                    std::cout << "Logout successfull! See ya'! " << std::endl;
                }
            else if ((command == "logout") && !isUser)
                {
                    std::cout << "You need to be logged into the system to operate!" << std::endl;
                }


            else if ((command == "USERS ADD") && isAdmin)
                {
                    std::cout << "Enter the username: " << std::endl;
                    std::cin >> username;
                    lowerString(username);
                    std::cout << "Enter the password: " << std::endl;
                    std::cin >> password;
                    lowerString(password);
                    if (!users.checkforUser(username))
                        {
                            User user1(username, password);
                            users.AddUser(user1);
                            std::cout << "Successful!" << std::endl;
                        } else
                        {
                            std::cout << "The user already exists" << std::endl;
                        }
                        

                }
            else if (command == "USERS ADD" && !isAdmin)
                {
                    std::cout << "No such permissions, you are not admin!" << std::endl;
                }


            else if (command == "USERS REMOVE" && isAdmin)
                {
                    std::cout << "Enter the username to be deleted: " << std::endl;
                    std::cin >> username;
                    users.RemoveUser(username);

                }
            else if (command == "USERS REMOVE" && !isAdmin)
                {
                    std::cout << "No such permissions, you are not admin!" << std::endl;
                }

            else if (command == "LOCATION" && isUser)
                {
                    std::cout<<"The current location is: "<<map.searchTheList(map.getLocation())<<std::endl;
                }
            else if (command == "LOCATION" && !isUser)
                {
                    std::cout<<"You need to login first!"<<std::endl;
                }


            else if (command == "CHANGE" && isUser)
                {
                    std::string input;
                    std::cout<<"Where you want to move on?"<<std::endl;
                    std::cin >> input;
                    lowerString(input);
                    map.moveOn(input);
                }
            else if (command == "CHANGE" && !isUser)
                {
                    std::cout<<"You need to login first!"<<std::endl;
                }


            else if (command == "NEIGHBOURS" && isUser)
                {
                    std::cout<<"The neighbours are:";
                    map.findNeighbours();
                }
            else if (command == "NEIGHBOURS" && !isUser)
                {
                    std::cout<<"You need to login first!"<<std::endl;
                }


            else if (command == "OPEN" && isUser)
                {
                    std::string inp1;
                    std::cout<<"Which intersection would you like to be opened?"<<std::endl;
                    std::cin>>inp1;
                    lowerString(inp1);
                    map.open(inp1);
                }
            else if (command == "OPEN" && !isUser)
                {
                    std::cout<<"You need to login first"<<std::endl;
                }

            else if (command == "CLOSE" && isUser)
                {
                    std::string inp1;
                    std::cout<<"Which intersection would you like to be closed?"<<std::endl;
                    std::cin>>inp1;
                    lowerString(inp1);
                    map.close(inp1);
                }
            else if (command == "CLOSE" && !isUser)
                {
                    std::cout<<"You need to login first"<<std::endl;
                }

            else if (command == "WAY" && isUser)
                {
                    std::string inp1, inp2;
                    std::cout<<"Enter the start point"<<std::endl;
                    std::cin>>inp1;
                    std::cout<<"Enter the end point"<<std::endl;
                    std::cin>>inp2;
                    lowerString(inp1);
                    lowerString(inp2);
                    bool check = map.isConnectionBtwTwo(map.returnStarttoInt(inp1), map.returnEndtoInt(inp2));
                    checkMapWay(map, check, inp1, inp2);
                }
            else if (command == "WAY" && !isUser)
                {
                    std::cout<<"You need to login first"<<std::endl;
                }
            else if(command == "WAYTOALL" && isUser)
                {
                    std::string input;
                    std::cout<<"Enter the intersection"<<std::endl;
                    std::cin>>input;
                    lowerString(input);
                    map.waytoAll(input);
                }

            else if(command == "WAYTOALL" && !isUser)
                {
                    std::cout<<"You need to login first"<<std::endl;
                }

            else if(command == "TOUR" && isUser)
                {
                   map.tour();
                }
            else if(command == "TOUR" && !isUser)
                {
                    std::cout<<"You need to login first"<<std::endl;
                }
            else if(command == "CLOSED" && isUser)
                {
                    map.printAllFinals();
                }
            else if(command == "CLOSED" && !isUser)
                {
                    std::cout<<"You need to login first"<<std::endl;
                }
            else if (command == "MOVE" && isUser)
                {
                    std::string inp4;
                    std::cout<<"Enter the location you want to move on"<<std::endl;
                    std::cin>>inp4;
                    lowerString(inp4);
                    map.move(inp4);
                }
            else if(command == "MOVE" && !isUser)
                {
                    std::cout<<"You need to login first"<<std::endl;
                }
            else if (command == "THREE" && isUser)
                {
                    std::string inp4;
                    std::cout<<"Enter the location you want"<<std::endl;
                    std::cin>>inp4;
                    lowerString(inp4);
                    map.three(inp4);
                }
            else if(command == "THREE" && !isUser)
                {
                    std::cout<<"You need to login first"<<std::endl;
                }
            else if (command == "PRINTALL" && isUser)
                {
                    map.coutAlltheVertexes();
                }
            else if(command == "PRINTALL" && !isUser)
                {
                    std::cout<<"You need to login first"<<std::endl;
                }



        }
    std::cout<<"Exiting the program..."<<std::endl;
    std::cout<<"Good bye, see ya! :)"<<std::endl;
    std::ofstream Usersoutput("Users.txt");
    users.saveUsers(Usersoutput);

    Usersoutput.close();
    Usersinput.close();
    users.saveUsers(Usersoutput);

}