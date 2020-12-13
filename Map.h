#pragma once
#include <string>
#include <map>
#include <vector>
#include<fstream>
#define MAXIMUM 20

using namespace std;
class Map
{
private:
	map<string, int> members;
	int AdjacencyMatrix[MAXIMUM][MAXIMUM];
	int membersCounter;
	int location;
	
public:
	Map();
	~Map();

//Additional Functions
public:
	Map readFromFile(string fileName);


};

