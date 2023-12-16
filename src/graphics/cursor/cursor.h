#ifndef CURSOR_H
#define CURSOR_H

#include "../drawable/drawable.h"
#include "math.h"

//drawables that depend on cursor information


/**-----*-----*-----*-----*-----*-----*-----*-----*
CLASS : cursor_drw
function: handles the position of cursor and other
        other cursor functions

*-----*-----*-----*-----*-----*-----*-----*-----**/
class cursor_drw : public drawable{
    
    sf::RectangleShape highlight;
    sf::Sprite reTexture;
    sf::Texture texture;
    std::string file;
    bool active[2] = {false,false};
    std::pair<int,int> pos;

public:


    virtual void draw(sf::RenderWindow& window) override{
        if(active[0]){
            window.setMouseCursorVisible(false);
            window.draw(reTexture);
        }
        if(active[1])
            close(window);
    }

cursor_drw& operator=(const cursor_drw& RHS){
    highlight = RHS.highlight;
    reTexture = RHS.reTexture;
    texture = RHS.texture;
    file = RHS.file;
    pos = RHS.pos;
    active[0] = RHS.active[0];
    active[1] = RHS.active[1];
    return *this;
}

//===========================================
//	MUTATORS
//===========================================
    
    //sets the position of the cursor respect to window
    void set_position(int x, int y);

    //sets the file for the texture of the cursor
    void set_file(std::string f);

    //set the postiion of the cursor retexture
    void set_reTexture_pos(int x, int y);

    //toggles window close
    void close_on(bool t);
   
    //toggle cursor texture 
    void reTexture_on(bool t);
//===========================================
//	ACCESSORS
//===========================================

    //get x position of cursor respect to window
    int get_x();
    
    //get y position of cursor respect to window
    int get_y();

    //get row of nxn board based on cursor pos
    int get_row(int offset=0);

    //get col of nxn board based on cursor pos
    int get_col(int offset=0);

    //get index of a tile based on cursor pos
    int get_index(int start_x=BOARD_START_X, int start_y=BOARD_START_Y);

//===========================================
//	ULTILITY
//===========================================

    //checks if cursor is within a rectanglar area
    bool in_area(int xMin, int xMax, int yMin, int yMax);

    //changes texture of cursor
    void reTexturize();

    //closes window close
    void close(sf::RenderWindow& window);

    //prints pos of cursor respect to window
    void print();

    //prints row, col, index of cursor respect to board
    void print_index();

};

/**-----*-----*-----*-----*-----*-----*-----*-----*
CLASS : button_drw
function: handles the creation and drawing of buttons
        that will be interacted with

*-----*-----*-----*-----*-----*-----*-----*-----**/
class button_drw : public drawable{

int xMin, 
    xMax,
    yMin, 
    yMax,
    alpha, //alpha level of button
    t_x=0, //where in sprite sheet x
    t_y=0, //where in sprite sheet y
    t_size_x, //size of texture in sprite sheet x
    t_size_y; //size of texture in sprite sheet y
    
double scale = 1; //scales the size of the button

sf::Texture texture;
sf::RectangleShape button;
sf::Color color;

cursor_drw* _cursor;

public:

button_drw(){set_type(1);}
~button_drw(){};
button_drw(cursor_drw* c){_cursor = c;set_type(1);}
button_drw& operator=(const button_drw& RHS);

virtual void draw(sf::RenderWindow& window) override;

//===========================================
//	ACCESSORS
//===========================================

//sets the backdrop color of the button
void set_color(sf::Color c);

//sets the cursor to use
void set_cursor(cursor_drw* cursor);

//sets the file for the texture 
void set_file(std::string file);

//sets the rectangular area of the button
void set_param(int xmin, int xmax, int ymin, int ymax);

//sets the top left corner pos of the button
void set_pos(int i, int j);

//sets the position by a proportion resepct to x and y 
void set_pos_by_prop(int x, int y, int x_prop, int y_prop);

//sets the size by a proportion respect to x and y
void set_size_by_prop(int x, int y, int x_prop, int y_prop);

//sets the size of the rectangle 
void set_size(int i, int j);

//set the tranparency of the button
void set_alpha(int a);

//sets where on the sprite sheet the texture is
void set_t(int x, int y);

//scales the button by s 
void set_scale(double s);

//sets how large the texture on the sprite sheet is and where it is
void set_texture_params(int x, int y, int s_x, int s_y);

//===========================================
//	BUTTON STATES
//===========================================

//button it neither hovered nor pressed
void idle();

//button is being hovered
void hover();

//button is being clicked
void click();

//check if button has a cursor within params
bool contains_cursor();

};

/**-----*-----*-----*-----*-----*-----*-----*-----*
CLASS : board_drw
function: 
    handles the drawing of board and tile 
    highlighting
*-----*-----*-----*-----*-----*-----*-----*-----**/
class board_drw : public drawable{

    sf::Color color;
    int* values;
    bool* active;
    std::string file;
    cursor_drw* _cursor;
    sf::Texture texture;
    sf::Sprite sprite;
    bool _select;
    int index;

public:
    virtual void draw(sf::RenderWindow& window) override{
        draw_board(window);
        if(contains_cursor())
            hover(window);
        if(_select)
            window.draw(select(index));
        select_off();
    }
;
//===========================================
//	MUTATORS
//===========================================
    
    //get board information to draw
    void set_board(board* b);

    //sets the file of the texture
    void set_file(std::string f);

    //sets the cursor to use
    void set_cursor(cursor_drw* c);

    //selects an index to be highlighted
    void set_index(int i);

//===========================================
//	UTILITY
//===========================================
    
    //checks if cursor is within board
    bool contains_cursor();

    //highlight tile cursor is on 
    void hover(sf::RenderWindow& window);
    
    //draws board from information
    void draw_board(sf::RenderWindow& window);

    //get row from index respect to board
    int get_row(int i);

    //get col from index respect to board
    int get_col(int i);

    //highlights the tile that is selected 
    sf::RectangleShape select(int i);

    //switches select on
    void select_on();

    //switches select off 
    void select_off();

};

#endif