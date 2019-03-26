//
//  mazequeue.cpp
//  Problem1
//
//  Created by Samritha Nagesh on 2/2/19.
//  Copyright © 2019 Samritha Nagesh. All rights reserved.
//

#include <queue>
#include <iostream>
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

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec){
    queue<Coord> coordMaze;
    Coord startCoord(sr,sc);
    coordMaze.push(startCoord);
    maze[sr][sc] = 'X';
    
    while(!coordMaze.empty()){
        Coord curr = coordMaze.front();
        coordMaze.pop();
        if(curr.r() == er && curr.c() == ec)
            return true;
        int curr_r = curr.r();
        int curr_c = curr.c();
        cout << curr_r << " " << curr_c << endl;
        if(maze[curr_r+1][curr_c] != 'X'){ //SOUTH
            maze[curr_r+1][curr_c] = 'X';
            coordMaze.push(Coord(curr_r+1,curr_c));
        }
        if(maze[curr_r][curr_c-1] != 'X'){ //WEST
            maze[curr_r][curr_c-1] = 'X';
            coordMaze.push(Coord(curr_r,curr_c-1));
        }
        if(maze[curr_r-1][curr_c] != 'X'){ //NORTH
            maze[curr_r-1][curr_c] = 'X';
            coordMaze.push(Coord(curr_r-1,curr_c));
        }
        if(maze[curr_r][curr_c+1] != 'X'){ //EAST
            maze[curr_r][curr_c+1] = 'X';
            coordMaze.push(Coord(curr_r,curr_c+1));
        }
        
    }
    return false;
}

int main()
{
    string maze[10] = {
        "XXXXXXXXXX",
        "X....X...X",
        "X.XX.XX..X",
        "XXX....X.X",
        "X.XXX.XXXX",
        "X.X...X..X",
        "X...X.X..X",
        "XXXXX.X.XX",
        "X........X",
        "XXXXXXXXXX"
    };
    
    if (pathExists(maze, 10,10, 3,5, 8,8))
        cout << "Solvable!" << endl;
    else
        cout << "Out of luck!" << endl;
}
