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

    std::vector<float> add_noise(std::vector<float> &signal, float SNR, float sig_pow = 1) const override;

    std::vector<std::complex<float>>
    add_noise(std::vector<std::complex<float>> &signal, float SNR, float sig_pow = 1) const override;
};


#endif //INFOCOMM_TOOLBOX_AWGNCHANNEL_HPP
