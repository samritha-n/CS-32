//
//  newSet.cpp
//  Homework1
//
//  Created by Samritha Nagesh on 1/16/19.
//  Copyright © 2019 Samritha Nagesh. All rights reserved.
//

#include "newSet.h"
#include <iostream>

Set::Set(int max)
{
    if(max >= 0)
        m_maxSize = max;
    m_size = 0;
    m_set = new ItemType[m_maxSize];
}

Set::~Set()
{
    delete [] m_set;
}

Set::Set(const Set& other)
{
    m_maxSize = other.m_maxSize;
    m_size = other.m_size;
    m_set = new ItemType[m_size+1];
    for(int i=0; i<m_maxSize; i++){
        m_set[i] = other.m_set[i];
    }
    
}

Set& Set::operator=(const Set& rhs)
{
    if(this != &rhs)
    {
        m_maxSize = rhs.m_maxSize;
        m_size = rhs.m_size;
        delete m_set;
        m_set = new ItemType[m_maxSize];
        
        for(int i=0; i<m_maxSize; i++){
            m_set[i] = rhs.m_set[i];
        }
    }
    return *this;
}

bool Set::empty() const{
    if(size() == 0){
        return true;
    }
    return false;
}

bool Set::erase(const ItemType& value){
    for(int i=0; i<m_size; i++){
        if(m_set[i] == value){
            for(int j = i; j < m_size; j++){
                m_set[j] = m_set[j+1];
            }
            m_size--;
            return true;
        }
    }
    return false;
}

int Set::size() const{
    return m_size;
}

bool Set::insert(const ItemType& value){
    if(contains(value) || (m_size) >= m_maxSize){
        return false;
    }
    
    m_set[m_size] = value;
    m_size++;
    
    return true;
    
}

bool Set::contains(const ItemType& value) const{
    for(int i=0; i< m_size; i++){
        if(m_set[i] == value){
            return true;
        }
    }
    return false;
}

bool Set::get(int i, ItemType& value) const{
    if( i >= 0 && i < m_size){
        for(int j = 0; j<m_size; j++){
            int num = 0;
            for(int k = 0; k<m_size; k++){
                if(m_set[j] > m_set[k])
                    num++;
            }
            if(num == i){
                value = m_set[j];
                return true;
            }
        }
    }
    return false;
}

void Set::swap(Set& other){
    int tempS = m_size;
    m_size = other.m_size;
    other.m_size = tempS;
    
    ItemType *temp;
    temp = m_set;
    m_set = other.m_set;
    other.m_set = temp;
    
    int tempMax = m_maxSize;
    m_maxSize = other.m_maxSize;
    other.m_maxSize = tempMax;
}

void Set::dump() const{
    for(int i=0; i<m_size; i++){
        std::cerr << m_set[i] << " ";
    }
    std::cerr << std::endl;
}
