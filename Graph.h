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
    bool isConnectionWithEverySingleVertex(string startName);
    void allEdges(int startPoint, int endPoint, int *edge, int &edgeIndx,bool* visitedVertexes,vector<Edge> &edges);
    void printAllFinals();
    bool Final(int i);
    int sumRoute(Edge edge);
    int halfCycle(int start);
    //For the Menu
    void PrintThreeShortest(int start, int end,int count);
    int getLocation()const;
    void moveOn();
    void findNeighbours();
    void close();
    void open();
    int returnStarttoInt(string startName);
    int returnEndtoInt(string endName);
    void tour();
    void waytoAll();





};


