#pragma once

bool isWayInGraph(int start, int end,const int Matrix[20][20] , int size,bool* visited)
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
