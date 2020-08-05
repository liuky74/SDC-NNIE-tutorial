//
// Created by liuky on 2020-08-05.
//

#ifndef NNIE_TUTORIAL_UTILS_SERVICE_HPP
#define NNIE_TUTORIAL_UTILS_SERVICE_HPP

#include "common.hpp"
#include "sdc.hpp"


class UtilsService {
private:
    int m_fd_util=-1;

public:
    UtilsService();
    int service_register();
    int SDC_MemAlloc(unsigned int size, SDC_MMZ_ALLOC_S* mem_params);


};


#endif //NNIE_TUTORIAL_UTILS_SERVICE_HPP
