#include "Graph.h"
#include "AddedFunctionality.h"


Graph::Graph()
{
    this->location = 0;
    this->membersSize = 0;
    initializeMassive(AdjacencyMatrix);
}

void Graph::readFromFile(string fileName)
{
    ifstream readFile(fileName);
    if (!readFile.is_open())
        {
            cout << "Error during the opening" << endl;
        }
    else
        {
            string rowRead;

            while (getline(readFile, rowRead))
                {
                    int index = 0;
                    string wordRead = "";
                    int intersectionIndex;
                    while (rowRead[index] != ' ')
                        {
                            wordRead = wordRead + rowRead[index];
                            ++index;
                        }
                    //cout << wordRead << endl;
                    if (members.find(wordRead) != members.end())
                        {
                            intersectionIndex = members[wordRead];
                        }

                    else
                        {
                            members.insert(pair<string, int>(wordRead, membersSize));
                            intersectionIndex = membersSize;
                            ++membersSize;
                        }
                    ++index;
                    for (index; index < rowRead.length(); index++)
                        {
                            wordRead = "";
                            int crossIndex;

                            while (rowRead[index] != ' ')
                                {
                                    wordRead += rowRead[index];
                                    index++;
                                }
                            if (members.find(wordRead) != members.end())
                                {
                                    crossIndex = members[wordRead];
                                }
                            else
                                {
                                    members.insert(pair<string, int>(wordRead, membersSize));
                                    crossIndex = membersSize;
                                    membersSize++;
                                }
                            index++;
                            wordRead = "";

                            while (rowRead[index] != ' ' && index < rowRead.length()) {
                                    wordRead += rowRead[index];
                                    index++;
                                }
                            AdjacencyMatrix[intersectionIndex][crossIndex] = stoi(wordRead);
                        }

                }

            readFile.close();
        }
}

void Graph::moveOn(string &input)
{
    if(members.find(input) != members.end())
        {
            int index=members[input];
            cout<<"Location is changed successfully..."<<endl;
            location=index;
        }
    else
        {
            cout<<"Location does not exist in the map..."<<endl;
        }
}

int Graph::getLocation() const
{
    return this->location;
}

string Graph::searchTheList(int n)
{
    for(auto it = this->members.begin(); it != this->members.end(); ++it)
        {
            if (it->second == n)
                return it->first;
        }
    return "";
}

bool Graph::isConnectionBtwTwo(int startPoint, int endPoint)
{
    bool visited[MAXIMUM] = { false };
    return isRoute(startPoint, endPoint, this->AdjacencyMatrix, visited, membersSize );
}

int Graph::returnStarttoInt(string startName)
{
    int startInt = members[startName];
    return startInt;
}

int Graph::returnEndtoInt(string endName)
{
    int endInt = members[endName];
    return endInt;
}

bool Graph::isConnectionWithEverySingleVertex(string startName)
{
    int start = members[startName];
    bool visitedVertexes[MAXIMUM] = { false };
    bool visitedCurrentVertexes[MAXIMUM]= { false };
    bool flag;

    for (auto i = 0; i < membersSize; i++)
        {
            if (i == start)
                {
                    continue;
                }
            flag = isRoute(start, i, AdjacencyMatrix, visitedCurrentVertexes, membersSize );
            if (flag)
                {
                    for (int j = 0; j < membersSize; j++)
                        {
                            visitedVertexes[j] = visitedVertexes[j] || visitedCurrentVertexes[j];
                            visitedCurrentVertexes[j] = 0;
                            flag = flag && visitedVertexes[j];
                        }
                    if (flag)
                        {
                            return true;
                        }
                }
            else
                {
                    return false;
                }
        }
    return false;
}


bool Graph::Final(int index)
{
    if(this->AdjacencyMatrix[index][index]<0)
        {
            return true;
        }
    for(auto i=0;i<membersSize;i++)
        {
            if(i==index)
                {
                    continue;
                }
            if(this->AdjacencyMatrix[index][i] >0)
                {
                    return false;
                }
        }

    return true;
}
void Graph::printAllFinals()
{
    for(auto i=0;i<membersSize;i++)
        {
            if(Final(i))
                {
                    for(int j=0; j < membersSize; j++)
                        {
                            if(i==j)
                                {
                                    continue;
                                }
                            if(this->AdjacencyMatrix[j][i]>0)
                                {
                                    cout <<"The Node:"<<" "<< searchTheList(i) <<" "<<"is the deadend and the road comes from the Node:"<<" "s<< searchTheList(j) << endl;
                                }
                        }
                }
        }
}

double Graph::sumRoute(Edge edge)
{
    double sum=0;
    for(int i=0;i<edge.edgeSize - 1; ++i)
        {
            sum+=AdjacencyMatrix[edge.edgeMass[i]][edge.edgeMass[i+1]];
        }
    return sum;
}

void Graph::printEdge(Edge edge) {
    int i = 0;
    while(i<edge.edgeSize)
        {
            cout<<searchTheList(edge.edgeMass[i])<<" ";
            i++;
        }
    //cout<<endl;
}

int Graph::Cycle(int start)
{
    for(auto i=membersSize/2;i<membersSize;i++)
        {
            if(i==start)
                {
                    continue;
                }
            if(isConnectionBtwTwo(start,i)&&isConnectionBtwTwo(i,start))
                {
                    return i;
                }
        }
    for(auto i=membersSize/2;i>=0;i--)
        {
            if(i==start)
                {
                    continue;
                }
            if(isConnectionBtwTwo(start,i) && isConnectionBtwTwo(i,start))
                {
                    return i;
                }
        }

    return -1;
}

void Graph::findConnections(int start, int end, vector<Edge> &edges, bool* visited, int &edgeIndex,int *edge) {

    visited[start]=true;
    edge[edgeIndex]=start;
    edgeIndex++;

    if(start!=end)
        {
            for(auto i=0;i<membersSize;i++)
                {
                    if(!visited[i] && this->AdjacencyMatrix[start][i]>0 && this->AdjacencyMatrix[i][i]>=0)
                        {
                            findConnections(i, end, edges,visited, edgeIndex,edge);
                        }
                }

        }
    else
        {
            Edge newEdge;
            newEdge.edgeSize = edgeIndex;
            for(int i=0;i<edgeIndex;i++)
                {
                    newEdge.edgeMass[i] = edge[i];
                    edges.push_back(newEdge);
                }
        }
    visited[start]=false;
    edgeIndex--;

}


void Graph::findNeighbours()
{
    int i = 0;
    while(i<membersSize)
        {

            if(this->AdjacencyMatrix[location][i]>0)
                {
                    cout<<searchTheList(i)<<" ";
                }
                i++;
        }
    cout<<endl;

}

void Graph::close()
{
    string inp1;
    cout<<"Which intersection would you like to be closed?"<<endl;
    cin>>inp1;
    if(members.find(inp1) != members.end())
    {
            closeIntersection(members[inp1], this->AdjacencyMatrix);
            cout<<"Successfully closed"<<endl;
    }
    else
        {
            cout<<"Not found 404 :D"<<endl;

        }
}

void Graph::open()
{
    string inp1;
    cout<<"Which intersection would you like to be opened?"<<endl;
    cin>>inp1;
    if(members.find(inp1) != members.end())
    {
            openIntersection(members[inp1], this->AdjacencyMatrix);
            cout<<"Successfully opened"<<endl;
    }
    else
        {
            cout<<"Not found 404 :D"<<endl;
        }
}

void Graph::threeWays(int startPoint, int endPoint)
{
    int count=3;
    if(!isConnectionBtwTwo(startPoint, endPoint))
        {
            cout<<"Error"<<endl;
            return;
        }
    bool visitedVertexes[MAXIMUM]={false};
    int* edge=new int[membersSize];
    int edgeIndex=0;
    vector<Edge> edgeMass;
    findConnections(startPoint, endPoint, edgeMass, visitedVertexes, edgeIndex, edge);
    delete[] edge;
    for(int i=0;i<count && !edgeMass.empty();i++)
        {
            int min=INT32_MAX;
            int minIndex=0;
            for(int k = 0;k < edgeMass.size();k++)
                {   int evaluated=sumRoute(edgeMass[k]);
                    if(evaluated < min)
                        {
                            min = evaluated;
                            minIndex = k;
                        }
                }
            printEdge(edgeMass[minIndex]);
            cout<<"- "<<min<<endl;
            edgeMass.erase(edgeMass.begin() + minIndex);
        }
}


