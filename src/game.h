#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <queue>
#include <vector>
#include <iomanip>
#include <stdlib.h>
#include <time.h>
#include "board.h"
#include "ai.h"
#include "data.h"
#include "graphics/window_observer.h"
#include "graphics/constants.h"
#include "graphics/color_constants.h"
#include "graphics/drawable.h"
#include "graphics/cursor.h"


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
    b_ptr = &b;}

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
    void draw_tile(sf::RenderWindow& window, int i, sf::Color c = sf::Color::Red);
    void draw_board(sf::RenderWindow& window);

//===========================================
//	GAME STATES
//===========================================

    int start(); 
    int idle();
    int end();
    int lost();

    int(game::*IDLE_ST)() = &game::idle;
    int(game::*END_ST)() = &game::end;
    int(game::*START_ST)() = &game::start;
    int(game::*LOST_ST)() = &game::lost;


//===========================================
//	INTERFACE
//===========================================

enum State {START, IDLE, END, LOST};
private:
    std::vector<int(game::*)()> _s = {START_ST, IDLE_ST, END_ST, LOST_ST};

    int cur_ST;     //current State
    int cur_EV;     //current Event

    tile_drw _tile;
    board_drw B;
    interface_drw _interface;
    cursor_drw _cursor;
    side_info_draw _side;
    button_drw _button;
};



#endif



// void Animate::load_help_screen(){
//     if(!texture.loadFromFile("sprites/help_menu.png")){
//         cout<<"help screen failed to load";
//     }
//     sprite.setPosition(sf::Vector2f(250,168));
//     sprite.setTexture(texture);
//     window.draw(sprite);
// } 