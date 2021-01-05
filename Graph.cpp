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

string Graph::searchTheList(int n) {
    map<string, int>::const_iterator it;
    for(it = this->members.cbegin(); it != this->members.cend(); ++it)
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

bool Graph::isWay(string startName, string endName)
{
    int start = members[startName];
    int end = members[endName];
    isConnectionBtwTwo(start, end);
}

bool Graph::isConnectionWithEverySingleVertex(string startName)
{
    int start = members[startName];
    bool visitedVertexes[MAXIMUM] = { false };
    bool visitedCurrentVertexes[MAXIMUM]= { false };
    bool flag;

    for (int i = 0; i < membersSize; i++)
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
    for(int i=0;i<membersSize;i++)
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
    for(int i=0;i<membersSize;i++)
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
    for(int i=membersSize/2;i<membersSize;i++)
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
    for(int i=membersSize/2;i>=0;i--)
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
            for(int i=0;i<membersSize;i++)
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




