#include "cursor.h"

//===========================================
//	MUTATORS
//===========================================

void cursor_drw::set_position(int x, int y){
    pos.first = x; 
    pos.second = y;
}

void cursor_drw::set_reTexture_pos(int x, int y){
    reTexture.setPosition(sf::Vector2f(x,y));
}

void cursor_drw::set_file(std::string f){
    file = f;
    if(!texture.loadFromFile(file)){
        std::cout<< file <<" icon failed to load";
    }
}

void cursor_drw::close_on(bool t){
    active[1] = t;
}

void cursor_drw::reTexture_on(bool t){
    active[0] = t;
}


//===========================================
//	ACCESSORS
//===========================================

int cursor_drw::get_x(){
    return pos.first;}

int cursor_drw::get_y(){
    return pos.second;}

int cursor_drw::get_row(int offset){
    return floor((double)(pos.second-offset)/TILE_SIZE);
}

int cursor_drw::get_col(int offset){
    return floor((double)(pos.first-offset)/TILE_SIZE);
}

int cursor_drw::get_index(int start_x, int start_y){
    return (5*get_row(start_x))+get_col(start_y);
}
//===========================================
//	ULTILITY
//===========================================

bool cursor_drw::in_area(int xMin, int xMax, int yMin, int yMax){
    if(pos.first > xMin && pos.first < xMax)
        if(pos.second > yMin && pos.second < yMax)
            return true;
    return false;
}

void cursor_drw::close(sf::RenderWindow& window){
    window.close();
}

void cursor_drw::print(){
    std::cout<<"["<<pos.first<<"|"<<pos.second<<"]"<<std::endl;
}

void cursor_drw::print_index(){
    std::cout<<"row: "<<get_row() <<" col: "<< get_col()<<" index: "<<get_index()<<std::endl;
}

void cursor_drw::reTexturize(){
    reTexture_on(true);
    set_reTexture_pos(pos.first-31,pos.second-22);
    reTexture.setTexture(texture);
}
