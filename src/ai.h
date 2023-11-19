#ifndef AI_H
#define AI_H

#include <iostream>
#include <iomanip>


class ai_player{
	int choice[25];
	int used;
	//data collector;

	public:
	ai_player(){
		init_choice();
		used = 1;
	}
	
    //reset choice arr
	void init_choice();

    //get unused index
	int get_index();

    //reset used
	void reset();

	//void set_collector(board& b);

};



#endif