#include "Graph.h"
#include "AddedFunctionality.h"


Graph::Graph()
{
    this->location = 0;
    this->membersSize = 0;
    initializeMassive(AdjacencyMatrix);
}

void Graph::readFromFile(std::string fileName)
{
    std::ifstream readFile(fileName);
    if (!readFile.is_open())
        {
            std::cout << "Error during the opening" << std::endl;
            return;
        }
    else
        {
            std::string rowRead;

            while (getline(readFile, rowRead))
                {
                    int index = 0;
                    std::string wordRead = "";
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
                            members.insert(std::pair<std::string, int>(wordRead, membersSize));
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
                                    members.insert(std::pair<std::string, int>(wordRead, membersSize));
                                    crossIndex = membersSize;
                                    membersSize++;
                                }
                            index++;
                            wordRead = "";

                            while (rowRead[index] != ' ' && index < rowRead.length()) {
                                    wordRead += rowRead[index];
                                    index++;
                                }
                                //The file must be correct to our preferences
                            AdjacencyMatrix[intersectionIndex][crossIndex] = stoi(wordRead);
                        }

                }

            readFile.close();
        }
}

void Graph::moveOn(std::string input)
{

    if(members.find(input) != members.end())
        {
            int index=members[input];
            std::cout<<"Location is changed successfully..."<<std::endl;
            location=index;
        }
    else
        {
            std::cout<<"Location does not exist on the map..."<<std::endl;
        }
}

void Graph::move(std::string input)
{

    if(members.find(input) != members.end())
    {
            int index=members[input];
            if(!isConnectionBtwTwo(location,index))
            {
                    std::cout<<"There is no way"<<std::endl;
            }
            else
                {
                    showEdge(location,index);
                    std::cout<<std::endl;
                    location=index;
                }
    }
    else
        {
            std::cout<<"Cannot find location"<<std::endl;
        }
}

int Graph::getLocation() const
{
    return this->location;
}

std::string Graph::searchTheList(int n)
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
    bool visited[20] = { false };
    return isRoute(startPoint, endPoint, this->AdjacencyMatrix, visited, membersSize );
}

int Graph::returnStarttoInt(std::string startName)
{
    int startInt = members[startName];
    return startInt;
}

int Graph::returnEndtoInt(std::string endName)
{
    int endInt = members[endName];
    return endInt;
}

bool Graph::isConnectionWithEverySingleVertex(std::string startName)
{
    int start = members[startName];
    bool visitedVertexes[20] = { false };
    bool visitedCurrentVertexes[20]= { false };
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
                    for (auto j = 0; j < membersSize; j++)
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
    int i = 0;
    while(i<membersSize)
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
                                    std::cout <<"The Node:"<<" "<< searchTheList(i) <<" "<<"is a deadend and the road comes from the Node:"<<" "<< searchTheList(j) << std::endl;
                                }
                        }
                }
                i++;
        }
}

int Graph::sumRoute(Edge edge)
{
    int sum=0;
    int i = 0;
    while(i<edge.edgeSize - 1)
        {
            sum+=AdjacencyMatrix[edge.edgeMass[i]][edge.edgeMass[i+1]];
            i++;
        }
    return sum;
}

void Graph::printEdge(Edge edge)
{
    int i = 0;
    while(i<edge.edgeSize)
        {
            std::cout<<searchTheList(edge.edgeMass[i])<<" - ";
            i++;
        }
}

int Graph::halfCycle(int start)
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

void Graph::findNeighbours()
{
    int i = 0;
    while(i<membersSize)
        {

            if(this->AdjacencyMatrix[location][i]>0)
                {
                    std::cout<<searchTheList(i)<<" ";
                }
                i++;
        }
    std::cout<<std::endl;

}

void Graph::close(std::string input)
{

    if(members.find(input) != members.end())
    {
            closeIntersection(members[input], this->AdjacencyMatrix);
            std::cout<<"Successfully closed"<<std::endl;
    }
    else
        {
            std::cout<<"Not found 404 :D"<<std::endl;

        }
}

void Graph::open(std::string input)
{

    if(members.find(input) != members.end())
    {
            openIntersection(members[input], this->AdjacencyMatrix);
            std::cout<<"Successfully opened"<<std::endl;
    }
    else
        {
            std::cout<<"Not found 404 :D"<<std::endl;
        }
}

void Graph::allEdges(int startPoint, int endPoint, int *edge, int &edgeIndx, bool *visitedVertexes,std::vector<Edge> &edges)
{

    visitedVertexes[startPoint]=true;
    edge[edgeIndx]=startPoint;
    edgeIndx++;

    if(startPoint==endPoint)
        {
            Edge newEdge;
            newEdge.edgeSize = edgeIndx;
            for(int i=0;i<edgeIndx;i++)
                {
                    newEdge.edgeMass[i] = edge[i];
                }
            edges.push_back(newEdge);
        }
    else
        {
            for(int i=0;i<membersSize;i++)
                {
                    if(!visitedVertexes[i] && this->AdjacencyMatrix[startPoint][i]>0 && this->AdjacencyMatrix[i][i]>=0)
                        {
                            allEdges(i, endPoint, edge, edgeIndx, visitedVertexes,edges);
                        }
                }
        }
    edgeIndx--;
    visitedVertexes[startPoint]=false;
}

void Graph::coutAlltheVertexes()
{
    for(auto it = members.begin(); it != members.end(); it++)
        {
            std::cout<<it->first<<std::endl;
        }
        return;
}

void Graph::printSmallest(int startPoint, int endPoint,int repeat = 3 )
{
    if(!isConnectionBtwTwo(startPoint,endPoint))
        {
            std::cout<<"There is no such way"<<std::endl;
            return;
        }
    std::vector<Edge> edges;
    int* edge=new int[membersSize];
    bool visitedVertexes[20]={false};
    int edgeIndx=0;
    allEdges(startPoint,endPoint,edge,edgeIndx,visitedVertexes,edges);
    delete[] edge;
    for(int i=0;i<repeat && !edges.empty();i++)
        {
            int minimum=1231312;
            int minimumIndex=0;
            for(int j = 0;j < edges.size();j++)
                {   int evaluation=sumRoute(edges[j]);
                    if(evaluation < minimum)
                        {
                            minimum = evaluation;
                            minimumIndex = j;
                        }
                }
            printEdge(edges[minimumIndex]);
            std::cout<<"is evaluated to: "<<minimum<<" meters"<<std::endl;
            edges.erase(edges.begin() + minimumIndex);
        }
}

void Graph::tour()
{
    int destination=halfCycle(location);
    if(destination<0)
        {
            std::cout<<"Tour cannot be done"<<std::endl;
        }
    else
        {
            printSmallest(location,destination,1);
            std::cout<<std::endl;
            printSmallest(destination,location,1);
            std::cout<<std::endl;
        }
}

void Graph::waytoAll(std::string input)
{

    bool check = isConnectionWithEverySingleVertex(input);
    if(check)
        {
            std::cout<<"There is a way from "<<input<<" to every single intersection"<<std::endl;
        }
    else
        {
            std::cout<<"There is no way from "<<input<<" to every single intersection"<<std::endl;
        }
}

void Graph::showEdge(int startPoint, int endPoint)
{
    std::vector<Edge> edges;
    int edgeIndx=0;
    int* edge=new int[membersSize];
    bool visitedVertexes[20]={false};

    allEdges(startPoint,endPoint,edge,edgeIndx,visitedVertexes, edges);
    printEdge(edges[0]);
    delete[] edge;
}
 void Graph::three(std::string input)
 {
    if(members.find(input) != members.end())
        {
            printSmallest(location, members[input], 3);
        }
    else
        {
            std::cout<<"There is no such location"<<std::endl;
        }
 }








