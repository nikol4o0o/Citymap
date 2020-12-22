#include"Graph.h"
#include"Edge.h"


using namespace std;

int main()
{
    Graph map;
    //ofstream output("input.txt");
    
    map.readFromFile("input.txt");
    //map.printAllStops();
    cout<<endl;
    cout<<map.isWay("A", "D");
    cout<<endl;
    cout<<"Hello world\n";
    return 0;
}
