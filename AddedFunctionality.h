//#pragma once
#define MAXIMUM 20

bool isRoute(int start, int end,const int Matrix[MAXIMUM][MAXIMUM], bool* visitedVertexes, int size)
{
    visitedVertexes[start] = true;
    if(Matrix[end][end]<0)
        return false;
    if (Matrix[start][end] > 0)
        {
            visitedVertexes[end] = true;
            return true;
        }

    for (auto i = 0; i < size; i++)
        {
            if(Matrix[i][i]<0)
                {
                    continue;
                }
            if (visitedVertexes[i] == false && Matrix[start][i] > 0 && isRoute(i, end, Matrix, visitedVertexes, size))
                {
                    return true;
                }
        }
    return false;
}

void initializeMassive(int matrix[MAXIMUM][MAXIMUM])
{
    for(auto i = 0; i < 20; i++)
        {
            for(auto j = 0; j < 20; j++)
                {
                    matrix[i][j] = 0;
                }
        }
}

void closeIntersection(int i, int matrix[MAXIMUM][MAXIMUM])
{
    matrix[i][i] = -1;
}

void openIntersection(int i , int matrix[MAXIMUM][MAXIMUM])
{
    matrix[i][i] = 0;
}


