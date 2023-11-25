#include "board.h"

board& board::operator=(const board& RHS){
	level = RHS.level;
	coins = RHS.coins;
	used = RHS.used;
	score = RHS.score;
	for(int i=0; i<25; i++){
		val[i] = RHS.val[i];
	}
}

//===========================================
//	SUMMATIONS
//===========================================

int board::sum_row(int row){
	int sum = 0;
	for(int i=0; i<5; i++){
		sum += val[(row*5)+i];
	}
	return sum;
}
int board::sum_row_b(int row){
	int sum = 0;
	for(int i=0; i<5; i++){
			if(val[(row*5)+i]==0){
			sum++;	
			}
	}
	return sum;
}

int board::sum_col_b(int col){
	int sum = 0;
	for(int i=0; i<5; i++){
		if(val[(i*5)+col]==0){
			sum++;
		}
	}
	return sum;
}

int board::sum_col(int col){
	int sum = 0;
	for(int i=0; i<5; i++){
		sum+= val[(i*5)+col];
	}
	return sum;
}

//===========================================
//	ACCESSORS
//===========================================

int board::get_level(){
	return level;
}
int board::get_coins(){
	return coins;
}
int board::get_score(){
	return score;
}
int board::get_used(){
	return used;
}

int board::get_val(int n){
	return val[n];
}

int* board::get_board_val(){
	return val;
}

bool* board::get_active(){
	return active;
}

int* board::get_rb(){
	return rb;
}
int* board::get_cb(){
	return cb;
}
int* board::get_rp(){
	return rp;
}
int* board::get_cp(){
	return cp;
}

//===========================================
//	MUTATORS
//===========================================

int board::set_bomb(){
	if(level<4)
		return level+5;
	else if(level == 4 && coins <244)
		return level+4;
	else
		return 10;
}

void board::set_coins(){
	int a = level-1,
	r = gen_num(5);
	coins = p_coins[(a*5)+r];
}

void board::set_level(int l){
	level = l;
}

void board::next_level(){
	level++;
}

void board::set_active(int i, bool t){
	active[i] = t;
}

//===========================================
//	CREATION
//===========================================

void board::reset(){
	level = 1;
	score = 1;
	init_active();
	set_coins();
}

void board::reset_all(){
	init_all();
	level = 1;
	score = 1;
	set_coins();
}

void board::reset_c(){
	score = 1;
	set_coins();
}

void board::reset_l(int l){
	score = 1;
	set_level(l);
	gen_board();
}

void board::init_all(){
	for(int i=0; i<25; i++){
		idx[i]=i;
		val[i]=1;
		active[i]=false;
	}
}

void board::init_idx(){
	for(int i=0; i<25; i++){
		idx[i]=i;
	}
}

void board::init_val(){
	for(int i=0; i<25; i++){
		val[i]=1;
	}
}

void board::init_active(){
	for(int i=0; i<25; i++){
		active[i]=false;
	}
}

void board::gen_board(){
	init_val();
	init_active();
	used = 0;
	
	//set coins
	set_coins();

	//sets bombs
	for(int i=0; i<set_bomb(); i++){
		fill_slot(0);
	}
	
	int hold = coins;

	//fill 2s
	while(hold%2 == 0 && hold>0){	
		fill_slot(2);
		hold = hold/2;
	}
	//fill 3s
	while(hold%3 == 0 && hold>0){
		fill_slot(3);
		hold = hold/3;
	}
	fill_data();
}

void board::fill_data(){
	for(int i=0;i<5;i++){
		cp[i] = sum_col(i);
		cb[i] = sum_col_b(i);
		rp[i] = sum_row(i);
		rb[i] = sum_row_b(i);
	}
}


//===========================================
//	HELPER
//===========================================

void board::active_all(){
	for(int i=0; i<25; i++){
		active[i]=true;
	}
}

void board::swap_end(int i, int size){
	int temp = idx[i];
	idx[i] = idx[size];
	idx[size] = temp;
}

void board::fill_slot(int value){
	int n;
	if(used == 24)
		n = 0;
	else
		n = gen_num(24-used);
	val[idx[n]] = value;
	swap_end(n,24-used);
	used++;
}

void board::print_row_stats(int n){
	for(int i=0; i<5; i++){
		if(val[(n*5)+i]==0 && active[(n*5)+i]==true)
			std::cout<<"["<<" V] ";

		else if(active[(n*5)+i]==true)
			std::cout<<"["<<std::setw(2)<<val[(n*5)+i]<<"] ";
		
		else
			std::cout<<"[ x] ";
	}
	std::cout<<"| <"<<sum_row(n)<<" | "<<sum_row_b(n)<<">"<<std::endl;
}

void board::print_col_stats(){
	for(int i=0;i<5;i++)
		std::cout<<"["<<std::setw(2)<<sum_col(i)<<"] ";
	std::cout<<" : p"<<std::endl;
	
	for(int i=0;i<5;i++)
		std::cout<<"["<<std::setw(2)<<sum_col_b(i)<<"] ";
	std::cout<<" : b"<<std::endl;
}

void board::print_board(){

	std::cout<<'\n'<<"--------voltorb flip-----------------"<<'\n';
	board_stats();
	std::cout<<"-------------------------*"<<'\n';
	std::cout<<'\n';
	for(int i=0; i<5; i++)
		print_row_stats(i);
	std::cout<<"-------------------------*"<<'\n';
	print_col_stats();
	std::cout<<"-------------------------------------"<<'\n';
}

void board::board_stats(){
	int twos = 0,
		threes = 0,
		hold = coins;

	while(hold%2 == 0 && hold>0){	
		twos++;
		hold = hold/2;
	}
	while(hold%3 == 0 && hold>0){
		threes++;
		hold = hold/3;
	}

	std::cout<<"[TWOS : " <<twos<<" ]";
	std::cout<<" [THREES : " <<threes<<" ]";
	std::cout<<" [BOMBS : " <<set_bomb()<<" ]"<<std::endl;
	std::cout<<"[LEVEL : " <<level<<" ]";
	std::cout<<" [COINS : " <<coins<<" ]"<<std::endl;
}

int board::gen_num(int n){
	return rand() % n;
}

void board::print_arr(int* a, int size){
	for(int i=0; i<5; i++){
		std::cout<<"[" <<std::setw(2)<<a[i]<<"] "; 
	}
}

int board::get_row(int i){
	return floor((double)i/5);
}

int board::get_col(int i){
	return i%5;
}

//===========================================
//	GAME MECH.
//===========================================

int board::select(int row, int col){
	return row*5 + col;
}

int board::flip(int index){
	active[index] = true;
	return val[index];
}

void board::play(){

}