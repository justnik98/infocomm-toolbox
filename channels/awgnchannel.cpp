//
// Created by justnik on 17.04.22.
//

#include "awgnchannel.hpp"


std::vector<float> AWGN_channel::add_noise(std::vector<float> &signal, float SNR, float sig_pow) const {
    std::random_device rd{};
    std::mt19937 gen{rd()};
    auto res = signal;
    auto sigma = sig_pow / sqrt(pow(10,SNR/10));
    std::normal_distribution<> dist{0, sigma};
    for (auto &&r: res) {
        r+= dist(gen);
    }
    return res;
}

std::vector<std::complex<float>>
AWGN_channel::add_noise(std::vector<std::complex<float>> &signal, float SNR, float sig_pow) const {
    std::random_device rd{};
    std::mt19937 gen{rd()};
    auto res = signal;
    auto sigma = sig_pow / sqrt(pow(10,SNR/10));
    std::normal_distribution<> dist{0, sigma};
    for (auto &&c: res) {
        c.real(c.real() + dist(gen));
        c.imag(c.imag() + dist(gen));
    }
    return res;
}
