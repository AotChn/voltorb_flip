#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <SFML/Graphics.hpp>
#include "constants.h"
#include "../board.h"
#include "color_constants.h"


//child of this class should end with drw suffix

class drawable{
private:
    std::pair<int,int> position;

public: 
    virtual ~drawable(){}
    virtual void draw(sf::RenderWindow&){}
    
    void set_position(int x, int y){position.first = x;position.second = y;}
    std::pair<int,int> get_position(){return position;}
    int get_x(){return position.first;}
    int get_y(){return position.second;}

};

class tile_drw : public drawable{

    sf::Color color;

public:
    virtual void draw(sf::RenderWindow& window) override{
        int dx = SCREEN_WIDTH/5, dy = SCREEN_HEIGHT/5;
        sf::RectangleShape r;
        r.setFillColor(color);
        r.setPosition(sf::Vector2f(dx*get_x(),dy*get_y()));
        r.setSize(sf::Vector2f(dx, dy));
        window.draw(r);
    }

    void set_fill(sf::Color c){
        color = c;
    }
    

};

class board_drw : public drawable{

    sf::Color color;
    int* values;
    bool active;

    int get_row(int i){
	    return floor((double)i/5);
    }

    int get_col(int i){
	    return i%5;
    }

public:
    virtual void draw(sf::RenderWindow& window) override{
        int dx = SCREEN_WIDTH/5, dy = SCREEN_HEIGHT/5;
        sf::RectangleShape r;
        for(int i=0; i<25; i++){
            switch(values[i]){
			case 0:
				color = PATH_RED;
				break;
			case 1:
				color = PATH_YELLOW;
				break;
			case 2:
				color = PATH_GREEN;
				break;
			case 3:
				color = SELECTED_BLUE;
				break;
			default:
				color = GRID_GREY;
				break;
		    }
            r.setFillColor(color);
            r.setPosition(sf::Vector2f(dx*get_col(i),dy*get_row(i)));
            r.setSize(sf::Vector2f(dx, dy));
            window.draw(r);
        }
        
    }

    void set_board(board* b){
        values = b->get_board_val();
        active = b->get_active();
    }
    
};

class interface_drw : public drawable{

std::string file;

public:
    virtual void draw(sf::RenderWindow& window) override{
        sf::Sprite sprite;
        sf::Texture texture;

        if(!texture.loadFromFile(file)){
            std::cout<< file <<" screen failed to load";
        }
        sprite.setPosition(sf::Vector2f(0,0));
        sprite.setTexture(texture);
        window.draw(sprite);
    }

    void set_file(std::string f){
        file = f;
    }
    
};

#endif 
