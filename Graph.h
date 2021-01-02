#pragma once
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include<fstream>
#include<string>
#include "Edge.h"
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

//Additional Functions Related to the Graph, other ones are located in AddedFunctionality.h
public:
    void printEdge(Edge edge);
    void readFromFile(string fileName);
    string searchTheList(int n);
    bool isWay(string startName, string endName);
    bool isRouteToEverySingleVertex(string startName);
    void printAllFinals();
    bool isFinal(int i);
    double sumRoute(Edge edge);



};

