#include "Graph.h"

Graph::Graph()
{
    this->location = 0;
    this->membersCounter = 0;
    for (auto i = 0; i < MAXIMUM; ++i)
    {
        for (auto j = 0; j < MAXIMUM; ++j)
        {
            AdjacencyMatrix[i][j] = 0;
        }
    }
}

void Graph::readFromFile(string fileName)
{
    ifstream input(fileName);
    if (!input.is_open())
    {
        cout << "Error during the opening" << endl;
    }
    else
    {
    
    string rowRead;
    

    while (getline(input, rowRead))
    {
        int index = 0;
        string wordRead = "";
        int intersectionIndex;
        while (rowRead[index] != ' ')
        {
            wordRead= wordRead + rowRead[index];
            ++index;
        }
        if (members.find(wordRead) != members.end())
        {
            intersectionIndex = members[wordRead];
        }
        else
        {
            members.insert(pair<string, int>(wordRead, membersCounter));
            intersectionIndex = membersCounter;
            ++membersCounter;
        }
        ++index;
        while (index < rowRead.length())
        {
            wordRead = "";
            int crossIndex;
            while (rowRead[index] != ' ')
            {
                wordRead += rowRead[index];
                index++;
            }
            if (members.find(wordRead) == members.end())
            {
                members.insert(pair<string, int>(wordRead, membersCounter));
                crossIndex = membersCounter;
                membersCounter++;
            }
            else
            {
                crossIndex = members[wordRead];
            }
            index++;
            wordRead = "";

            while (rowRead[index] != ' ' && index < rowRead.length())
            {
                wordRead += rowRead[index];
                index++;
            }
            AdjacencyMatrix[intersectionIndex][crossIndex] = stoi(wordRead);
            index++;
        }

    }

    input.close();
}
}
bool Graph::isThereRouteinGraph(int start, int end, int Matrix[MAXIMUM][MAXIMUM], bool* visitedVertexes, int size)
{
    visitedVertexes[start] = true;
    if(Matrix[end][end]<0)
        return false;
    if (Matrix[start][end] > 0)
    {
        visitedVertexes[end] = true;
        return true;
    }

    for (int i = 0; i < size; i++)
    {
        if(Matrix[i][i]<0)//check if closed
        {
            continue;
        }
        if (visitedVertexes[i] == false && Matrix[start][i] > 0 && isThereRouteinGraph(i, end, Matrix, visitedVertexes, size))
        {
            return true;
        }
    }
    return false;
}

void Graph::printTheMatrixforTest()
{
    for(auto it = members.cbegin(); it != members.cend(); ++it)
    {
        std::cout << it->first << " " << it->second<< "\n";
    }
}

Graph::~Graph()
{
 
}


