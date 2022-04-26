//
// Created by justnik on 21.04.22.
//

#ifndef INFOCOMM_TOOLBOX_MODULATOR_HPP
#define INFOCOMM_TOOLBOX_MODULATOR_HPP


#include <vector>
#include <complex>
#include <numeric>
#include <cmath>


class Modulator {
private:
    constexpr static auto pi = M_PI;
    constexpr static auto e = M_E;

    static double normalCDF(double value) {
        return 0.5 * erfc(-value * M_SQRT1_2);
    }

    static double Q(double x) {
        return 1.0 - normalCDF(x);
    }

    static double sinc(double x) {
        if (x != 0) {
            return sin(x) / (x);
        } else return 1;
    }

public:

    static double pm_signal(int i, double t, double f, double T, int q, double E);

    static double fm_signal(int i, double t, double f, double T, int q, double E);

    static double qam_signal(int i, double t, double f, double T, int q, double E);

    static std::vector<std::vector<double>> qam(int q, double T, double dt, double f, double E);

    static std::vector<std::vector<double>> pm(int q, double T, double dt, double f, double E);

    static std::vector<std::vector<double>> fm(int q, double T, double dt, std::vector<double> &f, double E);

    static std::vector<std::complex<double>> constellation(int q, double T, double dt, double f, double E,
                                                           double(*op)(int, double, double, double,
                                                                       int,
                                                                       double));

    static double fer_theor(double snr, int q, const std::string &mod);

    static std::vector<std::vector<double>>
    spectrum(int q, double T, double df, double f, double E, const std::string &mod);

    static std::vector<int> grey_mapping (int q, const std::string &mod);
};


#endif //INFOCOMM_TOOLBOX_MODULATOR_HPP
