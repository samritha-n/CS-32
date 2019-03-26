//
//  main.cpp
//  Project2
//
//  Created by Samritha Nagesh on 1/25/19.
//  Copyright © 2019 Samritha Nagesh. All rights reserved.
//

#include "Set.h"
#include <iostream>
#include <cassert>
using namespace std;

void test()
{
    Set s1;
    
    s1.insert(3);
    s1.insert(9);
    s1.insert(2);
    s1.insert(8);
    
    
    Set s2;
    s2.insert(9);
    s2.insert(8);
    s2.insert(7);
    
    Set result;
    
    unite(s1,s2,result);
    result.insert(8);
    result.insert(7);
    result.dump();
}

int main()
{
    test();
    cout << "Passed all tests" << endl;
}

