//
//  history.cpp
//  Project1
//
//  Created by Samritha Nagesh on 1/13/19.
//  Copyright © 2019 Samritha Nagesh. All rights reserved.
//

#include "History.h"
#include "Arena.h"
#include "globals.h"
#include <iostream>
using namespace std;

History::History(int nRows, int nCols)
{
    m_row = nRows;
    m_col = nCols;
    for(int r = 0; r < m_row; r++){
        for(int c = 0; c < m_col; c++){
            m_display[r][c] = '.';
        }
    }
}
bool History::record(int r, int c)
{
    if(r < 1 || r > m_row || c < 1 || c > m_col) //if r or c is out of bounds
        return false;
    
    if(m_display[r-1][c-1] == '.'){ 
        m_display[r-1][c-1] = 'A';
    }
    else if (m_display[r-1][c-1] >= 'A' && m_display[r-1][c-1] < 'Z')
        m_display[r-1][c-1]++;
    return true;
    
}
void History::display() const
{
    clearScreen();
    for(int r = 0; r < m_row; r++){
        for(int c = 0; c < m_col; c++)
            cout << m_display[r][c];
        cout << endl;
    }
    cout << endl;
}
