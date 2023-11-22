#include "drawable.h"
#include "math.h"


class cursor_drw : public drawable{
    sf::RectangleShape highlight;
    sf::Sprite _hover;
    sf::Texture texture;
    std::string file;
    bool active[2] = {false,false};

public:

    std::pair<int,int> pos;

    virtual void draw(sf::RenderWindow& window) override{
        if(active[0]){
            window.setMouseCursorVisible(false);
            window.draw(_hover);
        }
        if(active[1])
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

    void set_hover_pos(int x, int y){
        _hover.setPosition(sf::Vector2f(x,y));
    }

    void hover_on(bool t){
        active[0] = t;
    }

    void highlight_on(bool t){
        active[1] = t;
    }

    void hover(){
        hover_on(true);
        set_hover_pos(pos.first-50,pos.second-50);
        if(!texture.loadFromFile(file)){
            std::cout<< file <<" icon failed to load";
        }
        _hover.setTexture(texture);
    }

    void set_file(std::string f){
        file = f;
    }

    void tile_highlight(int ){

    }

    int get_row(){
	    return floor((double)pos.second/200);
    }

    int get_col(){
	    return floor((double)pos.first/200);
    }

    int get_index(){
        return (5*get_row())+get_col();
    }

    void print_index(){
        std::cout<<"row: "<<get_row() <<" col: "<< get_col()<<" index: "<<get_index()<<std::endl;
    }
};

class button_drw : public drawable{

int xMin, 
    xMax,
    yMin, 
    yMax,
    alpha,
    t_x, //where in sprite sheet x
    t_y; //where in sprite sheet y

sf::Texture texture;
sf::RectangleShape button;
sf::Color color;

cursor_drw* _cursor;

public:
    virtual void draw(sf::RenderWindow& window) override{
        if(contains_cursor())
            hover();
        else
            idle();
        //button.setTexture(&texture);
        button.setFillColor(sf::Color(255,255,255,alpha));
        button.setPosition(sf::Vector2f(xMin,yMin));
        button.setSize(sf::Vector2f(xMax-xMin,yMax-yMin));
        //button.setTextureRect(sf::IntRect(t_x,t_y,xMax-xMin,yMax-yMin));
        window.draw(button);
    }


void set_color(sf::Color c){
    color = c;
}

void set_cursor(cursor_drw* cursor){
    _cursor = cursor;
}

void set_file(std::string file){
    if(!texture.loadFromFile(file)){
       std::cout<< file <<" button failed to load";
    }
}

void set_param(int xmin, int xmax, int ymin, int ymax){
    xMin = xmin; 
    xMax = xmax; 
    yMin = ymin; 
    yMax = ymax;
}

void set_pos(int i, int j){
    xMin = i;
    yMin = j;
    button.setPosition(sf::Vector2f(xMin,yMin));
}

void set_pos_by_prop(int x, int y, int x_prop, int y_prop){
    xMin = x * x_prop;
    yMin = y * y_prop;
    button.setPosition(sf::Vector2f(xMin,yMin));
}

void set_size_by_prop(int x, int y, int x_prop, int y_prop){
    xMax = xMin+(x*x_prop);
    yMax = yMin+(y*y_prop);
    button.setSize(sf::Vector2f(xMax-xMin,yMax-yMin));
}

void set_size(int i, int j){
    xMax = xMin+i;
    yMax = yMin+j;
    button.setSize(sf::Vector2f(xMax-xMin,yMax-yMin));
}

void set_alpha(int a){
    alpha = a;
}

void idle(){ //dark
    set_alpha(225);
}

void hover(){ //medium
    set_alpha(125);
}

void click(){ //lightest
    set_alpha(95);
}

bool contains_cursor(){
    if(_cursor->get_x() > xMin && _cursor->get_x() < xMax)
        if(_cursor->get_y() > yMin && _cursor->get_y() < yMax)
            return true;
    return false;
}

void set_t(int x, int y){
    t_x = x;
    t_y = y;
}

};