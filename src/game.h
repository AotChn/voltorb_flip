#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <time.h>
#include "constants.h"
#include "board.h"
#include "ai.h"

class game{

private:
    board b;
    int wins,
        loses,
        coins,
        score,
        it,
        cur_it;
public:

game(){reset();}

//===========================================
//	GAME STATE
//===========================================
    
    //run game normally
    void play();

    //run game with ai
    void play(ai_player);
    
    //when you win
    void win();

    //when you lose
    void lose();

    //when you finish game
    void complete();

    //win stats
    void winrate();

    //reset game
    void reset();

};


#endif