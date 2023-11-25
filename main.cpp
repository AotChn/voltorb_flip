#include <iostream>
#include "src/board.h"
#include "src/game.h"
#include "src/ai/data.h"
#include <algorithm>
#include <chrono>
#include "src/graphics/window/animate.h"

int main(int argc, char **argv){
	// game voltorb;
	// ai_player william;
	// auto start = std::chrono::high_resolution_clock::now();
	// voltorb.play(william,100,5,"sample");
	// auto stop = std::chrono::high_resolution_clock::now();
	// auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

	// std::cout << "Time : "<< duration.count() << "ms" << std::endl;
	// return 0;


	animate app;
	game voltorb;
	//ai_player william;
	app.Attach(&voltorb);
	app.run();
	//voltorb.board_stats();
	//voltorb.play(william, 1, 5,0,"sample");
    std::cout << "End of Main\n";
}


