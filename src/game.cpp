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

void game::win(int l){
	b.reset_l(l);
	std::cout<<"LEVEL : "<<b.get_level()<<" COMPLETE"<<'\n';
	wins++;
	score = 1;
	if(b.get_level()>8)
		complete();
}

void game::lose(){
	b.active_all();
	b.print_board();
	std::cout<<"YOU LOSE HAHA!"<<'\n';
	loses++;
	score = 1;
	b.reset();
}

void game::lose(int l){
	b.active_all();
	b.print_board();
	std::cout<<"YOU LOSE HAHA!"<<'\n';
	loses++;
	score = 1;
	b.reset_l(l);
}



void game::complete(){
	std::cout<<"CONGRATS YOU HAVE COMPLETED ALL LEVELS!";
	wins++;
	score = 1;
	comp++;
	b.reset_l(1);
}

void game::winrate(){
	std::cout<<"wins: "<<wins <<'\n';
	std::cout<<"loses: "<<loses <<'\n';
	std::cout<<"score: "<<score <<'\n';
	std::cout<<"iterations: "<<cur_it <<'\n';
	std::cout<<"completed sessions: "<<comp<<'\n';
}

void game::reset(){
    wins=0;
	loses=0;
	it=1,
	score=1,
	cur_it=0;
	srand(time(NULL));
	b.gen_board();
}

void game::play(ai_player ai){
	b.gen_board();

	while(cur_it != it){
		b.print_board();
		b.fill_data();
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

void game::play(ai_player ai,int i){
	srand(time(NULL));
	b.gen_board();
	collector.set_board(b);

	while(cur_it != i){
		b.print_board();
		b.fill_data();
		int choice = ai.get_index();

		std::cout<<"select : ";
		std::cout<<choice<<std::endl;

		score = score * b.get_val(choice);
		if(score == 0){
			lose();
			ai.reset();
			cur_it++;
			collector.write_data();
		}
		if(score == b.get_coins()){
			win();
			ai.reset();
			cur_it++;
			collector.write_data();
		}
	}
	winrate();
	
}

void game::play(ai_player ai,int i, int l, int y,std::string f){
	srand(time(NULL));
	b.gen_board();
	collector.set_board(b);
	bool new_game = true;

	ai.sorter(this->get_b_ptr());
	while(cur_it != i){
		b.print_board();
		b.fill_data();
		if(new_game)
			ai.sorter(this->get_b_ptr());
		int choice = ai.get_index(1);

		std::cout<<"select : ";
		std::cout<<choice<<std::endl;

		score = score * b.flip(choice);
		new_game = false;
		if(score == 0){
			lose(1);
			cur_it++;
			collector.write_data(f);
			new_game = true;
		}
		if(score == b.get_coins()){
			win(b.get_level()+1);
			cur_it++;
			collector.write_data(f);
			new_game = true;
		}
	}
	winrate();
}

void game::update(){
	cur_ST = (this->*_s[cur_ST])();
}

void game::onNotify(sf::RenderWindow& window, int event){
	cur_EV = event;
	switch (event)
    {
		case CUSTOM_SFEV::Draw:
			draw(window);
			return;
		break;
		case CUSTOM_SFEV::Close:
			window.close();
		break;
        case sf::Event::MouseButtonPressed:{

                break;
            }
        case sf::Event::MouseButtonReleased:{

                break;
            }   
        case sf::Event::MouseMoved:{
				 _cursor.set_position(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
                break;
            }
    
    default:
		cur_EV = CUSTOM_SFEV::Idle;
        break;
    }
    update();
}

void game::draw(sf::RenderWindow& window){
	while(!toDraw.empty()){
            toDraw.front()->draw(window);
            toDraw.pop();
        }
}


void game::draw_tile(sf::RenderWindow& window, int i, sf::Color c){
	sf::RectangleShape r;
	r.setPosition(sf::Vector2f(b.get_col(i)*(SCREEN_WIDTH/5),b.get_row(i)*(SCREEN_HEIGHT/5)));
    r.setSize(sf::Vector2f(SCREEN_WIDTH/5,SCREEN_HEIGHT/5));
	r.setFillColor(c);
	window.draw(r);
}

void game::draw_board(sf::RenderWindow& window){
	for(int i=0; i<25; i++){
		switch(b.get_val(i)){
			case 0:
				draw_tile(window, i, PATH_RED);
				break;
			case 1:
				draw_tile(window, i, PATH_YELLOW);
				break;
			case 2:
				draw_tile(window, i, PATH_GREEN);
				break;
			case 3:
				draw_tile(window, i, SELECTED_BLUE);
				break;
			default:
				draw_tile(window, i, GRID_GREY);
				break;
		}
	}
}

int game::start(){
	srand(30);
	_button.set_cursor(&_cursor);
	_interface.set_file("../title_screen.png");
	toDraw.push(&_interface);
	//_cursor.print();
	// if(_cursor.in_area(591,853,508,646)){
	// 	_cursor.set_highlight_pos(591,508);
	// 	_cursor.set_highlight_size(260,136);
	// 	_cursor.set_highlight_color(SELECTED_BLUE);
	// 	_cursor.highlight_on(true);
	// }
	// else
	// 	_cursor.highlight_on(false);
	_cursor.set_file("../farfetch_leak.png");
	_cursor.hover();
	toDraw.push(&_cursor);

	_button.set_cursor(&_cursor);
	_button.set_color(sf::Color::Blue);
	_button.set_param(591*1.5,851*1.5,508*1.5,644*1.5);

	switch (cur_EV){
	case sf::Event::MouseButtonReleased:{
		//return IDLE;
	break;
	}
	case sf::Event::MouseButtonPressed:{
		if(_button.contains_cursor()){
			return IDLE;
		}
			
	break;
	}
	case sf::Event::MouseMoved:{
	break;
	}
	default:{

	break;
	}   

	}
	toDraw.push(&_button);
	return START;
}
int game::idle(){

	B.set_board(&b);
	B.set_file("../voltorb_tiles.png");
	_side.set_file("../voltorb_info2.png");
	_side.set_side_info(b_ptr);
	_cursor.hover();
	switch (cur_EV){
		case sf::Event::MouseButtonPressed:{
			if(_cursor.in_area(0,1000,0,1000)){
				b.set_active(_cursor.get_index(), true);
				std::cout<<b.get_val(_cursor.get_index())<<" ";
				_cursor.print_index();
				if(b.get_val(_cursor.get_index())==0){
					return LOST;
				}
			}
		break;
		}
		
		}
			
	toDraw.push(&B);
	toDraw.push(&_side);
	toDraw.push(&_cursor);
	return IDLE;
}

int game::lost(){
	b.active_all();
	_cursor.hover();
	_interface.set_file("../Lose_screen1.png",100);
	toDraw.push(&B);
	toDraw.push(&_cursor);
	toDraw.push(&_interface);
	switch (cur_EV){
		case sf::Event::MouseButtonPressed:{
			return END;
		}
	
	}
	return LOST;
}

int game::end(){
	_interface.set_file("../Lose_screen1.png",255);
	toDraw.push(&_interface);
	switch (cur_EV){
		case sf::Event::MouseButtonPressed:
		break;
	}
	return END;
}

void game::play(ai_player,int, int, std::string f,std::string mode){
	srand(time(NULL));
	while(cur_ST != END){

	}

}




// b.gen_board();
// 	collector.set_board(b);
// 	bool new_game = true;

// 	ai.sorter(this->get_b_ptr());
// 	while(cur_it != i){
// 		b.print_board();
// 		b.fill_data();
// 		if(new_game)
// 			ai.sorter(this->get_b_ptr());
// 		int choice = ai.get_index(1);

// 		std::cout<<"select : ";
// 		std::cout<<choice<<std::endl;

// 		score = score * b.flip(choice);
// 		new_game = false;
// 		if(score == 0){
// 			lose(1);
// 			cur_it++;
// 			collector.write_data(f);
// 			new_game = true;
// 		}
// 		if(score == b.get_coins()){
// 			win(b.get_level()+1);
// 			cur_it++;
// 			collector.write_data(f);
// 			new_game = true;
// 		}
// 	}
// 	winrate();

//get the current tile info

