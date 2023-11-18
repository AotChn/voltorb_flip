
#include <iostream>
#include "gtest/gtest.h"

int main(int argc, char **argv){
	::testing::InitGoogleTest(&argc, argv);
	std::cout<<"\n\n----------running basic_test.cpp---------\n\n"<<std::endl;
	return RUN_ALL_TESTS();
}
