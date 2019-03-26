//
//  mazestack.hpp
//  Problem1
//
//  Created by Samritha Nagesh on 2/2/19.
//  Copyright © 2019 Samritha Nagesh. All rights reserved.
//

#ifndef MAZESTACK_INCLDUED
#define MAZESTACK_INCLDUED

#include <string>
#include <iostream>
#include <stack>
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
bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec);
// Return true if there is a path from (sr,sc) to (er,ec)
// through the maze; return false otherwise


#endif //MAZESTACK_INCLDUED
