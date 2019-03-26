//
//  Set.cpp
//  Homework1
//
//  Created by Samritha Nagesh on 1/16/19.
//  Copyright © 2019 Samritha Nagesh. All rights reserved.
//

#include "Set.h"
#include <iostream>

Set::Set()
{
    m_size = 0;
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
    if(contains(value) || (m_size) >= DEFAULT_MAX_ITEMS){
        return false;
    }
    
//    int index = 0;
//    for(index=0; index < m_size; index++){
//        if(m_set[index] >= value){
//            for(int j = m_size; j > index; j--){
//                m_set[j] = m_set[j-1];
//            }
//        }
//    }
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
    
    int newSize;
    if(other.size() > m_size){
        newSize = other.size();
    }
    else
        newSize = m_size;
    
    for(int i=0; i < newSize; i++){
        ItemType temp = m_set[i];
        m_set[i] = other.m_set[i];
        other.m_set[i] = temp;
    }
}

void Set::dump() const{
    for(int i=0; i<m_size; i++){
        std::cerr << m_set[i] << " ";
    }
    std::cerr << std::endl;
}
