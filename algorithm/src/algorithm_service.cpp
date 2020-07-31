//
// Created by liuky on 2020-07-31.
//

#include "algorithm_service.hpp"

AlgorithmService::AlgorithmService(VideoService *video_service){
    m_video_service = video_service;
    service_register();
};
int AlgorithmService::service_register() {
    m_fd_algorithm = open("/mnt/srvfs/algorithm.iaas.sdc", O_RDWR);
    if (m_fd_algorithm < 0) {
        DEBUG_LOG("open video failed, ret is: %i\n", m_fd_algorithm);
        return ERR;
    }
    return PAS;
}
