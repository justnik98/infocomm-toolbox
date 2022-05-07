//
// Created by ankolesn on 26.04.22.
//

#include <valarray>
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
        state >>= 1;
        state += (int) bit << (size_memory - 1);

        for (unsigned int trelli: trellis) {
            auto tmp = trelli & state;
            if (nnz(tmp) % 2 != 0) {
                res.push_back(1);
            } else {
                res.push_back(0);
            }
        }
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

std::vector<bool> TCM::vitdec(const std::vector<bool> &msg) {
    std::vector<bool> res;

    class node {
    public:
        size_t d_min = INT32_MAX;
        std::vector<bool> msg;
    };

    std::vector<node> prev(pow(2, size_memory));
    std::vector<node> cur(pow(2, size_memory));
    for (auto i = 0; i < prev.size(); ++i) {
        prev[i].msg.resize(msg.size() / trellis.size());
        cur[i].msg.resize(msg.size() / trellis.size());
    }
    prev[0].d_min = 0;
    auto k = 0;
    while (k != msg.size()) {
        for (int i = 0; i < prev.size(); ++i) {
            if (prev[i].d_min == INT32_MAX) continue;
            auto st0 = i >> 1; // состояние
            auto st1 = i >> 1;
            // case 0
            st0 += 0 << (size_memory - 1);
            auto new_d = prev[i].d_min;
            auto new_msg = prev[i].msg;
            auto j = 0;
            for (unsigned int trelli: trellis) {
                auto tmp = trelli & st0;
                if (nnz(tmp) % 2 != 0) {
                    new_d += 1 ^ (int) msg[k + j];
                } else {
                    new_d += 0 ^ (int) msg[k + j];
                }
                ++j;
            }
            if (cur[st0].d_min > new_d) {
                cur[st0].d_min = new_d;
                cur[st0].msg = prev[i].msg;
                cur[st0].msg[k / trellis.size()] = 0;
            }
            //case 1
            st1 += 1 << (size_memory - 1);
            new_d = prev[i].d_min;
            new_msg = prev[i].msg;
            j = 0;
            for (unsigned int trelli: trellis) {
                auto tmp = trelli & st1;
                if (nnz(tmp) % 2 != 0) {

                    new_d += 1 ^ (int) msg[k + j];
                } else {

                    new_d += 0 ^ (int) msg[k + j];
                }
                ++j;
            }
            if (cur[st1].d_min > new_d) {
                cur[st1].d_min = new_d;
                cur[st1].msg = prev[i].msg;
                cur[st1].msg[k / trellis.size()] = 1;
            }
        }
        k += trellis.size();
        prev = cur;
        cur = std::vector<node>(cur.size());
        for (auto i = 0; i < prev.size(); ++i) {
            cur[i].msg.resize(msg.size() / 2);
        }
    }
    size_t d_min = INT32_MAX;
    size_t i_min = 0;
    for (int i = 0; i < prev.size(); ++i) {
        if (prev[i].d_min < d_min) {
            d_min = prev[i].d_min;
            i_min = i;
        }
    }
    return prev[i_min].msg;
}

std::vector<bool> TCM::vitdec(const std::vector<double> &msg) {
    std::vector<bool> res;

    class node {
    public:
        double d_max = 0;
        std::vector<bool> msg;
    };

    std::vector<node> prev(pow(2, size_memory));
    std::vector<node> cur(pow(2, size_memory));
    for (auto i = 0; i < prev.size(); ++i) {
        prev[i].msg.resize(msg.size() / trellis.size());
        cur[i].msg.resize(msg.size() / trellis.size());
    }
    prev[0].d_max = 0;
    auto k = 0;
    while (k != msg.size()) {
        for (int i = 0; i < prev.size(); ++i) {
            auto st0 = i >> 1; // состояние
            auto st1 = i >> 1;
            // case 0
            st0 += 0 << (size_memory - 1);
            auto new_d = prev[i].d_max;
            auto new_msg = prev[i].msg;
            auto j = 0;
            for (unsigned int trelli: trellis) {
                auto tmp = trelli & st0;
                if (nnz(tmp) % 2 != 0) {
                    if (msg[k + j] > 0) {
                        new_d -= std::abs(msg[k + j]);
                    } else {
                        new_d += std::abs(msg[k + j]);
                    }
                } else {
                    if (msg[k + j] <= 0) {
                        new_d -= std::abs(msg[k + j]);
                    } else {
                        new_d += std::abs(msg[k + j]);
                    }
                }
                ++j;
            }
            if (cur[st0].d_max < new_d) {
                cur[st0].d_max = new_d;
                cur[st0].msg = prev[i].msg;
                cur[st0].msg[k / trellis.size()] = 0;
            }
            //case 1
            st1 += 1 << (size_memory - 1);
            new_d = prev[i].d_max;
            new_msg = prev[i].msg;
            j = 0;
            for (unsigned int trelli: trellis) {
                auto tmp = trelli & st1;
                if (nnz(tmp) % 2 != 0) {
                    if (msg[k + j] > 0) {
                        new_d -= std::abs(msg[k + j]);
                    } else {
                        new_d += std::abs(msg[k + j]);
                    }
                } else {
                    if (msg[k + j] <= 0) {
                        new_d -= std::abs(msg[k + j]);
                    } else {
                        new_d += std::abs(msg[k + j]);
                    }
                }
                ++j;
            }
            if (cur[st1].d_max < new_d) {
                cur[st1].d_max = new_d;
                cur[st1].msg = prev[i].msg;
                cur[st1].msg[k / trellis.size()] = 1;
            }
        }
        k += trellis.size();
        prev = cur;
        cur = std::vector<node>(cur.size());
        for (auto i = 0; i < prev.size(); ++i) {
            cur[i].msg.resize(msg.size() / 2);
        }
    }
    double d_max = 0;
    size_t i_min = 0;
    for (int i = 0; i < prev.size(); ++i) {
        if (prev[i].d_max > d_max) {
            d_max = prev[i].d_max;
            i_min = i;
        }
    }
    return prev[i_min].msg;


}
