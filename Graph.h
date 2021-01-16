#pragma once
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include<fstream>
#include<string>
#include "Edge.h"


class Graph
{
private:
    std::unordered_map<std::string, int> members;
    int AdjacencyMatrix[20][20]{};
    int membersSize;
    int location;


public:
    Graph();

//Additional Functions Related to the Graph, other ones are located in AddedFunctionality.h
//I have done it to clean some of the code it was a real mess!
public:
    void printEdge(Edge edge);
    void readFromFile(std::string fileName);
    std::string searchTheList(int n);
    bool isConnectionBtwTwo(int startPoint, int endPoint);
    bool isConnectionWithEverySingleVertex(std::string startName);
    void allEdges(int startPoint, int endPoint, int *edge, int &edgeIndx,bool* visitedVertexes,std::vector<Edge> &edges);
    void printAllFinals();
    bool Final(int i);
    int sumRoute(Edge edge);
    int halfCycle(int start);
    //For the Menu
    void printSmallest(int start, int end,int count);
    int getLocation()const;
    void moveOn(std::string input);
    void move(std::string input);
    void findNeighbours();
    void close(std::string input);
    void open(std::string input);
    int returnStarttoInt(std::string startName);
    int returnEndtoInt(std::string endName);
    void tour();
    void waytoAll(std::string input);
    void showEdge(int startPoint, int endPoint);
    void three(std::string input);
    void coutAlltheVertexes();





};


