#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <time.h>
#include "constants.h"
#include "ai.h"
#include "math.h"

class board{
private: 
	int level,
		coins,
		used,
		score;
	int val[25], 
		idx[25],
        rb[5],
        cb[5],
        rp[5],
        cp[5];
	bool active[25];
 	int p_coins[40] = {24,27,32,36,48,
 				   	   54,64,72,81,96,
					   108,128,144,162,192,
					   216,243,256,288,324,
					   384,432,486,512,576,
					   648,729,768,864,972,
					   1152,1296,1458,1536,1728,
					   2187,2304,2592,2916,3456};
public:
	
	board(){reset_all();used=0;}
    board& operator=(const board& RHS);

//===========================================
//	SUMMATIONS
//===========================================
	
    int sum_row(int row);
	int sum_row_b(int row);
	int sum_col_b(int col);
	int sum_col(int col);

//===========================================
//	MUTATORS
//===========================================
	
    int set_bomb();
    void set_coins();
    void set_level(int l);
    void next_level();

//===========================================
//	ACCESSORS
//===========================================

    int get_level();
    int get_coins();
    int get_score();
    int get_used();
    int get_val(int n);
    int* get_board_val();
    int* get_rb();
    int* get_cb();
    int* get_rp();
    int* get_cp();

//===========================================
//	CREATION
//===========================================
    
    //resets variables
    void reset();

    //resets everything
    void reset_all();

    //only resets coins and score;
    void reset_c();

    //reset to certain level
    void reset_l(int l);

    //initializes all arr
    void init_all();

    //init idx arr
    void init_idx();

    //init val arr
    void init_val();

    //init active arr
    void init_active();

    //generates new board
    void gen_board();

    //fill board data
    void fill_data();

//===========================================
//	HELPER
//===========================================

    //flips all slots to active
    void active_all();

    //swaps arr[i] with arr[size]
	void swap_end(int i, int size);
	
    //places value in unused slot
	void fill_slot(int value);

    //prints rows with bomb and pt info
    void print_row_stats(int n);

    //prints bomb and pt info of col
    void print_col_stats();
    
    //prints full board
    void print_board();

    //get number from 0-n
    int gen_num(int n);

    //print board stats
    void board_stats();

    //print arr
    void print_arr(int*, int);

    int get_row(int i);

    int get_col(int i);


//===========================================
//	GAME MECH.
//===========================================

    //plays game
	void play();

    //flip slot to active
    int flip(int index);

    //index by row col
	int select(int row, int col);

};


#endif