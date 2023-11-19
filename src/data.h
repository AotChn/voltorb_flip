#ifndef DATA_H
#define DATA_H

#include "iomanip"
#include "iostream"
#include "fstream"
#include "board.h"

class data{

private:
    board* b;
    std::ofstream out;

public:
    data(){};

    void write_data();
    void set_board(board g);


};


#endif