#include "Map.h"

Map::Map()
{
	this->location = 0; 
	this->membersCounter = 0; 
	for (int i = 0; i < MAXIMUM; ++i)
	{
		for (int j = 0; j < MAXIMUM; ++j)
		{
			AdjacencyMatrix[i][j] = 0;
		}
	}
}

Map Map::readFromFile(string fileName)
{
	ifstream input("fileName");
	string rowRead;
	

	while (getline(input, rowRead))
	{
		int index = 0;
		string wordRead = "";
		int intersectionIndex;
		while (rowRead[index] != ' ')
		{
			rowRead= rowRead + wordRead[index];
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