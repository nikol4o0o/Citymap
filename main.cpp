#include<iostream>
#include"Graph.h"
#include"Edge.h"


using namespace std;

int main()
{
    Graph map;
    //ofstream output("input.txt");
    
    map.readFromFile("input.txt");
    map.printTheMatrixforTest();
    cout<<"Hello world\n";
    return 0;
}
