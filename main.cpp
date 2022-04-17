#include <iostream>
#include "channels/awgnchannel.hpp"

using namespace  std;
int main() {
    vector<float> v (100000);
    AWGN_channel c;
    v = c.add_noise(v,3);
    auto sum = 0.0;
    for(auto &&vi: v){
        sum += vi*vi;
    }
    cout << sum/ v.size() << endl;
    return 0;
}
