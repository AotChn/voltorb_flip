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
    bool* active;
    std::string file;

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
        sf::Texture texture;
        sf::Sprite sprite;
        if(!texture.loadFromFile(file)){
            std::cout<< file <<" tileset failed to load";
        }
        sprite.setTexture(texture);
        for(int i=0; i<25; i++){
            if(active[i]){
                switch(values[i]){
                case 1:
                    sprite.setTextureRect(sf::IntRect(0, 0, 200, 200));
                    break;
                case 2:
                    sprite.setTextureRect(sf::IntRect(200, 0, 200, 200));
                    break;
                case 3:
                    sprite.setTextureRect(sf::IntRect(400, 0, 200, 200));
                    break;
                case 0:
                    sprite.setTextureRect(sf::IntRect(600, 0, 200, 200));
                    break;
                default:
                    break;
                }
            }
            else
                sprite.setTextureRect(sf::IntRect(800, 0, 200, 200));
            sprite.setPosition(sf::Vector2f(dx*get_col(i),dy*get_row(i)));
            window.draw(sprite);
        }
        
    }

    void set_board(board* b){
        values = b->get_board_val();
        active = b->get_active();
    }

    void set_file(std::string f){
        file = f;
    }
    
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

class side_info_draw : public drawable{
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
    draw_border_bot(SCREEN_HEIGHT, SCREEN_WIDTH, window);
    draw_border_side(SCREEN_HEIGHT, SCREEN_WIDTH, window);
}

void set_file(std::string f){
    if(!texture.loadFromFile(file)){
       std::cout<< f <<" screen failed to load";
    }
    file = f;
}

void set_side_info(board* b){
    cp = b->get_cp();
    cb = b->get_cb();
    rp = b->get_rp();
    rb = b->get_rb();
}

void draw_border_side(int start_x, int start_y, sf::RenderWindow& window){
    sf::RectangleShape r;
    for(int i=0; i<5; i++){
    r.setPosition(sf::Vector2f(start_x,(i*200)));
    r.setSize(sf::Vector2f(200,200));
    r.setFillColor(ROSEMARY_GREEN);
    window.draw(r);
}
    
    r.setTexture(&texture);
    r.setFillColor(sf::Color::White);
    for(int i=0; i<5; i++){

        int tile_size = 200,
            m = tile_size/2,
            off = 10; //offset -> offset right away from board (+x)
        
        //top border
        r.setPosition(sf::Vector2f(start_x+off,(i*tile_size)));
        r.setSize(sf::Vector2f(tile_size,m));
        r.setTextureRect(sf::IntRect(0,100,tile_size,m));
        window.draw(r);
        
        //bottom border
        r.setPosition(sf::Vector2f(start_x+off,(i*tile_size+m)));
        r.setSize(sf::Vector2f(tile_size,m));
        r.setTextureRect(sf::IntRect(200,100,tile_size,m));
        window.draw(r);
        
        //voltorb
        r.setPosition(sf::Vector2f(start_x+off,(i*tile_size+m)));
        r.setSize(sf::Vector2f(m,m));
        r.setTextureRect(sf::IntRect(10*100,0,m,m));
        window.draw(r);

        //bombs
        r.setPosition(sf::Vector2f(start_x+m+off,(i*tile_size+m)));
        r.setSize(sf::Vector2f(m,m));
        r.setTextureRect(sf::IntRect((rb[i])*100,0,m,m));
        window.draw(r);
        
        //pts right
        r.setPosition(sf::Vector2f(start_x+m+off,(i*tile_size)));
        r.setSize(sf::Vector2f(m,m));
        r.setTextureRect(sf::IntRect((rp[i]%10)*100,0,m,m));
        window.draw(r);

        //pts left
        if(rp[i]/10 >1){
        r.setPosition(sf::Vector2f(start_x+off,(i*tile_size)));
        r.setSize(sf::Vector2f(m,m));
        r.setTextureRect(sf::IntRect((rp[i]/10)*100,0,m,m));
        window.draw(r);
    }
    //---
        
    }
    }

void draw_border_bot(int start_x, int start_y, sf::RenderWindow& window){
    sf::RectangleShape r;
    for(int i=0; i<5; i++){
        r.setPosition(sf::Vector2f((i*200),start_y));
        r.setSize(sf::Vector2f(200,200));
        r.setFillColor(ROSEMARY_GREEN);
        window.draw(r);
    }
    r.setTexture(&texture);
    r.setFillColor(sf::Color::White);
    for(int i=0; i<5; i++){
        
        int tile_size = 200,
            m = tile_size/2,
            off = 10; //offset -> offset down away from board (+y)
        
        //top border
        r.setPosition(sf::Vector2f((i*tile_size),start_y+off));
        r.setSize(sf::Vector2f(tile_size,m));
        r.setTextureRect(sf::IntRect(0,100,tile_size,m));
        window.draw(r);

        //bottom border 
        r.setPosition(sf::Vector2f((i*tile_size),start_y+m+off));
        r.setSize(sf::Vector2f(tile_size,m));
        r.setTextureRect(sf::IntRect(200,100,tile_size,m));
        window.draw(r);

        //voltorb
        r.setPosition(sf::Vector2f((i*tile_size),start_y+m+off));
        r.setSize(sf::Vector2f(m,m));
        r.setTextureRect(sf::IntRect(10*100,0,m,m));
        window.draw(r);

        //bombs
        r.setPosition(sf::Vector2f((i*tile_size)+100,start_y+m+off));
        r.setSize(sf::Vector2f(m,m));
        r.setTextureRect(sf::IntRect((cb[i])*100,0,m,m));
        window.draw(r);

        //pts right
        r.setPosition(sf::Vector2f((i*tile_size)+100,start_y+off));
        r.setSize(sf::Vector2f(m,m));
        r.setTextureRect(sf::IntRect((cp[i]%10)*100,0,m,m));
        window.draw(r);

        //pts left
        if(cp[i]/10 >1){
        r.setPosition(sf::Vector2f((i*tile_size),start_y+off));
        r.setSize(sf::Vector2f(m,m));
        r.setTextureRect(sf::IntRect((cb[i]/10)*100,0,m,m));
        window.draw(r);
        }
        //---
    }
};



};

#endif 
