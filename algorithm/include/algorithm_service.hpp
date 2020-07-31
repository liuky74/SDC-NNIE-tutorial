//
// Created by liuky on 2020-07-31.
//

#ifndef NNIE_TUTORIAL_ALGORITHM_SERVICE_HPP
#define NNIE_TUTORIAL_ALGORITHM_SERVICE_HPP

#include "video_service.hpp"

class AlgorithmService {
private:
    VideoService *m_video_service;
    int m_fd_algorithm; //sdc的算法模块服务句柄
public:
    AlgorithmService(VideoService *video_service);
    int service_register();
};


#endif //NNIE_TUTORIAL_ALGORITHM_SERVICE_HPP
