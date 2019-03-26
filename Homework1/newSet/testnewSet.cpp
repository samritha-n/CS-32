////
////  testnewSet.cpp
////  Homework1
////
////  Created by Samritha Nagesh on 1/22/19.
////  Copyright © 2019 Samritha Nagesh. All rights reserved.
////
////
#include "newSet.h"
#include <string>
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
    Set a(1000);   // a can hold at most 1000 distinct items
    Set b(5);      // b can hold at most 5 distinct items
    Set c;         // c can hold at most DEFAULT_MAX_ITEMS distinct items
    ItemType v[6] = { 234, 523, 983, 231, 237,238 };

    // No failures inserting 5 distinct items into b
    for (int k = 0; k < 5; k++)
        assert(b.insert(v[k]));

    // Failure if we try to insert a sixth distinct item into b
    assert(!b.insert(v[5]));

    // When two Sets' contents are swapped, their capacities are swapped
    // as well:
    a.swap(b);
    assert(!a.insert(v[5])  &&  b.insert(v[5]));
}
