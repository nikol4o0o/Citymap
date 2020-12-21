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
    void printAllStops();
    string findByValue(int n);
    bool isEnd(int index);
    bool isWay(int start, int end);
    void isWay(string startName, string endName);
    void readFromFile(string fileName);
};

