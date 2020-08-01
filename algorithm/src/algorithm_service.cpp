//
// Created by liuky on 2020-07-31.
//

#include <cstring>
#include <sys/uio.h>
#include "algorithm_service.hpp"

AlgorithmService::AlgorithmService(VideoService *video_service){
    m_video_service = video_service;
    if(service_register()<0){
        exit(0);
    }
};
int AlgorithmService::service_register() {
    m_fd_algorithm = open("/mnt/srvfs/algorithm.iaas.sdc", O_RDWR);
    if (m_fd_algorithm < 0) {
        DEBUG_LOG("open video failed, ret is: %i\n", m_fd_algorithm);
        return ERR;
    }
    return PAS;
}

int AlgorithmService::SDC_TransYUV2RGB(SDC_YUV_FRAME_S *yuv, SDC_YUV_FRAME_S *rgb) {
    SDC_COMMON_HEAD_S head;
    int nRet;
    struct iovec iov[2];

    // 编写请求头
    memset(&head, 0, sizeof(head));
    head.version = SDC_VERSION;
    head.url = SDC_URL_YUV_TRAN;
    head.method = SDC_METHOD_CREATE;
    head.head_length = sizeof(SDC_COMMON_HEAD_S);
    head.content_length = sizeof(SDC_YUV_FRAME_S);

    iov[0].iov_base = &head;
    iov[0].iov_len = sizeof(head);
    iov[1].iov_base = yuv;
    iov[1].iov_len = sizeof(SDC_YUV_FRAME_S);

    // 写入请求头
    nRet = writev(m_fd_algorithm, iov, sizeof(iov) / sizeof(iovec));
    if (nRet < 0) {
        DEBUG_LOG("Error:failed SDC_TransYUV2RGB,nRet:%d!", nRet);
        return ERR;
    }
    // read response
    iov[1].iov_base = rgb;
    iov[1].iov_len = sizeof(SDC_YUV_FRAME_S);
    nRet = readv(m_fd_algorithm, iov, 2);
    if (head.code != SDC_CODE_200 || nRet < 0 || head.content_length != sizeof(SDC_YUV_FRAME_S)) {
        DEBUG_LOG("ERR:SDC_TransYUV2RGB,nRet:%d,rsp_head.code:%d!",nRet, head.code);
        return ERR;
    }
    return PAS;

}

int AlgorithmService::SDC_TransYUV2RGBRelease(SDC_YUV_FRAME_S *rgb) {
    SDC_COMMON_HEAD_S head;
    int nRet;
    struct iovec iov[2];

    // fill head struct
    memset(&head, 0, sizeof(head));
    head.version = SDC_VERSION;
    head.url = SDC_URL_YUV_TRAN;
    head.method = SDC_METHOD_DELETE;
    head.head_length = sizeof(head);
    head.content_length = sizeof(SDC_YUV_FRAME_S);

    iov[0].iov_base = &head;
    iov[0].iov_len = sizeof(SDC_COMMON_HEAD_S);
    iov[1].iov_base = rgb;
    iov[1].iov_len = sizeof(SDC_YUV_FRAME_S);

    // write request
    nRet = writev(m_fd_algorithm, iov, sizeof(iov) / sizeof(iovec));
    if (nRet < 0) {
        DEBUG_LOG("ERR:failed SDC_TransYUV2RGBRelease,nRet:%d!", nRet);
        return ERR;}

    return PAS;
}
