//
// Created by justnik on 17.04.22.
//

#include "awgnchannel.hpp"


std::vector<double> AWGN_channel::add_noise(std::vector<double> &signal, double SNR, double sig_pow) const {
    std::random_device rd{};
    std::mt19937 gen{rd()};
    auto res = signal;
    auto sigma = sqrt(sig_pow / pow(10, SNR / 10));
    std::normal_distribution<> dist{0, sigma};
    for (auto &&r: res) {
        r += dist(gen);
    }
    return res;
}

std::complex<double> AWGN_channel::add_noise(std::complex<double> &signal, double SNR, double sig_pow) const {
    std::random_device rd{};
    std::mt19937 gen{rd()};
    auto res = signal;
    auto sigma = sqrt(sig_pow / pow(10, SNR / 10));
    std::normal_distribution<> dist{0, sigma};
    auto x_noise = dist(gen);
    auto y_noise = dist(gen);
    res.real(res.real() + x_noise/sqrt(2));
    res.imag(res.imag() + y_noise/sqrt(2));
    return res;
}

