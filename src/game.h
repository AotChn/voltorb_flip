#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <time.h>
#include "constants.h"
#include "board.h"
#include "ai.h"
#include "data.h"

class game{

private:
    data collector;
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

    //run game with ai and collect data
    void play(ai_player,int i);

    //run game with ai and collect data on certain level
    void play(ai_player,int, int);
    
    //when you win
    void win();

    //win and go to level l
    void win(int l);

    //when you lose
    void lose();

    //lose and go to level l
    void lose(int l);

    //when you finish game
    void complete();

    //win stats
    void winrate();

    //reset game
    void reset();

    board get_board(){return b;}

};


#endif