#pragma once
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include<fstream>
#define MAXIMUM 20

using namespace std;
class Graph
{
private:
	map<string, int> members;
	int AdjacencyMatrix[MAXIMUM][MAXIMUM];
	int membersCounter;
	int location;
	
public:
	Graph();
	~Graph();

//Additional Functions
public:
	void readFromFile(string fileName);
	void printAllStops();
	bool isEnd(int index);
	string findByValue(int n);

};

