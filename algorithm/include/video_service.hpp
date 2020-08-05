//
// Created by liuky on 2020-07-31.
//

#ifndef NNIE_TUTORIAL_VIDEO_SERVICE_HPP
#define NNIE_TUTORIAL_VIDEO_SERVICE_HPP

#include "common.hpp"
#include "sdc.hpp"
#include "array_queue.hpp"

#include <hi_comm_svp.h>
#include <hi_nnie.h>

typedef struct
{
    SVP_NNIE_MODEL_S    stModel;
    SVP_MEM_INFO_S      stModelBuf;//store Model file
}SVP_NNIE_MODEL_WITH_FILE_S;


class VideoService {
private:
    int m_fd_video; //sdc的视频服务句柄
    long long m_frame_idx;//用于保存取出数据的帧序号
    uint32_t m_yuv_channel_id; //yuv视频通道id
    ArrayQueue *m_video_queue; //缓存视频数据的队列
    int m_stop_reading;

public:
    explicit VideoService(ArrayQueue *video_queue);

    int get_fd();

    void stop_reading();

    int service_register();

    int get_yuv_channel_id();

    int set_yuv_channel_param(uint32_t width, uint32_t height, uint32_t fps) ;

    int subscribe_video(uint32_t yuv_capacity) ;

    int release_yuv(SDC_YUV_DATA_S *data);

    void* read_camera_data_run();

    int get_data_from_queue(SDC_YUV_DATA_S* yuv_data,int duration_num);

};

#endif //NNIE_TUTORIAL_VIDEO_SERVICE_HPP
