//
//  testSSNSet.cpp
//  Homework1
//
//  Created by Samritha Nagesh on 1/21/19.
//  Copyright © 2019 Samritha Nagesh. All rights reserved.
//

#include "SSNSet.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
    SSNSet s;

    ItemType x = 9876543;
    s.add(x);
    ItemType y = 1234523;
    s.add(y);
    cerr << s.size() << endl;
    s.print();
}
