//
// Created by justnik on 17.04.22.
//

#ifndef INFOCOMM_TOOLBOX_CHANNEL_HPP
#define INFOCOMM_TOOLBOX_CHANNEL_HPP

#include <vector>
#include <complex>

class Channel {
public:
    Channel() = default;

    [[nodiscard]] virtual std::vector<float>
    add_noise(std::vector<float> signal, float SNR, float sig_pow = 1) const = 0;

    [[nodiscard]] virtual std::vector<std::complex<float>>
    add_noise(std::vector<std::complex<float>> signal, double SNR, float sig_pow = 1) const = 0;
};


#endif //INFOCOMM_TOOLBOX_CHANNEL_HPP
