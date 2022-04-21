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
public:

    static double pm_signal(int i, double t, double f, double T, int q, double E);

    static double fm_signal(int i, double t, double f, double T, int q, double E);

    static double qam_signal(int i, double t, double f, double T, int q, double A);

    static std::vector<std::vector<double>> qam(int q, double T, double dt, double f, double A);

    static std::vector<std::vector<double>> pm(int q, double T, double dt, double f, double E);

    static std::vector<std::vector<double>> fm(int q, double T, double dt, std::vector<double> &f, double E);

    static std::vector<std::complex<double>> constellation(int q, double T, double dt, double f, double E,
                                                    double(*op)(int, double, double, double,
                                                                int,
                                                                double));
};


#endif //INFOCOMM_TOOLBOX_MODULATOR_HPP
