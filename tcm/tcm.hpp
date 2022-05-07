//
// Created by ankolesn on 26.04.22.
//

#ifndef INFOCOMM_TOOLBOX_TCM_HPP
#define INFOCOMM_TOOLBOX_TCM_HPP
#include <vector>

#include <cstdint>

class TCM {
private:
    uint32_t state = 0;
    uint32_t size_memory = 0;
    std::vector<uint32_t> trellis;

    int nnz(uint32_t n);

public:
    explicit TCM(const std::vector<std::vector<int>>& tr);

    std::vector<bool> encode (const std::vector<bool> &msg);

    std::vector<bool> vitdec (const std::vector<bool> &msg);

    std::vector<bool> vitdec (const std::vector<double> &msg);

};


#endif //INFOCOMM_TOOLBOX_TCM_HPP
