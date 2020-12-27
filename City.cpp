#include"Graph.h"
#include"Edge.h"


using namespace std;

int main()
{
    Graph map;
    //ofstream output("input.txt");
    
    map.readFromFile("input.txt");
    //cout<<map.isWay("C", "A");
    cout<<endl;
    //cout<<map.isRouteToEverySingleVertex("A");
    cout<<endl;
    map.printAllFinals();
    cout<<"Hello world\n";
    cout<<endl;
    return 0;
}
