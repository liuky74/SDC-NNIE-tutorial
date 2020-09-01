//
// Created by liuky on 2020-07-31.
//

#ifndef NNIE_TUTORIAL_ALGORITHM_SERVICE_HPP
#define NNIE_TUTORIAL_ALGORITHM_SERVICE_HPP


#include "video_service.hpp"
#include "utils_service.hpp"
#include "event_service.hpp"

class AlgorithmService {
private:
    VideoService *m_video_service;
    UtilsService *m_utils_service;
    int m_fd_algorithm=-1; //sdc的算法模块服务句柄
    SVP_NNIE_MODEL_WITH_FILE_S m_model;
public:

    SVP_NNIE_MODEL_WITH_FILE_S *get_model();

    AlgorithmService(VideoService *video_service,UtilsService *utils_service);
    int service_register();

    /*将SDC采集到的原始YUV420SP数据转换为RGB数据*/
    int SDC_TransYUV2RGB(SDC_YUV_FRAME_S *yuv, SDC_YUV_FRAME_S *rgb);

    /*转换后的数据内存释放将由Algorithm负责*/
    int SDC_TransYUV2RGBRelease(SDC_YUV_FRAME_S *rgb);

    int SDC_UnLoadModel(SVP_NNIE_MODEL_S *pstModel);

    int SDC_load_model(const char* model_file_name,unsigned int load_mode);

    int SDC_ModelDecript(SDC_MMZ_ALLOC_S *pstMmzAddr);

    int SDC_Nnie_Forward(SDC_NNIE_FORWARD_S *p_sdc_nnie_forward);

};


#endif //NNIE_TUTORIAL_ALGORITHM_SERVICE_HPP
