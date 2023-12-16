
#include "cursor.h"


void board_drw::draw_board(sf::RenderWindow& window){
    int tile_size=BOARD_SIZE/BOARD_N,
        pos_x = BOARD_START_X,
        pos_y = BOARD_START_Y,
        total = BOARD_N*BOARD_N,
        offset=10;
    sprite.setTexture(texture);
    for(int i=0; i<total; i++){
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
            case 0: //bomb
                sprite.setTextureRect(sf::IntRect(600, 0, 200, 200));
                break;
            default:
                break;
            }
        }
        else
            sprite.setTextureRect(sf::IntRect(800, 0, 200, 200)); //unflipped
        sprite.setPosition(sf::Vector2f(tile_size*get_col(i)+pos_x,tile_size*get_row(i)+pos_y));
        window.draw(sprite);
    }
}

void board_drw::set_board(board* b){
    values = b->get_board_val();
    active = b->get_active();
}

void board_drw::set_file(std::string f){
    file = f;
    if(!texture.loadFromFile(file)){
        std::cout<< file <<" tileset failed to load";
    }
}

void board_drw::set_cursor(cursor_drw* c){
    _cursor = c;
}

bool board_drw::contains_cursor(){
if(_cursor->get_x() > BOARD_START_X && _cursor->get_x() < BOARD_START_X+BOARD_SIZE)
    if(_cursor->get_y() > BOARD_START_Y && _cursor->get_y() < BOARD_START_Y+BOARD_SIZE)
        return true;
return false;
}

void board_drw::hover(sf::RenderWindow& window){
    sf::RectangleShape border;
    int tile_size=BOARD_SIZE/BOARD_N,
        pos_x = _cursor->get_col(BOARD_START_X)*tile_size + BOARD_START_X,
        pos_y = _cursor->get_row(BOARD_START_Y)*tile_size + BOARD_START_Y,
        offset=10;

    border.setFillColor(sf::Color::Red);

    //top
    border.setPosition(sf::Vector2f(pos_x,pos_y-offset));
    border.setSize(sf::Vector2f(tile_size, offset));
    window.draw(border);
    
    //bottom
    border.setPosition(sf::Vector2f(pos_x,(pos_y+tile_size)));
    border.setSize(sf::Vector2f(tile_size, offset));
    window.draw(border);

    //right
    border.setPosition(sf::Vector2f((pos_x+tile_size),pos_y));
    border.setSize(sf::Vector2f(offset, tile_size));
    window.draw(border);

    //left
    border.setPosition(sf::Vector2f(pos_x-offset,pos_y));
    border.setSize(sf::Vector2f(offset, tile_size));
    window.draw(border);
}

int board_drw::get_row(int i){
    return floor((double)i/BOARD_N);
}

int board_drw::get_col(int i){
    return i%BOARD_N;
}

sf::RectangleShape board_drw::select(int i){
    int tile_size=BOARD_SIZE/BOARD_N,
        pos_x = BOARD_START_X,
        pos_y = BOARD_START_Y,
        total = BOARD_N*BOARD_N,
        offset=10;
    
    sf::RectangleShape r;
    r.setFillColor(sf::Color::Green);
    r.setSize(sf::Vector2f(tile_size,tile_size));
    r.setPosition(sf::Vector2f(tile_size*get_col(i)+pos_x,tile_size*get_row(i)+pos_y));
    return r;
}


void board_drw::select_on(){
    _select = true;
}


void board_drw::select_off(){
    _select = false;
}

void board_drw::set_index(int i){
    index = i;
}