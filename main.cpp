#include <complex>
#include <iostream>
#include <fstream>
#include "channels/awgnchannel.hpp"
#include "modulators/modulator.hpp"

using namespace std;

vector<double> modeling(vector<complex<double>> &c, const vector<double> &snr_dB_arr, size_t num) {
    vector<double> Pe;
    AWGN_channel awgn;

    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> distrib(0, static_cast<int>(c.size()) - 1);

    for (auto &snr: snr_dB_arr) {
        cout << "SNR: " << snr << endl;
        auto sum = 0.0;
        size_t error_count = 0;
        for (auto n = 0; n < num; ++n) {
            auto i = distrib(gen);
            auto r = awgn.add_noise(c[i], snr);
            auto dmin = numeric_limits<double>::infinity();
            auto ind = 0;
            for (auto k = 0; k < c.size(); ++k) {
                double d = sqrt(pow(c[k].real() - r.real(), 2) + pow(c[k].imag() - r.imag(), 2));
                if (d < dmin) {
                    dmin = d;
                    ind = k;
                }
            }
            if (ind != i) {
                error_count++;
            }
        }
        Pe.push_back(static_cast<double>(error_count) / num);
    }
    return Pe;
}

int main() {
    //Time Test
//    vector<double> v (100000000);
//    AWGN_channel c;
//    auto start = std::chrono::system_clock::now();
//    v = c.add_noise(v,0, 1);
//    auto end = std::chrono::system_clock::now();
//
//    std::chrono::duration<double> diff = end - start;
//    std::cout << "Time to fill and iterate a vector of " << std::setw(9)
//              << v.size() << ": " << diff.count() << " s\n";
//
//    auto sum = 0.0;
//    for(auto &&vi: v){
//        sum += vi*vi;
//    }
//    cout << sum/ v.size() << endl;
    // params
    int q = 16;
    double T = 1.0 / 600.0;
    double dt = T / 1000.0;
    int f = 2400;
    // vector<double> f = {20.0/T, 19.0/T, 18.0/T, 17.0/T};
    double E = 1;
    //signals
    ofstream out("in.txt");
    auto arr = Modulator::pm(q, T, dt, f, E);

    for (auto j = 0; j < arr[0].size(); ++j) {
        out << dt * j << ' ';
        for (auto &i: arr) {
            out << i[j] << ' ';
        }
        out << endl;
    }
    out.close();
    //constellation
    ofstream out2("constellation");
    auto foo = Modulator::pm_signal; //хранит указатель на функцию qam_signal
    auto constell = Modulator::constellation(q, T, dt, f, E, foo);
    for (int i = 0; i < q; ++i) {
        out2 << constell[i].real() << ' ' << constell[i].imag() << endl;
    }
    //awgn channel
    vector<double> snr_arr(25);
    int i = 0;
    for (auto &snr: snr_arr) {
        snr = i++;
    }
    ofstream out3("Pe");
    auto res = modeling(constell, snr_arr, 100000);
    for (auto j = 0; j < snr_arr.size(); ++j) {
        out3 << snr_arr[j] << ' ' << res[j] << ' ' << Modulator::fer_theor(pow(10, snr_arr[j] / 10), q, "pm") << endl;
    }
    return 0;
}

