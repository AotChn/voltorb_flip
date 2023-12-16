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
	//b.print_board();
	//std::cout<<"YOU LOSE HAHA!"<<'\n';
	score = 1;
	b.reset_l(l);
}



void game::complete(){
	//std::cout<<"CONGRATS YOU HAVE COMPLETED ALL LEVELS!";
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
		drawable* d = toDraw.front(); 
		d->draw(window);
		toDraw.pop();
		if(d->get_type()==1){ //button
			delete d;
		}
    }
}

int game::start(){

	button_drw* b = play_button();
	button_drw* ai = ai_button();

	_text.set_color(sf::Color::Black);
	_text.set_size(75);
	_text.set_str("temp. ai button");
	_text.set_pos(591*1.5,508*1.5+450+100);

	switch (cur_EV){
	case sf::Event::MouseButtonPressed:
		if(b->contains_cursor())
			return IDLE;
		if(ai->contains_cursor())
			return AI_MODE;
	}
	
	set_interface(INTERFACE::TITLE);
	_cursor.reTexturize();
	toDraw.push(&_interface);
	toDraw.push(b);
	toDraw.push(ai);
	toDraw.push(&_text);
	toDraw.push(&_cursor);
	return START;
}



int game::idle(){

	switch (cur_EV){
	case sf::Event::MouseButtonPressed:
		if(_board.contains_cursor()){
			update_score(false);
			if(lose_cond()){
				loses++;
				return LOST;
			}
			if(win_cond()){
				wins++;
				return WON;
			}
			flip_tile();
		}
	break;
	}
			
	_cursor.reTexturize();
	toDraw.push(&_board);
	toDraw.push(&_side);
	toDraw.push(&_cursor);
	return IDLE;
}

int game::lost(){

	button_drw* play_again = play_again_button();
	button_drw* quit = quit_button();

	//std::cout<<"LOST: " <<loses <<std::endl;

	if(_ai)
		return AI_MODE;

	b.active_all();
	switch (cur_EV){
	case sf::Event::MouseButtonPressed:
		if(play_again->contains_cursor()){
			lose(1);
			return START;
		}
		if(quit->contains_cursor()){
			_cursor.close_on(true); 
			toDraw.push(&_cursor);
		}
	break;
	}

	set_interface(INTERFACE::LOSE,90);
	_cursor.reTexturize();
	toDraw.push(&_board);
	toDraw.push(&_interface);
	toDraw.push(play_again);
	toDraw.push(quit);
	toDraw.push(&_cursor);
	return LOST;
}

int game::end(){
	switch (cur_EV){
	case sf::Event::MouseButtonPressed:
		_cursor.close_on(true); 
		toDraw.push(&_cursor);
	break;
	}

	return END;
}

int game::won(){

	//std::cout<<"WINS: "<<wins<<std::endl;

	if(b.get_level()>8-1){
		return COMPLETED;
	}
	std::cout<<"LEVEL : "<<b.get_level()<<" COMPLETE"<<'\n';
	win(b.get_level()+1);
	switch (cur_EV){
	case sf::Event::MouseButtonPressed:

	break;
	}

	std::cout<<"\nYOU HAVE WON\n";
	if(_ai)
		return AI_MODE;
	return IDLE;
}

int game::completed(){

	button_drw* play_again = play_again_button();
	button_drw* quit = quit_button();

	switch (cur_EV){
	case sf::Event::MouseButtonPressed:
		if(play_again->contains_cursor()){
			lose(1);
			return START;
		}
		if(quit->contains_cursor()){
			_cursor.close_on(true); 
			toDraw.push(&_cursor);
		}
	break;
	}
	
	set_interface(INTERFACE::COMPLETE,255);
	_cursor.reTexturize();
	toDraw.push(&_interface);
	toDraw.push(play_again);
	toDraw.push(quit);
	toDraw.push(&_cursor);

	return COMPLETED;
}

int game::ai_play(){
	_text.set_pos(0,0);
	_text.set_size(50);
	_text.set_str(stat_check_text());
	_text.set_color(sf::Color::Green);

	toDraw.push(&_text);
	_cursor.reTexturize();
	toDraw.push(&_cursor);
	return AI_PLAY;
}

int game::ai_mode(){
	target_it = 25;

	hold = games/target_it+1;
	if(games%target_it==0){
		std::cout<<"level up : "<< hold << "\n";
	}
	if(games>=8*target_it){
		stat_check();
		return AI_PLAY;
	}
	std::cout<<"| "<<games;
	ai_player ai;
	_ai = true;
	ai.sorter(this->get_b_ptr());
	int i = ai.get_index();
	_board.select_on();
	_board.set_index(i);
	update_score(i,false);
	//std::cout<<score<<"|"<<std::endl;
	if(lose_cond(i)){
		loses++;
		b.active_all();
		lose(hold);
		games++;
	}
	if(win_cond()){
		l_tracker[hold-1] = l_tracker[hold-1]+1;
		wins++;
		win(hold);
		games++;
	}
	flip_tile(i);
	it++;
	_cursor.reTexturize();
	toDraw.push(&_board);
	toDraw.push(&_side);
	toDraw.push(&_cursor);
	//std::cout<<"in ai_play:";
	return AI_MODE;
}

void game::stat_check(){
	std::cout<<"--------STATS--------";
	std::cout<<"\nGames played: "<<games;
	std::cout<<"\nWins: "<<wins;
	std::cout<<"\nLoses: "<<loses;
	std::cout<<"\nWinrate: "<<double(wins)/(double(loses)+double(wins));
	std::cout<<"\nIterations: "<<it<<"\n";

}

std::string game::stat_check_text(){
	std::string str="";
	str += "--------AI PERFORMANCE REPORT--------";
	str+=  
	"\nGames played: " + std::to_string(games) + 
	"\nWins: " + std::to_string(wins) +
	"\nLoses: " + std::to_string(loses) +
	"\nWinrate: " + std::to_string(double(wins)/(double(loses)+double(wins))) +
	"\nIterations: " + std::to_string(it);
	
	for(int i=0; i<8; i++){
		str += "\n wins in L "+std::to_string(i+1) + ": " + std::to_string(l_tracker[i]) +
		"/" + std::to_string(target_it)+ " ->rate: " +
		std::to_string(double(l_tracker[i])/double(target_it));
	}
	if(double(wins)/(double(loses)+double(wins))<.8)
		str += "\n\nwith a winrate less than 80% this ai is garbage"; 

	return str;
}


void game::init_cursor(){
    _cursor.set_file("../farfetch_leak.png");
	_cursor.reTexturize();
    _board.set_cursor(&_cursor);
}

void game::init_board(){
	_board.set_board(&b);
	_board.set_file("../voltorb_tiles.png");
    _side.set_side_info(&b);
	_side.set_file("../voltorb_info.png");
	_text.set_file("Nexa-Heavy.ttf");
}

void game::init_buttons(){
	// _buttons.push_back(play_button());
	// _buttons.push_back(play_again_button());
	// _buttons.push_back(quit_button());
}

button_drw* game::play_button(){
    button_drw* button = new button_drw(&_cursor);
	button->set_file("../play_button.png");
	button->set_color(sf::Color::Blue);
	int startx= 591*1.5,
		starty = 508*1.5,
		dx = 600,
		dy = 400;
	button->set_param(startx,startx+dx,starty,starty+dy);
	button->set_scale(.75);

	return button;
}

button_drw* game::ai_button(){
    button_drw* button = new button_drw(&_cursor);
	button->set_color(sf::Color::Blue);
	int startx= 591*1.5,
		starty = 508*1.5+450,
		dx = 600,
		dy = 400;
	button->set_param(startx,startx+dx,starty,starty+dy);
	button->set_scale(.75);

	return button;
}

button_drw* game::play_again_button(){
    button_drw* button = new button_drw(&_cursor);
	button->set_cursor(&_cursor);
	button->set_file("../buttons.png");
	button->set_color(sf::Color::Blue);
	button->set_t(475,0);
	int startx= 575,
		starty = 1000+50+50,
		dx = 475,
		dy = 200;
	button->set_param(startx,startx+dx,starty,starty+dy);
	button->set_scale(1);

	return button;
}

button_drw* game::quit_button(){
    button_drw* button = new button_drw(&_cursor);
	button->set_cursor(&_cursor);
	button->set_file("../buttons.png");
	button->set_color(sf::Color::Red);
	button->set_t(0,0);
	int startx= 0+50,
		starty = 1000+50+50,
		dx = 475,
		dy = 200;
	button->set_param(startx,startx+dx,starty,starty+dy);
	button->set_scale(1);

	return button;
}

void game::update_score(int i, bool cheat){
    score = score * b.get_val(_cursor.get_index());
	if(!cheat)
        score = b.get_coins();
	if(_ai)
		score = score * b.get_val(i);
}

bool game::win_cond(){
    return score == b.get_coins();
}

bool game::lose_cond(int i){
	if(_ai)
		return b.get_val(i)==0;
    return b.get_val(_cursor.get_index())==0;
}

void game::flip_tile(int i, bool debug){
	if(_ai)
		b.set_active(i,true);
	else
		b.set_active(_cursor.get_index(), true);

    if(debug){
        std::cout<<b.get_val(_cursor.get_index())<<" ";
        _cursor.print_index();
	}
}

void game::set_interface(int cur, int alpha){
    std::string file = "";
    switch(cur){
    case INTERFACE::TITLE:
        file = "../title_screen.png";
    break;
    case INTERFACE::LOSE:
        file = "../Lose_screen1.png";
    break;
    case INTERFACE::WIN:
        file = "../win_screen.png";
    break;
	case INTERFACE::COMPLETE: 
		file = "../level_8_complete.png";
	break;
    default:
        file = "no file";
    break;
    }

    _interface.set_file(file,alpha);
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

