#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <queue>
#include <vector>
#include <iomanip>
#include <stdlib.h>
#include <time.h>
#include "board.h"
#include "ai/ai.h"
#include "ai/data.h"
#include "graphics/window/window_observer.h"
#include "graphics/window/constants.h"
#include "graphics/window/color_constants.h"
#include "graphics/drawable/drawable.h"
#include "graphics/cursor/cursor.h"


class game : public Window_Observer{

private:
    data collector;
    board b;
    board *b_ptr;
    int wins,
        loses,
        coins,
        score,
        it,
        cur_it,
        comp=0;
    std::queue<drawable*> toDraw;

public:

game() : cur_ST(0){
    reset();
    b_ptr = &b;
    init_cursor();
    init_board();
    init_buttons();}

//===========================================
//	PLAY MODES
//===========================================
    
    //run game normally
    void play();

    //run game with ai
    void play(ai_player);

    //run game with ai and collect data
    void play(ai_player,int i);

    //run game with ai and collect data on certain level
    void play(ai_player,int, int, int, std::string f = "voltorb_data");

    void play(ai_player,int, int, std::string f = "voltorb_data",std::string mode = "visual");

//===========================================
//	PLAY OUTCOMES
//===========================================
    
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

    //reset game
    void reset();

//===========================================
//	STATISTICS
//===========================================

    //win stats
    void winrate();
    void board_stats(){b.board_stats();
                       b.active_all();
                       b.print_board();}

//===========================================
//	ACCESSORS
//===========================================

    int get_wins(){return wins;}
    int get_loses(){return loses;}

    board get_board(){return b;}
    board* get_b_ptr(){return b_ptr;}

//===========================================
//	PROCCESS Event 
//===========================================
    void update();
    void onNotify(sf::RenderWindow& window, int event) override;

//===========================================
//	Draw
//===========================================
    void draw(sf::RenderWindow& window);

//===========================================
//	GAME STATES
//===========================================

    int start(); 
    int idle();
    int end();
    int lost();
    int won();
    int completed();

    int(game::*IDLE_ST)() = &game::idle;
    int(game::*END_ST)() = &game::end;
    int(game::*START_ST)() = &game::start;
    int(game::*LOST_ST)() = &game::lost;
    int(game::*WON_ST)() = &game::won;
    int(game::*COMPLETED_ST)() = &game::completed;

enum State {START, IDLE, END, LOST, WON, COMPLETED};
private:
    std::vector<int(game::*)()> _s = {START_ST, IDLE_ST, END_ST, LOST_ST, WON_ST, COMPLETED_ST};

    int cur_ST;     //current State
    int cur_EV;     //current Event

    interface_drw _interface;
    side_info_drw _side;
    
    //cursor dependents
    cursor_drw _cursor;
    board_drw _board;
    std::vector<button_drw*> _buttons;


public:

void init_cursor();

void init_board();

button_drw* play_button();

button_drw* play_again_button();

button_drw* quit_button();

void update_score(bool cheat = false);

bool win_cond();

bool lose_cond();

void flip_tile(bool debug = false);

void init_buttons();

enum INTERFACE {NON,TITLE,LOSE,WIN,COMPLETE};
enum BUTTONS {PLAY, PLAY_AGAIN, QUIT};

void set_interface(int cur=INTERFACE::NON, int alpha = 225);

};



#endif
