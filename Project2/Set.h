//
//  Set.hpp
//  Project2
//
//  Created by Samritha Nagesh on 1/25/19.
//  Copyright © 2019 Samritha Nagesh. All rights reserved.
//

#ifndef SET_INCLUDED
#define SET_INCLUDED

#include <string>

// Later in the course, we'll see that templates provide a much nicer
// way of enabling us to have Sets of different types.  For now,
// we'll use a type alias.

using ItemType = int;

const int DEFAULT_MAX_ITEMS = 250;

class Set
{
public:
    Set();               // Create an empty set (i.e., one with no items).
    
    bool empty() const;  // Return true if the set is empty, otherwise false.
    
    int size() const;// Return the number of items in the set.
    
    ~Set();
    
    Set(const Set& other);
    
    Set& operator=(const Set& rhs);
    
    bool insert(const ItemType& value);
    // Insert value into the set if it is not already present.  Return
    // true if the value was actually inserted.  Leave the set unchanged
    // and return false if the value was not inserted (perhaps because it
    // was already in the set or because the set has a fixed capacity and
    // is full).
    
    bool erase(const ItemType& value);
    // Remove the value from the set if present.  Return true if the
    // value was removed; otherwise, leave the set unchanged and
    // return false.
    
    bool contains(const ItemType& value) const;
    // Return true if the value is in the set, otherwise false.
    
    bool get(int i, ItemType& value) const;
    // If 0 <= i < size(), copy into value the item in the set that is
    // strictly greater than exactly i items in the set and return true.
    // Otherwise, leave value unchanged and return false.
    
    void swap(Set& other);
    // Exchange the contents of this set with the other one.
    
    void dump() const;
    //Print items in the linked list
    
private:
    int m_size;
    // number of items in the set
    struct Node{
        ItemType value;
        Node* next;
        Node* prev;
    };
    Node* m_head;
};

// Inline implementations

inline
int Set::size() const
{
    return m_size;
}

inline
bool Set::empty() const
{
    return m_size==0;
}
void unite(const Set& s1, const Set& s2, Set& result);
void subtract(const Set& s1, const Set& s2, Set& result);

#endif // SET_INCLUDED

