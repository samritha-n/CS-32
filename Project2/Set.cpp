//
//  Set.cpp
//  Project2
//
//  Created by Samritha Nagesh on 1/25/19.
//  Copyright © 2019 Samritha Nagesh. All rights reserved.
//

#include "Set.h"
#include <iostream>

Set::Set()
: m_size(0)
{
    m_head = nullptr;
}
Set::~Set()
{
    Node* deleteNode = m_head;
    
    while(deleteNode != nullptr){
        Node* nextNode = deleteNode;//delete all the nodes in order
        deleteNode = deleteNode->next;
        delete nextNode;
    }
}
//Copy Constructor
Set::Set(const Set& other)
: m_size(other.m_size)
{
    Node *newNode = other.m_head;
    m_head = new Node;
    
    while(newNode != nullptr){      //Copy all the values into this set
        insert(newNode->value);
        newNode=newNode->next;
    }
    
}

Set& Set::operator=(const Set& rhs)
{
    if (m_head != rhs.m_head)
    {
        Set temp(rhs);
        swap(temp);
    }
    return *this;
}
bool Set::insert(const ItemType& data)
{
    Node *insertNode = new Node;
    insertNode->value = data;
    
    if(empty()){
        m_head=insertNode;
        m_head->next = nullptr;
        m_head->prev = nullptr;
        
        m_size++;
        return true;
    }
    if(m_head->value > data){
        insertNode->next = m_head;
        m_head->prev = insertNode;
        insertNode->prev = nullptr;
        m_head=insertNode;
        m_size++;
        return true;
    }
    
    else{
        Node* temp = m_head;
        
        for(int i=0; i<m_size; i++){
            if(temp->value == data){
                return false;
            }
            else if(temp->value > data){
                insertNode->next = temp;
                insertNode->prev = temp->prev;
                temp->prev = insertNode;
                temp->prev->next = insertNode;
                
                m_size++;
                return true;
                
            }
            else if (i == m_size-1){
                temp->next = insertNode;
                insertNode->next = nullptr;
                insertNode->prev = temp;
                m_size++;
                return true;
            }
            temp = temp->next;
        }
        
    }
    return false;
    
}

bool Set::erase(const ItemType& data)
{
    if(empty())
        return false;
    if (m_head->value == data)
    {
        if(m_size == 1){
            m_head=nullptr;
        }
        else{
            m_head = m_head->next;
            m_head->prev = nullptr;
        }
        m_size--;
        return true;
    }
    Node* temp = m_head;
    for(int i=0; i < m_size; i++){
        if(temp->value == data){
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
            delete temp;
            m_size--;
            return true;
        }
        temp = temp->next;
    }
    return false;
}

bool Set::get(int i, ItemType& value) const
{
    if (i < 0  ||  i >= m_size)
        return false;
    Node* temp = m_head;
    for(int r=0; r<i; r++){
        temp=temp->next;
    }
    value = temp->value;
    return true;
}
bool Set::contains(const ItemType& value) const{
    Node* temp = m_head;
    for(int i=0; i<m_size; i++){
        if(temp->value == value){
            return true;
        }
        temp=temp->next;
    }
    return false;
}

void Set::swap(Set& other)
{
    // Swap elements.  Since the only elements that matter are those up to
    // m_size and other.m_size, only they have to be moved.
    
    Node* temp = m_head;
    m_head = other.m_head;
    other.m_head = temp;
    
    // Swap sizes
    int tempSize = m_size;
    m_size = other.m_size;
    other.m_size = tempSize;
}
void Set::dump() const{
    Node* p;
    p = m_head;
    while (p != nullptr){
        std::cerr << p->value << std::endl;
        p = p->next;
    }
}
void unite(const Set& s1, const Set& s2, Set& result){
    if(&s1 != &result && &s2 != &result){ //Can't refer to same set
        for(int n=0; n<result.size(); n++){
            ItemType erase;
            result.get(n,erase);
            result.erase(erase);
        }
        for(int i=0; i<s1.size(); i++){
            ItemType item1;
            s1.get(i,item1);
            result.insert(item1);
        }
        for(int r=0; r<s2.size(); r++){
            ItemType item2;
            s2.get(r,item2);
            result.insert(item2);
        }
    }
    
}
void subtract(const Set& s1, const Set& s2, Set& result){
    if(&s1 != &result && &s2 != &result){
        for(int n=0; n<result.size(); n++){
            ItemType erase;
            result.get(n,erase);
            result.erase(erase);
        }
        for(int i=0; i<s1.size(); i++){
            ItemType item1;
            s1.get(i,item1);
            if(!s2.contains(item1))
                result.insert(item1);
        }
    }
}
