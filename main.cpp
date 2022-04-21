#include <iostream>
#include <fstream>
#include "channels/awgnchannel.hpp"
#include "modulators/modulator.hpp"

using namespace  std;
int main() {
    //Time Test
//    vector<float> v (100000000);
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
    int q = 4;
    double T = 1.0 / 600.0;
    double dt = T / 1000.0;
    int f = 2400;
    // vector<double> f = {20.0/T, 19.0/T, 18.0/T, 17.0/T};
    double A = 1;
    //signals
    ofstream out("in.txt");
    auto arr = Modulator::pm(q, T, dt, f, A);

    for (auto j = 0; j < arr[0].size(); ++j) {
        out << dt * j << ' ';
        for (auto & i : arr) {
            out << i[j] << ' ';
        }
        out << endl;
    }
    out.close();
    //constellation
    ofstream out2("constellation");
    auto foo = Modulator::pm_signal; //хранит указатель на функцию qam_signal
    auto constell = Modulator::constellation(q, T, dt, f, A, foo);
    for (int i = 0; i < q; ++i) {
        out2 << constell[i].real() << ' ' << constell[i].imag() << endl;
    }

    //awgn channel

    return 0;
}

