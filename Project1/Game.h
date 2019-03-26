//
//  Game.hpp
//
//
//  Created by Samritha Nagesh on 1/11/19.
//

#ifndef GAME_INCLUDED
#define GAME_INCLUDED

#include "Arena.h"
#include "History.h"

class Game
{
public:
    // Constructor/destructor
    Game(int rows, int cols, int nZombies);
    ~Game();
    
    // Mutators
    void play();
    
private:
    Arena* m_arena;
};

#endif //GAME_INCLUDED
