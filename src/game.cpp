#include "game.h"

void game::win(){
	b.reset_c();
	b.next_level();
	std::cout<<"LEVEL : "<<b.get_level()<<" COMPLETE"<<'\n';
	wins++;
	if(b.get_level()>8)
		complete();
	score = 1;
}

void game::lose(){
	b.active_all();
	b.print_board();
	std::cout<<"YOU LOSE HAHA!"<<'\n';
	loses++;
	score = 1;
	b.reset();
}

void game::complete(){
	b.reset();
	std::cout<<"CONGRATS YOU HAVE COMPLETED ALL LEVELS!";
	wins++;
	score = 1;
}

void game::winrate(){
	std::cout<<"wins: "<<wins <<'\n';
	std::cout<<"loses: "<<loses <<'\n';
	std::cout<<"score: "<<score <<'\n';
	std::cout<<"iterations: "<<cur_it <<'\n';
}

void game::reset(){
    wins=0;
	loses=0;
	it=5000,
	score=1,
	cur_it=0;
}

void game::play(ai_player ai){
	srand(time(NULL));
	b.gen_board();

	while(cur_it != it){
		b.print_board();
		int choice = ai.get_index();

		std::cout<<"select : ";
		std::cout<<choice<<std::endl;

		score = score * b.get_val(choice);
		if(score == 0){
			lose();
			ai.reset();
			cur_it++;
		}
		if(score == b.get_coins()){
			win();
			ai.reset();
			cur_it++;
		}
	}
	winrate();
	
}

void game::play(){
	srand(time(NULL));
	b.gen_board();

	while(loses == 0 || wins > 8){
		b.print_board();
		int ans;
		std::cout<<"select : ";
		std::cin>>ans;

		int choice = ans;

		score = score * b.flip(choice);
		if(score == 0){
			lose();
		}
		if(score == b.get_coins()){
			win();
		}
	}
}