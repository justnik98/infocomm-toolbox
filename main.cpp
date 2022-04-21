#include <iostream>
#include <chrono>
#include <iomanip>
#include "channels/awgnchannel.hpp"

using namespace  std;
int main() {
    vector<float> v (100000000);
    AWGN_channel c;
    auto start = std::chrono::system_clock::now();
    v = c.add_noise(v,0, 1);
    auto end = std::chrono::system_clock::now();

    std::chrono::duration<double> diff = end - start;
    std::cout << "Time to fill and iterate a vector of " << std::setw(9)
              << v.size() << ": " << diff.count() << " s\n";

    auto sum = 0.0;
    for(auto &&vi: v){
        sum += vi*vi;
    }
    cout << sum/ v.size() << endl;
    return 0;
}

