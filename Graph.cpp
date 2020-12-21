#include "Graph.h"


bool isWayInGraph(int start, int end,const int Matrix[MAXIMUM][MAXIMUM] , int size,bool* visited)
{
    visited[start] = true;
    if(Matrix[end][end]<0)
        return false;
    if (Matrix[start][end] > 0)
    {
        visited[end] = true;
        return true;
    }

    for (int i = 0; i < size; i++)
    {
        if(Matrix[i][i]<0)//check if closed
        {
            continue;
        }
        if (visited[i] == false && Matrix[start][i] > 0 && isWayInGraph(i, end, Matrix, size, visited))
        {
            return true;
        }
    }
    return false;
}

Graph::Graph()
{
    this->location = 0;
    this->membersSize = 0;
    for (auto i = 0; i < MAXIMUM; ++i)
    {
        for (auto j = 0; j < MAXIMUM; ++j)
        {
            AdjacencyMatrix[i][j] = 0;
        }
    }
}

void Graph::readFromFile(string fileName) {
    ifstream readFile(fileName);
    if (!readFile.is_open()) {
        cout << "Error during the opening" << endl;
    } else {
        string rowRead;


        while (getline(readFile, rowRead)) {
            int index = 0;
            string wordRead = "";
            int intersectionIndex;
            while (rowRead[index] != ' ') {
                wordRead = wordRead + rowRead[index];
                ++index;
            }
            //cout << wordRead << endl;
            if (members.find(wordRead) != members.end()) {
                intersectionIndex = members[wordRead];
            } else {
                members.insert(pair<string, int>(wordRead, membersSize));
                intersectionIndex = membersSize;
                ++membersSize;
            }
            ++index;
            for (index; index < rowRead.length(); index++) {
                wordRead = "";
                int crossIndex;
                while (rowRead[index] != ' ') {
                    wordRead += rowRead[index];
                    index++;
                }
                if (members.find(wordRead) != members.end()) {
                    crossIndex = members[wordRead];
                } else {
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

bool Graph::isEnd(int index) {
    if (this->AdjacencyMatrix[index][index] < 0) return true;
    for (auto i = 0; i < membersSize; i++)
    {
        if (i == index) continue;
        if (this->AdjacencyMatrix[index][i] > 0)
            return false;
    }

    return true;
}

string Graph::findByValue(int n) {
    map<string, int>::const_iterator it = this->members.begin();
    while (it != this->members.end())
    {
        if (it->second == n)
            return it->first;
        it++;
    }
    return "";
}

void Graph::printAllStops() {
    for (auto i = 0; i < membersSize; i++)
    {
        if (isEnd(i))
        {
            for (int k = 0; k < membersSize; k++)
            {
                if (i == k) continue;
                if (this->AdjacencyMatrix[k][i] > 0)
                {
                    cout << findByValue(k) << " - " << findByValue(i) << endl;
                }
            }
        }
    }
}



bool Graph::isWay(int start, int end)
{
    bool visited[MAXIMUM] = { false };
    return isWayInGraph(start, end, this->AdjacencyMatrix, membersSize, visited );
}

void Graph::isWay(string startName, string endName) {
    if(isWay(members[startName],members[endName]))
    {
        cout<<"there is way between "<<startName<<" and "<<endName<<endl;
        return;
    }
    cout<<"there is NO way between "<<startName<<" and "<<endName<<endl;
}






