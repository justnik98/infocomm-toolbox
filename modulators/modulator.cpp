//
// Created by justnik on 21.04.22.
//

#include <iostream>
#include "modulator.hpp"

double Modulator::qam_signal(int i, double t, double f, double T, int q, double A) {
    int i1 = i / sqrt(q);
    int i2 = i % (int) sqrt(q);
    double si1 = A * (1 - 2 * i1 / (sqrt(q) - 1));
    double si2 = A * (1 - 2 * i2 / (sqrt(q) - 1));
    double res = (si1 * sqrt(2 / T) * cos(2 * pi * f * t)) + (si2 * sqrt(2 / T) * sin(2 * pi * f * t));
    return res;
}

std::vector<std::vector<double>> Modulator::qam(int q, double T, double dt, double f, double A) {
    std::vector<std::vector<double>> arr(q);
    for (auto i = 0; i < q; ++i) {
        arr[i].resize(T / dt + 1);
    }
    for (int i = 0; i < q; i++) {
        int j = 0;
        for (double t = 0; t < T; t += dt, j++) {
            arr[i][j] = qam_signal(i, t, f, T, q, A);
        }
    }
    return arr;
}

std::vector<std::vector<double>> Modulator::pm(int q, double T, double dt, double f, double E) {
    std::vector<std::vector<double>> arr(q);
    for (auto i = 0; i < q; ++i) {
        arr[i].resize(T / dt + 1);
    }
    for (int i = 0; i < q; i++) {
        int j = 0;
        for (double t = 0; t < T; t += dt, j++) {
            arr[i][j] = pm_signal(i, t, f, T, q, E);
        }
    }
    return arr;
}

double Modulator::pm_signal(int i, double t, double f, double T, int q, double E) {
    double theta = (2 * pi * i) / q;
    double res = sqrt((2 * E) / T) * cos(2 * pi * f * t - theta);
    return res;
}

double Modulator::fm_signal(int i, double t, double f, double T, int q, double E) {
    double res = sqrt((2 * E) / T) * cos(2 * pi * f * t);
    return res;
}

std::vector<std::vector<double>> Modulator::fm(int q, double T, double dt, std::vector<double> &f, double E) {
    std::vector<std::vector<double>> arr(q);
    for (auto i = 0; i < q; ++i) {
        arr[i].resize(T / dt + 1);
    }
    for (int i = 0; i < q; i++) {
        int j = 0;
        for (double t = 0, j = 0; t < T; t += dt, j++) {
            arr[i][j] = fm_signal(i, t, f[i], T, q, E);
        }
    }
    return arr;
}

std::vector<std::complex<double>> Modulator::constellation(int q, double T, double dt, double f, double E,
                                                           double(*op)(int, double, double,
                                                                       double, int,
                                                                       double)) {
    std::vector<std::complex<double>> res(q);
    for (int i = 0; i < q; i++) {
        double x = 0;
        double y = 0;
        for (double t = 0; t < T; t += dt) {
            x += op(i, t, f, T, q, E) * sqrt(2.0 / T) * cos(2 * pi * f * t);
            y += op(i, t, f, T, q, E) * sqrt(2.0 / T) * sin(2 * pi * f * t);
        }
        res[i] = std::complex(x * dt, y * dt);
    }
    double e_mean = 0;
    for (auto &si: res) {
        e_mean += (si.real() * si.real() + si.imag() * si.imag());
    }
    e_mean /= q;
    for (auto &si: res) {
        si.real(si.real() / sqrt(e_mean / E));
        si.imag(si.imag() / sqrt(e_mean / E));
    }
    return res;
}

double Modulator::fer_theor(double snr, int q, const std::string &mod) {
    if (mod == "qam") {
        return pow(e, (-3 * snr / (2 * (q - 1))));
    } else if (mod == "pm") {
        return 2 * Q(sqrt(2 * snr) * sin(pi / q));
    }
    return 0;
}

std::vector<std::vector<double>>
Modulator::spectrum(int q, double T, double df, double f0, double E, const std::string &mod) {
    std::vector<std::vector<double>> s(q);

    if (mod == "qam") {
        for (int i = 0; i < q; ++i) {
            std::complex<double> p;
            for (int f = 0; f < 10 * f0; ++f) {
                int i1 = i / sqrt(q);
                int i2 = i % (int) sqrt(q);
                double si1 = E * (1 - 2 * i1 / (sqrt(q) - 1));
                double si2 = E * (1 - 2 * i2 / (sqrt(q) - 1));

            }
        }
        return {{0}};
    } else if (mod == "pm") {
        for (int i = 0; i < q; ++i) {
            std::complex<double> p;
            for (int f = 0; f < 10 * f0; ++f) {
                double theta = 2.0 * pi * i / q;
                std::complex<double> p3 = pow(e, std::complex<double>(0, pi * f * T));
                std::complex<double> p1 =
                        sqrt(E * T / 2.0) * cos(theta) * (sinc((f - f0) * T) + sinc((f + f0) * T)) * p3;
                std::complex<double> p2 =
                        (std::complex<double>(1, 0) / std::complex<double>(0, 1)) * sqrt(E * T / 2.0) * sin(theta) *
                        (sinc((f - f0) * T) - sinc((f + f0) * T)) * p3;
                p = p1 + p2;
                s[i].push_back(abs(p));
            }
        }

        return s;
    }


    return std::vector<std::vector<double>>();
}
