//
//  Zombie.hpp
//  Project1
//
//  Created by Samritha Nagesh on 1/9/19.
//  Copyright © 2019 Samritha Nagesh. All rights reserved.
//

#ifndef ZOMBIE_INCLUDED
#define ZOMBIE_INCLUDED
class Arena;
class Zombie
{
    public:
        // Constructor
        Zombie(Arena* ap, int r, int c);
    
        // Accessors
        int  row() const;
        int  col() const;
    
        // Mutators
        void move();
        bool getAttacked(int dir);
    
    private:
        Arena* m_arena;
        int    m_row;
        int    m_col;
        int    m_health;
};
#endif //ZOMBIE_INCLUDED
