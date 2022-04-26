//
// Created by ankolesn on 26.04.22.
//

#include "tcm.hpp"

TCM::TCM(const std::vector<std::vector<int>> &tr) {
    trellis.resize(tr.size());
    for (auto i = 0; i < tr.size(); ++i) {
        auto size_memory_max = 3 * (tr[i].size() - 1);
        if (tr[i][0] == 1)
            size_memory_max++;
        else if (tr[i][0] == 2 || tr[i][0] == 3)
            size_memory_max += 2;
        else
            size_memory_max += 3;
        if (size_memory_max > size_memory)
            size_memory = size_memory_max;

        trellis[i] = 0;
        for (auto j = 0; j < tr[i].size(); ++j) {
            trellis[i] <<= 3;
            trellis[i] += tr[i][j];
        }
    }
}

std::vector<bool> TCM::encode(const std::vector<bool> &msg) {
    std::vector<bool> res;
    for (const auto &bit: msg) {
        state += (int)bit << (size_memory - 1);

        for (unsigned int trelli : trellis) {
            auto tmp = trelli & state;
            if (nnz(tmp) % 2 != 0){
                res.push_back(1);
            }
            else{
                res.push_back(0);
            }
        }
        state >>= 1;
    }
    return res;
}

int TCM::nnz(uint32_t n) { //number of 1 in bin(n)
    auto res = 0;
    while (n) {
        n &= n - 1;
        ++res;
    }
    return res;
}
