#include "drawable.h"

void side_info_drw::set_file(std::string f){
    file = f;
    if(!texture.loadFromFile(file)){
       std::cout<< f <<" screen failed to load";
    }
}

void side_info_drw::set_side_info(board* b){
    cp = b->get_cp();
    cb = b->get_cb();
    rp = b->get_rp();
    rb = b->get_rb();
}

void side_info_drw::draw_border_side(int start_x, int start_y, sf::RenderWindow& window){
    sf::RectangleShape r;
    int off = 15; //offset -> offset right away from board (+x)
    for(int i=0; i<5; i++){
    r.setPosition(sf::Vector2f(start_x+off,(i*200)+start_y));
    r.setSize(sf::Vector2f(200,200));
    r.setFillColor(GRID_GREY);
    window.draw(r);
}
    
    r.setTexture(&texture);
    r.setFillColor(sf::Color::White);
    for(int i=0; i<BOARD_N; i++){

        int tile_size = TILE_SIZE,
            m = tile_size/2;
        
        //top border
        r.setPosition(sf::Vector2f(start_x+off,(i*tile_size)+start_y));
        r.setSize(sf::Vector2f(tile_size,m));
        r.setTextureRect(sf::IntRect(0,100,tile_size,m));
        window.draw(r);
        
        //bottom border
        r.setPosition(sf::Vector2f(start_x+off,(i*tile_size+m)+start_y));
        r.setSize(sf::Vector2f(tile_size,m));
        r.setTextureRect(sf::IntRect(200,100,tile_size,m));
        window.draw(r);
        
        //voltorb
        r.setPosition(sf::Vector2f(start_x+off,(i*tile_size+m)+start_y));
        r.setSize(sf::Vector2f(m,m));
        r.setTextureRect(sf::IntRect(10*100,0,m,m));
        window.draw(r);

        //bombs
        r.setPosition(sf::Vector2f(start_x+m+off,(i*tile_size+m)+start_y));
        r.setSize(sf::Vector2f(m,m));
        r.setTextureRect(sf::IntRect((rb[i])*100,0,m,m));
        window.draw(r);
        
        //pts right
        r.setPosition(sf::Vector2f(start_x+m+off,(i*tile_size)+start_y));
        r.setSize(sf::Vector2f(m,m));
        r.setTextureRect(sf::IntRect((rp[i]%10)*100,0,m,m));
        window.draw(r);

        //pts left
        if(rp[i]/10 >1){
        r.setPosition(sf::Vector2f(start_x+off,(i*tile_size)+start_y));
        r.setSize(sf::Vector2f(m,m));
        r.setTextureRect(sf::IntRect((rp[i]/10)*100,0,m,m));
        window.draw(r);
    }
    //---
        
    }
    }

void side_info_drw::draw_border_bot(int start_x, int start_y, sf::RenderWindow& window){
    sf::RectangleShape r;
    int off = 15; //offset -> offset down away from board (+y)
    for(int i=0; i<BOARD_N; i++){
        r.setPosition(sf::Vector2f((i*TILE_SIZE)+start_x,start_y+off));
        r.setSize(sf::Vector2f(TILE_SIZE,TILE_SIZE));
        r.setFillColor(GRID_GREY);
        window.draw(r);
    }
    r.setTexture(&texture);
    r.setFillColor(sf::Color::White);
    for(int i=0; i<5; i++){
        
        int tile_size = TILE_SIZE,
            m = tile_size/2;
        
        //top border
        r.setPosition(sf::Vector2f((i*tile_size)+start_x,start_y+off));
        r.setSize(sf::Vector2f(tile_size,m));
        r.setTextureRect(sf::IntRect(0,100,tile_size,m));
        window.draw(r);

        //bottom border 
        r.setPosition(sf::Vector2f((i*tile_size)+start_x,start_y+m+off));
        r.setSize(sf::Vector2f(tile_size,m));
        r.setTextureRect(sf::IntRect(200,100,tile_size,m));
        window.draw(r);

        //voltorb
        r.setPosition(sf::Vector2f((i*tile_size)+start_x,start_y+m+off));
        r.setSize(sf::Vector2f(m,m));
        r.setTextureRect(sf::IntRect(10*100,0,m,m));
        window.draw(r);

        //bombs
        r.setPosition(sf::Vector2f((i*tile_size)+100+start_x,start_y+m+off));
        r.setSize(sf::Vector2f(m,m));
        r.setTextureRect(sf::IntRect((cb[i])*100,0,m,m));
        window.draw(r);

        //pts right
        r.setPosition(sf::Vector2f((i*tile_size)+100+start_x,start_y+off));
        r.setSize(sf::Vector2f(m,m));
        r.setTextureRect(sf::IntRect((cp[i]%10)*100,0,m,m));
        window.draw(r);

        //pts left
        if(cp[i]/10 >1){
        r.setPosition(sf::Vector2f((i*tile_size)+start_x,start_y+off));
        r.setSize(sf::Vector2f(m,m));
        r.setTextureRect(sf::IntRect((cb[i]/10)*100,0,m,m));
        window.draw(r);
        }
        //---
    }
}