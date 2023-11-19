#include "data.h"


void data::write_data(){
    out.open("voltorb_data.csv",std::ofstream::app);
        b->fill_data();
        int* cp = b->get_cp();
        int* cb = b->get_cb();
        int* rp = b->get_rp();
        int* rb = b->get_rb();
        int* values = b->get_board_val();

//        out << "index, value, col pts, col bombs, row pts, row bombs" <<'\n';
        for(int i=0; i<25; i++){
            out << i <<','
                <<values[i] << ','
                << cp[b->get_col(i)] << ','
                << cb[b->get_col(i)] << ','
                << rp[b->get_row(i)] << ','
                << rb[b->get_row(i)]
                <<'\n';
        }

    std::cout<<"data write finished [check]"<<std::endl;
    out.close();
}

void data::set_board(board g){
    b = &g;
}

