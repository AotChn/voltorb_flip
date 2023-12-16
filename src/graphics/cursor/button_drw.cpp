#include "cursor.h"


void button_drw::draw(sf::RenderWindow& window){
    button.setFillColor(color);
    button.setPosition(sf::Vector2f(xMin,yMin));
    button.setSize(sf::Vector2f((xMax-xMin),(yMax-yMin)));
    window.draw(button);
    
    if(contains_cursor())
        hover();
    else
        idle();
    button.setTexture(&texture);
    button.setFillColor(sf::Color(255,255,255,alpha));
    button.setTextureRect(sf::IntRect(t_x,t_y,t_size_x,t_size_y));
    window.draw(button);
}

void button_drw::set_color(sf::Color c){
    color = c;
}

void button_drw::set_cursor(cursor_drw* cursor){
    _cursor = cursor;
}

void button_drw::set_file(std::string file){
    if(!texture.loadFromFile(file)){
       std::cout<< file <<" button failed to load";
    }
}

void button_drw::set_param(int xmin, int xmax, int ymin, int ymax){
    xMin = xmin; 
    xMax = xmax; 
    yMin = ymin; 
    yMax = ymax;
    t_size_x = xMax-xMin;
    t_size_y = yMax-yMin;
}

void button_drw::set_pos(int i, int j){
    xMin = i;
    yMin = j;
    button.setPosition(sf::Vector2f(xMin,yMin));
}

void button_drw::set_pos_by_prop(int x, int y, int x_prop, int y_prop){
    xMin = x * x_prop;
    yMin = y * y_prop;
    button.setPosition(sf::Vector2f(xMin,yMin));
}

void button_drw::set_size_by_prop(int x, int y, int x_prop, int y_prop){
    xMax = xMin+(x*x_prop);
    yMax = yMin+(y*y_prop);
    button.setSize(sf::Vector2f(xMax-xMin,yMax-yMin));
}

void button_drw::set_size(int i, int j){
    xMax = xMin+i;
    yMax = yMin+j;
    button.setSize(sf::Vector2f(xMax-xMin,yMax-yMin));
}

void button_drw::set_alpha(int a){
    alpha = a;
}

void button_drw::idle(){ //dark
    set_alpha(225);
}

void button_drw::hover(){ //medium
    set_alpha(125);
}

void button_drw::click(){ //lightest
    set_alpha(95);
}

bool button_drw::contains_cursor(){
    if(_cursor->get_x() > xMin && _cursor->get_x() < xMax)
        if(_cursor->get_y() > yMin && _cursor->get_y() < yMax)
            return true;
    return false;
}

void button_drw::set_t(int x, int y){
    t_x = x;
    t_y = y;
}

void button_drw::set_scale(double s){
    scale = s;
    xMax = xMin + ((xMax-xMin)*scale);
    yMax = yMin + ((yMax-yMin)*scale);
}   

void button_drw::set_texture_params(int x, int y, int s_x, int s_y){
    t_x = x;
    t_y = y;
    t_size_x = s_x;
    t_size_y = s_y;
}

button_drw& button_drw::operator=(const button_drw& RHS){
    xMin = RHS.xMin;
    xMax = RHS.xMax;
    yMin = RHS.yMin;
    yMax = RHS.yMax;
    alpha = RHS.alpha;
    t_x = RHS.t_x;
    t_y = RHS.t_y;
    t_size_x = RHS.t_size_x;
    t_size_y = RHS.t_size_y;
    scale = RHS.scale;
    texture = RHS.texture;
    button = RHS.button;
    color = RHS.color;
    _cursor = RHS._cursor;

    return *this;

}

