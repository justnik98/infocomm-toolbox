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

    [[nodiscard]] virtual std::vector<double>
    add_noise(std::vector<double> &signal, double SNR, double sig_pow = 1) const = 0;

    [[nodiscard]] virtual std::complex<double>
    add_noise(std::complex<double> &signal, double SNR, double sig_pow = 1) const = 0;
};


#endif //INFOCOMM_TOOLBOX_CHANNEL_HPP
