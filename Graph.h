#pragma once
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include<fstream>
#include<string>
#include "Edge.h"
#define MAXIMUM 20

using namespace std;
class Graph
{
private:
    //Using ordered map, which is Trie will search faster
    unordered_map<string, int> members;
    int AdjacencyMatrix[MAXIMUM][MAXIMUM]{};
    int membersSize;
    int location;

public:
    Graph();

//Additional Functions Related to the Graph, other ones are located in AddedFunctionality.h
public:
    void printEdge(Edge edge);
    void readFromFile(string fileName);
    string searchTheList(int n);
    bool isConnectionBtwTwo(int startPoint, int endPoint);
    bool isWay(string startName, string endName);
    bool isConnectionWithEverySingleVertex(string startName);
    void findConnections(int start, int end, vector<Edge> &edges, bool* visited, int &edgeIndex,int *edge);
    void printAllFinals();
    bool Final(int i);
    double sumRoute(Edge edge);
    int Cycle(int start);
    //For the Menu
    int getLocation()const;
    void moveOn(string& input);
    void findNeighbours();
    void close();
    void open();




};


