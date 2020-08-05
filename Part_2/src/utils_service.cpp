//
// Created by liuky on 2020-08-05.
//

#include <sys/uio.h>
#include "utils_service.hpp"

UtilsService::UtilsService(){
    service_register();
}

int UtilsService::service_register() {
    m_fd_util = open("/mnt/srvfs/utils.iaas.sdc", O_RDWR);
    if (m_fd_util < 0) {
        DEBUG_LOG("open video failed, ret is: %i\n", m_fd_util);
        return ERR;
    }
    return PAS;
}

int UtilsService::SDC_MemAlloc(unsigned int size, SDC_MMZ_ALLOC_S *mem_params) {
    /*用于摄像机(SDC)的内存申请函数
     * size: 需要申请的内存大小
     * mem_params: 用于保存申请到的内存信息
     * */

//    SDC_COMMON_HEAD_S head = {0};
//    head.version = SDC_VERSION;
//    head.url = SDC_URL_MMZ;
//    head.method = SDC_METHOD_CREATE;
//    head.head_length = sizeof(head);// + sizeof(cached_head),
//    head.content_length = sizeof(size);
//
//    struct iovec iov[] = {
//            { (void*)&head, sizeof(head) },
//            //{ (void*)&cached_head, sizeof(cached_head) },
//            { &size, sizeof(size) }
//    };
//
//
//    int nret = writev(m_fd_util, iov, 2);
//    if(nret < 0) return ERR;
//    //fprintf(stdout,"mmz_alloc_cached:1\n");
//
//    iov[1].iov_base = mem_params;
//    iov[1].iov_len = sizeof(*mem_params);
//
//    nret = readv(m_fd_util, iov,2);
//    if(nret < 0)
//    {
//        fprintf(stdout,"mmz_alloc_cached:1\n");
//        return ERR;
//    }
//    //fprintf(stdout,"mmz_alloc_cached:2\n");
//
//    if(head.code != SDC_CODE_200 || head.head_length != sizeof(head) || head.content_length != sizeof(*mem_params))
//    {
//        fprintf(stdout,"mmz_alloc_cached:2,size:%d\n", mem_params->size);
//        return ERR;
//    }
//    //fprintf(stdout,"mmz succeed mmz_alloc_cached:size:%d\n",size);
//    return size;

    int ret;
    char buf[1024];
    SDC_COMMON_HEAD_S *head = (SDC_COMMON_HEAD_S*)buf;
    head->version = SDC_VERSION;
    head->url = SDC_URL_MMZ;
    head->method = SDC_METHOD_CREATE;
    head->head_length = sizeof(SDC_COMMON_HEAD_S);
    head->content_length = sizeof(size);

    //    SDC_COMMON_HEAD_S head = {0};
//    head.version = SDC_VERSION;
//    head.url = SDC_URL_MMZ;
//    head.method = SDC_METHOD_CREATE;
//    head.head_length = sizeof(head);// + sizeof(cached_head),
//    head.content_length = sizeof(size);

    struct iovec iov[] = {
            {(void *) head, sizeof(SDC_COMMON_HEAD_S)},
            {&size,          sizeof(size)}};
    /*写入请求*/
    ret = writev(m_fd_util, iov, 2);
    if (ret < 0) return ERR;
    /*传入pstMemParas指针用于接收内存信息*/
    iov[1].iov_base = mem_params;
    iov[1].iov_len = sizeof(SDC_MMZ_ALLOC_S);
    /*读取返回*/
    ret = readv(m_fd_util, iov, 2);
    if (ret < 0) {
        DEBUG_LOG("ERR:SDC_MemAlloc readv failed,mmz_alloc_cached:1");
        return ERR;
    }
    if (head->code != SDC_CODE_200 || head->head_length != sizeof(SDC_COMMON_HEAD_S) || head->content_length != sizeof(*mem_params)) {
        DEBUG_LOG("ERR:mmz_alloc_cached:2,CODE:%i, mmz_size:%d", head->code, mem_params->size);
        return ERR;
    }
    return size;

}