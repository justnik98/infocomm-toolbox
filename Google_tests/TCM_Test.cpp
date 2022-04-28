//
// Created by ankolesn on 28.04.22.
//

#include "gtest/gtest.h"
#include "tcm.cpp"

TEST(TCM_Encoder, zero_msg){
    TCM tcm({{2},{2}});
    std::vector<bool>  res (32);
    std::vector<bool>  msg(16);
    EXPECT_EQ(tcm.encode(msg), res);
}

TEST(TCM_Decoder, random_input){
    TCM tcm({{10, 15}, {37, 76}});
    std::vector<bool> msg (1024);
    for(auto &&mi:msg){
        mi = rand() % 2;
    }

    EXPECT_EQ(tcm.vitdec(tcm.encode(msg)),msg);
}

TEST(TCM_Decoder, fix_one_bit_error){
    TCM tcm({{10, 15}, {37, 76}});
    std::vector<bool> msg (1024);
    for(auto &&mi:msg){
        mi = rand() % 2;
    }
    std::vector<bool> res = tcm.encode(msg);
    res[50] = !res[50];
    EXPECT_EQ(tcm.vitdec(res),msg);
}