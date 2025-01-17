#pragma once


bool isRoute(int start, int end,const int Matrix[20][20], bool* visitedVertexes, int size)
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
            if (!visitedVertexes[i] && Matrix[start][i] > 0 && isRoute(i, end, Matrix, visitedVertexes, size))
                {
                    return true;
                }
        }
    return false;
}

void initializeMassive(int matrix[20][20])
{
    for(auto i = 0; i < 20; i++)
        {
            for(auto j = 0; j < 20; j++)
                {
                    matrix[i][j] = 0;
                }
        }
}

void closeIntersection(int i, int matrix[20][20])
{
    matrix[i][i] = -1;
}

void openIntersection(int i , int matrix[20][20])
{
    matrix[i][i] = 0;
}


