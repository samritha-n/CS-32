//
//  SSNSet.cpp
//  Homework1
//
//  Created by Samritha Nagesh on 1/21/19.
//  Copyright © 2019 Samritha Nagesh. All rights reserved.
//

#include "SSNSet.h"
#include <iostream>
using namespace std;

SSNSet::SSNSet()
{}
bool SSNSet::add(unsigned long ssn){
    return m_SSNSet.insert(ssn);
}
int SSNSet::size() const{
    return m_SSNSet.size();
}
void SSNSet::print() const{
    unsigned long ssn;
    for(int i=0; i<size(); i++){
        m_SSNSet.get(i, ssn);
        cout << ssn << endl;
    }
}
