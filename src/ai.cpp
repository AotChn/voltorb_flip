

#include "ai.h"


int gen_num(int n){
	return rand() % n;
}

void swap_end(int a[], int i, int size){
	int temp = a[i];
	a[i] = a[size];
	a[size] = temp;
}

void ai_player::init_choice(){
	for(int i=0; i<25; i++){
		choice[i] = i;
	}
}

int ai_player::get_index(){
	int n = gen_num(25-used);
	int idx = choice[n];
	swap_end(choice,n,25-used);
	used++;
	return idx;
}

void ai_player::reset(){
	used = 1;
}
