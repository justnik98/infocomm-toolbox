//
// Created by justnik on 17.04.22.
//

#ifndef INFOCOMM_TOOLBOX_AWGNCHANNEL_HPP
#define INFOCOMM_TOOLBOX_AWGNCHANNEL_HPP

#include <random>
#include "channel.hpp"

class AWGN_channel : public Channel {
public:
    AWGN_channel() = default;

    std::vector<double> add_noise(std::vector<double> &signal, double SNR, double sig_pow = 1) const final;

    std::complex<double> add_noise(std::complex<double> &signal, double SNR, double sig_pow = 1) const final;
};


#endif //INFOCOMM_TOOLBOX_AWGNCHANNEL_HPP
