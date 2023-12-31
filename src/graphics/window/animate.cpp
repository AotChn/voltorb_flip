#include "animate.h"

animate::animate(){
    window.create(sf::VideoMode(1500,1500),"VOLTORB FLIP");
    window.setFramerateLimit(60);
    // sf::Mouse::setPosition(sf::Vector2i(0,0), window);
}

void animate::run(){
    while(window.isOpen()){
        process_events();
        update();
        render();
    }
}

void animate::render(){
    window.clear(BACKGROUND_DARK);
    draw();
    window.display();
}

void animate::draw(){
    Notify(window, Draw);
}

void animate::update(){
}

void animate::process_events(){
    sf::Event event;
    int key = event.key.code;
    if(window.pollEvent(event)){
        switch(event.type){
        case sf::Event::Closed:
            window.close();
            break;
        default:
            Notify(window, event.type);
        break;
        }
    }
    else Notify(window, CUSTOM_SFEV::Idle);  
}

