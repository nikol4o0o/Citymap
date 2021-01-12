#pragma once
#include <iostream>
#include<string>
#include<list>

using namespace std;
class Edge
{
public:
    int length;
    int edgeSize;
    int edgeMass[20];

    Edge()
    {
        length = 0;
        edgeSize = 0;
        //edgeMass[20] = {0};

    }

};


