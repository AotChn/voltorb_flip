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
        comp=0,
        games,
        hold,
        target_it=10;
    std::queue<drawable*> toDraw;
    bool _ai;
    int l_tracker[8]={0,0,0,0,0,0,0,0};

public:

game() : cur_ST(0){
    score = 1;
    it = 0;
    games = 0;
    hold = 1;
    reset();
    b_ptr = &b;
    init_cursor();
    init_board();
    std::cout<<"starting it: "<<it<<"\n";}
   // init_buttons();}

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
    void stat_check();
    std::string stat_check_text();

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
    int ai_mode();
    int ai_play();

    int(game::*IDLE_ST)() = &game::idle;
    int(game::*END_ST)() = &game::end;
    int(game::*START_ST)() = &game::start;
    int(game::*LOST_ST)() = &game::lost;
    int(game::*WON_ST)() = &game::won;
    int(game::*COMPLETED_ST)() = &game::completed;
    int(game::*AI_MODE_ST)() = &game::ai_mode;
    int(game::*AI_PLAY_ST)() = &game::ai_play;

private:
    std::vector<int(game::*)()> _s = {START_ST, IDLE_ST, END_ST, 
                                      LOST_ST, WON_ST, COMPLETED_ST,
                                      AI_MODE_ST, AI_PLAY_ST};

    int cur_ST;     //current State
    int cur_EV;     //current Event

    interface_drw _interface;
    side_info_drw _side;
    
    //cursor dependents
    cursor_drw _cursor;
    board_drw _board;
    // std::vector<button_drw*> _buttons;
    //drawing text
    text_drw _text;

public:

//===========================================
//	INITILIZE
//===========================================

//sets cursor for drawables
void init_cursor();

//sets board for drawables
void init_board();

//sets up all buttons in game
void init_buttons();

//===========================================
//	DRAWABLE SETUPS
//===========================================

//button to start game
button_drw* play_button();

//button to start ai game
button_drw* ai_button();

//button to restart game
button_drw* play_again_button();

//button to quit game
button_drw* quit_button();

//chooses correct interface 
void set_interface(int cur=INTERFACE::NON, int alpha = 225);

//===========================================
//	UTILITIY
//===========================================

//update score of game
void update_score(int i=0, bool cheat = false);

//checks if win condition have been met
bool win_cond();

//checks if lose condition have been met
bool lose_cond(int i=0);

//display chosen tile on board
void flip_tile(int i=0, bool debug = false);

//===========================================
//	ENUMS
//===========================================

enum State {START, IDLE, END, LOST, WON, COMPLETED, AI_MODE, AI_PLAY};
enum INTERFACE {NON, TITLE, LOSE, WIN, COMPLETE};
enum BUTTONS {PLAY, PLAY_AGAIN, QUIT};


};




#endif
