#include "drawable.h"


class cursor_drw : public drawable{
sf::RectangleShape highlight;

public:

    std::pair<int,int> pos;

    virtual void draw(sf::RenderWindow& window) override{
        window.draw(highlight);
    }

    void set_position(int x, int y){
        pos.first = x; 
        pos.second = y;
    }

    int get_x(){return pos.first;}
    int get_y(){return pos.second;}

    bool in_area(int xMin, int xMax, int yMin, int yMax){
        if(pos.first > xMin && pos.first < xMax)
            if(pos.second > yMin && pos.second < yMax)
                return true;
        return false;
    }

    void print(){
        std::cout<<"["<<pos.first<<"|"<<pos.second<<"]"<<std::endl;
    }

    void set_highlight_pos(int x, int y){
        highlight.setPosition(sf::Vector2f(x,y));
    }

    void set_highlight_size(int x, int y){
        highlight.setSize(sf::Vector2f(x,y));
    }

    void set_highlight_color(sf::Color c){
        highlight.setFillColor(c);
    }

    void hover(){
        set_highlight_pos(pos.first,pos.second);
        set_highlight_size(10,10);
        set_highlight_color(sf::Color::Red);
    }

};