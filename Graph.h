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
    int membersSize;
    int location;
    
public:
    Graph();

//Additional Functions
public:
    void readFromFile(string fileName);
    string searchTheList(int n);
    bool isWay(string startName, string endName);
    bool isRouteToEverySingleVertex(string startName);

};

