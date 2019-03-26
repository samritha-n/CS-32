//
//  history.hpp
//  Project1
//
//  Created by Samritha Nagesh on 1/13/19.
//  Copyright © 2019 Samritha Nagesh. All rights reserved.
//

#ifndef HISTORY_INCLUDED
#define HISTORY_INCLUDED
#include "globals.h"

class History
{
    public:
        History(int nRows, int nCols);
        bool record(int r, int c);
        void display() const;
    private:
        int m_row;
        int m_col;
        char m_display[MAXROWS][MAXCOLS];
    
};

#endif //HISTORY_INCLUDED
