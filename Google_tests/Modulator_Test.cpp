//
// Created by ankolesn on 30.04.22.
//

#include "gtest/gtest.h"
#include "modulator.cpp"


TEST(QAM_mod_demod, zero_msg) {
    int q = 16;
    double T = 1.0 / 600.0;
    double dt = T / 1000.0;
    int f = 2400;
    double E = 1;
    std::vector<bool> msg(32);
    auto foo = Modulator::qam_signal; //хранит указатель на функцию qam_signal
    auto constell = Modulator::constellation(q, T, dt, f, E, foo);
    auto map = Modulator::grey_mapping(q, "qam");
    auto mod = Modulator::qam_mod(msg, constell, map);
    auto demod = Modulator::qam_demod(mod, constell, map);
    EXPECT_EQ(demod, msg);
}

TEST(QAM_mod_demod, random_msg) {
    int q = 16;
    double T = 1.0 / 600.0;
    double dt = T / 1000.0;
    int f = 2400;
    double E = 1;
    std::vector<bool> msg(16);
    for (auto &&mi: msg) {
        mi = rand() % 2;
    }
    auto foo = Modulator::qam_signal; //хранит указатель на функцию qam_signal
    auto constell = Modulator::constellation(q, T, dt, f, E, foo);
    auto map = Modulator::grey_mapping(q, "qam");
    auto mod = Modulator::qam_mod(msg, constell, map);
    auto demod = Modulator::qam_demod(mod, constell, map);
    EXPECT_EQ(demod, msg);
}

TEST(QAM_mod_demod_soft, zero_msg) {
    int q = 16;
    double T = 1.0 / 600.0;
    double dt = T / 1000.0;
    int f = 2400;
    double E = 1;
    std::vector<bool> msg(32);
    std::vector<double> exp(32);
    auto ind = 0;
    for (auto &&e: exp) {
        e = ind++ % 2 ? 20 : 80;
    }
    auto foo = Modulator::qam_signal; //хранит указатель на функцию qam_signal
    auto constell = Modulator::constellation(q, T, dt, f, E, foo);
    auto map = Modulator::grey_mapping(q, "qam");
    auto mod = Modulator::qam_mod(msg, constell, map);
    auto demod = Modulator::qam_soft_demod(mod, constell, map, 20);
    auto i = 0;
    for (auto llr: demod) {
        EXPECT_TRUE(llr-exp[i++] < std::numeric_limits<float>::epsilon());
    }
}

TEST(QAM_mod_demod_soft, ones_msg) {
    int q = 16;
    double T = 1.0 / 600.0;
    double dt = T / 1000.0;
    int f = 2400;
    double E = 1;
    std::vector<bool> msg(32, 1);
    std::vector<double> exp(32, -20);
    auto ind = 0;
    auto foo = Modulator::qam_signal; //хранит указатель на функцию qam_signal
    auto constell = Modulator::constellation(q, T, dt, f, E, foo);
    auto map = Modulator::grey_mapping(q, "qam");
    auto mod = Modulator::qam_mod(msg, constell, map);
    auto demod = Modulator::qam_soft_demod(mod, constell, map, 20);
    auto i = 0;
    for (auto llr: demod) {
        EXPECT_TRUE(llr-exp[i++] < std::numeric_limits<float>::epsilon());
    }
}
