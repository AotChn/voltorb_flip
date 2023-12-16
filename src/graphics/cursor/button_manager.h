#ifndef BUTTON_MANAGER_H
#define BUTTON_MANAGER_H

#include "cursor.h"
#include <vector>

struct button_info{

int pos_x, 
    pos_y,
    size_x, 
    size_y,
    alpha, //alpha level of button
    t_x=0, //where in sprite sheet x
    t_y=0, //where in sprite sheet y
    t_size_x, //size of texture in sprite sheet x
    t_size_y; //size of texture in sprite sheet y
    
double scale = 1; //scales the size of the button
sf::Color color;

//===========================================
//	MUTATORS
//===========================================
void set_position(int x, int y);
void set_size(int x, int y);
void set_alpha(int a);
void set_sprite_sheet(int x, int y, int s_x, int s_y);
void set_scale(int s);
void set_color(sf::Color c);
//===========================================
//	BUTTON STATES
//===========================================
void idle();
void hover();
void click();
bool contains_cursor();


};

class button_manager : public drawable{


cursor_drw cursor;
sf::Texture texture;
sf::RectangleShape button;
std::vector<button_info> buttons;
int index;

public: 

virtual void draw(sf::RenderWindow& window) override{
    set_rectangle(index);
    window.draw(button);
}

//===========================================
//	MUTATORS
//===========================================
void set_texture();
void set_cursor();
void set_rectangle(int index);
//===========================================
//	UTILITY
//===========================================
void add_button(button_info b);



}

















#endif