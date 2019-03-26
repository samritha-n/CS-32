//
//  main.cpp
//  Prob3
//
//  Created by Samritha Nagesh on 2/11/19.
//  Copyright © 2019 Samritha Nagesh. All rights reserved.
//

#include <string>

using namespace std;


class Coord
{
public:
    Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
    int r() const { return m_r; }
    int c() const { return m_c; }
private:
    int m_r;
    int m_c;
};
bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec)
{
    if (sr < 0  ||  sr >= nRows  ||  sc < 0  || sc >= nCols  ||
        er < 0  ||  er >= nRows  ||  ec < 0  || ec >= nCols  ||
        maze[sr][sc] != '.'  ||  maze[er][ec] != '.')
        return false;
    
   if(sr == er && sc == ec)
       return true;
    maze[sr][sc] = 'X';
    //NORTH
    if(maze[sr-1][sc] != 'X'){
        if(pathExists(maze, nRows, nCols, sr-1, sc, er, ec))
            return true;
    }
    //SOUTH
    if(maze[sr+1][sc] != 'X'){
        if(pathExists(maze, nRows, nCols, sr+1, sc, er, ec))
            return true;
    }
    //EAST
    if(maze[sr][sc+1] != 'X'){
        if(pathExists(maze, nRows, nCols, sr, sc+1, er, ec))
            return true;
    }
    //WEST
    if(maze[sr][sc-1] != 'X'){
        if(pathExists(maze, nRows, nCols, sr, sc-1, er, ec))
            return true;
    }
    
    
    return false;
}
int main(){}
