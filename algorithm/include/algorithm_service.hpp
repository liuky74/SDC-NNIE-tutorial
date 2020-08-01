//
// Created by liuky on 2020-07-31.
//

#ifndef NNIE_TUTORIAL_ALGORITHM_SERVICE_HPP
#define NNIE_TUTORIAL_ALGORITHM_SERVICE_HPP

#include "video_service.hpp"

class AlgorithmService {
private:
    VideoService *m_video_service;
    int m_fd_algorithm=-1; //sdc的算法模块服务句柄
public:
    AlgorithmService(VideoService *video_service);
    int service_register();

    /*将SDC采集到的原始YUV420SP数据转换为RGB数据*/
    int SDC_TransYUV2RGB(SDC_YUV_FRAME_S *yuv, SDC_YUV_FRAME_S *rgb);

    /*转换后的数据内存释放将由Algorithm负责*/
    int SDC_TransYUV2RGBRelease(SDC_YUV_FRAME_S *rgb);


};


#endif //NNIE_TUTORIAL_ALGORITHM_SERVICE_HPP
