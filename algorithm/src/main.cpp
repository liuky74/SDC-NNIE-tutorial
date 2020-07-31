#include <iostream>
#include <unistd.h>
#include <thread>
#include <video_service.hpp>
#include "common.hpp"
#include "array_queue.hpp"

using namespace std;


int main() {
    ArrayQueue array_queue(25, sizeof(SDC_YUV_DATA_S));
    /* 构造函数会执行 注册服务 + 申请yuv_channel id + 导入队列*/
    VideoService video_service(&array_queue);
    //设定视频通道的参数
    video_service.set_yuv_channel_param(640, 480, 25);
    //订阅数据
    video_service.subscribe_video(25);
    //使用线程将订阅的数据不停的保存到数组队列中
    std::thread video_thread(&VideoService::read_camera_data_run,&video_service);
    //取出数据并释放
    int duration_num=1;//每次只取一帧数据
    SDC_YUV_DATA_S yuv_data[duration_num];
    int loop_condition=1,ret;

    while(loop_condition){
        ret=video_service.get_data_from_queue(yuv_data,duration_num);
        /*如果能正常取出数据,则打印数据的内存地址*/
        if (ret==PAS){
            DEBUG_LOG("addr_virt: %lu",yuv_data[0].frame.addr_virt);
            /*释放数据的内存空间,注意因为我们只取了一帧数据所以释放时是单个元素释放*/
            video_service.release_yuv(&yuv_data[0]);
        }
        //我们一秒取25帧,也就是40000微妙一帧,为了更好的观测到队列为空时的返回值,所以延迟30000微妙
        usleep(30000);

    }

    while (1){
        sleep(5);
    }

    printf("End\n");
}