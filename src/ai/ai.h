#ifndef AI_H
#define AI_H

#include <iostream>
#include <iomanip>
#include <vector>
#include <queue>

struct tile_r{
	tile_r(){}
	tile_r(int r, int i){
		rating = r;
		index = i;
	}

	friend bool operator<(const tile_r& l, const tile_r& r){
		return l.rating < r.rating;
	}

	friend std::ostream& operator <<(std::ostream& outs, const tile_r& tile_r){
		outs << tile_r.rating;
		return outs;
	}

	int rating,
		index;
};

class ai_player{
	std::priority_queue<tile_r> best;
	int choice[25];
	int used;

	public:
	ai_player(){
		init_choice();
		used = 1;
	}
	
    //reset choice arr
	void init_choice();

    //get unused index
	int get_index();

	int get_index(int a){
		int index = best.top().index;
		std::cout<<"index: " << best.top().index<< " rating: "<< best.top().rating<<std::endl; 
		best.pop();
		return index;
	}

    //reset used
	void reset();

	//void set_collector(board& b);
	template<class T>
	void sorter(T* b);

};

template<class T>
void ai_player::sorter(T* b){
	while(!best.empty()){
		std::cout<<" " << best.top();
		best.pop();
	}
	b->fill_data();
	int* cp = b->get_cp();
	int* cb = b->get_cb();
	int* rp = b->get_rp();
	int* rb = b->get_rb();
	int sum;
	for(int i=0; i<25; i++){
		sum = 2*(rp[b->get_row(i)] + cp[b->get_col(i)]) - (rb[b->get_row(i)] + cb[b->get_col(i)]);
		best.emplace(tile_r(sum, i));
	}

	
}



#endif