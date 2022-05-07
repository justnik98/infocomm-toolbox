//
// Created by ankolesn on 28.04.22.
//

#include "gtest/gtest.h"
#include "tcm.cpp"

TEST(TCM_Encoder, zero_msg){
    TCM tcm({{13},{15}});
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

TEST(TCM_Decoder, large_input){
    TCM tcm({{10, 15}, {37, 76}});
    std::vector<bool> msg (10240);
    for(auto &&mi:msg){
        mi = rand() % 2;
    }
    EXPECT_EQ(tcm.vitdec(tcm.encode(msg)),msg);
}

TEST(TCM_Decoder, soft_input){
    TCM tcm ({{13},{15}});
    std::vector<double> signal (32, 20);
    std::vector<bool> msg (16, 0);
    EXPECT_EQ(msg, tcm.vitdec(signal));
}

TEST(TCM_Decoder, soft_random_input){
    TCM tcm({{13}, {15}});
    std::vector<bool> msg(16);
    for(auto &&mi:msg){
        mi = rand() % 2;
    }
    std::vector<double> llr;
    auto enc = tcm.encode(msg);
    for (auto &&m:enc) {
        if(m) {
            llr.push_back(-0.5);
        }
        else{
            llr.push_back(0.5);
        }
    }
    EXPECT_EQ(msg, tcm.vitdec(llr));
}