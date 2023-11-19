#include <iostream>
#include "src/board.h"
#include "src/game.h"
#include "src/data.h"


int main(int argc, char **argv){
	game voltorb;
	ai_player william;
	voltorb.play(william,5000,5);
	return 0;
}
