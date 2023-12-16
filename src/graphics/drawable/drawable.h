#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <SFML/Graphics.hpp>
#include "../../board.h"
#include "../window/color_constants.h"
#include "../window/constants.h"


/**-----*-----*-----*-----*-----*-----*-----*-----*
CLASS : 
function: parent class of items that can be drawn in game
//child of this class should end with drw suffix

*-----*-----*-----*-----*-----*-----*-----*-----**/
class drawable{
private:
    int _type;

public: 
    drawable(){_type = 0;}
    virtual ~drawable(){}
    virtual void draw(sf::RenderWindow&){}

    virtual int get_type(){return _type;}
    virtual void set_type(int t){_type = t;}

};

class interface_drw : public drawable{

std::string file;
int alpha;

public:
    virtual void draw(sf::RenderWindow& window) override{
        sf::Sprite sprite;
        sf::Texture texture;

        if(!texture.loadFromFile(file)){
            std::cout<< file <<" screen failed to load";
        }
        
        sprite.setScale(1.5,1.5);

        sprite.setPosition(sf::Vector2f(0,0));
        sprite.setTexture(texture);
        sprite.setColor(sf::Color(255,255,255,alpha));
        window.draw(sprite);
    }

    void set_file(std::string f, int a = 255){
        file = f;
        alpha = a;
    }
    
};

class side_info_drw : public drawable{
sf::Sprite sprite;
sf::Texture texture;
std::string file;
sf::Color colors[5] = {LINE_RED,LINE_YELLOW,LINE_GREEN,LINE_BLUE,LINE_PURPLE};
int* cp;
int* cb;
int* rp;
int* rb;
        
public: 
virtual void draw(sf::RenderWindow& window) override{
    draw_border_bot(BOARD_START_X, BOARD_SIZE+BOARD_START_Y, window);
    draw_border_side(BOARD_SIZE+BOARD_START_X, BOARD_START_Y, window);
}

void set_file(std::string f);

//initalize the data from board
void set_side_info(board* b);

//draw info to the right side of board
void draw_border_side(int start_x, int start_y, sf::RenderWindow& window);

//draw info to the bottom side of board
void draw_border_bot(int start_x, int start_y, sf::RenderWindow& window);

};

class text_drw : public drawable{
sf::Text text;
sf::Font font; 
int x,
    y,
    size;
std::string file,
            str; 

public:
virtual void draw(sf::RenderWindow& window) override{
    window.draw(text);
}

void set_file(std::string f){
    file = f;
    if(!font.loadFromFile(file)){
       std::cout<< f <<" font failed to load";
    }
    text.setFont(font);
}

void set_pos(int i, int j){
    x = i;
    y = j;
    text.setPosition(sf::Vector2f(x,y));
}

void set_size(int s){
    size = s;
    text.setCharacterSize(s);
}

void set_str(std::string s){
    text.setString(s);
}

void set_color(sf::Color c){
    text.setFillColor(c);
}
};

#endif 
