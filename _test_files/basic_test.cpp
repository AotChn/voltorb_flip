#include "gtest/gtest.h"
#include <iostream>

#include "../src/board.h"

class INDEXING : public testing::Test{
  protected:
  board b;
  int result;
};

TEST_F(INDEXING, row_from_index0){
  result = b.get_row(0);
  EXPECT_EQ(0,result);
}

TEST_F(INDEXING, row_from_index1){
  result = b.get_row(1);
  EXPECT_EQ(0,result);
}

TEST_F(INDEXING, row_from_index6){
  result = b.get_row(6);
  EXPECT_EQ(1,result);
}

TEST_F(INDEXING, row_from_index24){
  result = b.get_row(24);
  EXPECT_EQ(4,result);
}

TEST_F(INDEXING, row_from_index17){
  result = b.get_row(17);
  EXPECT_EQ(3,result);
}

TEST_F(INDEXING, col_col_from_index0){
  result = b.get_col(0);
  EXPECT_EQ(0,result);
}

TEST_F(INDEXING, col_col_from_index1){
  result = b.get_col(1);
  EXPECT_EQ(1,result);
}

TEST_F(INDEXING, col_col_from_index6){
  result = b.get_col(6);
  EXPECT_EQ(1,result);
}

TEST_F(INDEXING, col_col_from_index24){
  result = b.get_col(24);
  EXPECT_EQ(4,result);
}

TEST_F(INDEXING, col_col_from_index17){
  result = b.get_col(17);
  EXPECT_EQ(2,result);
}


int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  std::cout<<"\n\n----------running basic_test.cpp---------\n\n"<<std::endl;
  return RUN_ALL_TESTS();
}
