//
// Created by liuky on 2020-08-05.
//

#include <sys/uio.h>
#include <hi_type.h>
#include "utils_service.hpp"

UtilsService::UtilsService(){
    service_register();
}

int UtilsService::get_fd() {
    return m_fd_utils;
}

/*更新内存*/
HI_S32 UtilsService::SDC_FlushCache(HI_U64 u64PhyAddr, HI_VOID *pvVirAddr, HI_U32 u32Size)
{
    HI_S32 s32Ret = HI_SUCCESS;
    SDC_MEM_S sdc_mem_addr;
    sdc_mem_addr.addr_phy = (void *)u64PhyAddr;
    sdc_mem_addr.addr_virt = pvVirAddr;
    sdc_mem_addr.size = u32Size;

    s32Ret = ioctl(m_fd_utils, SRVFS_PHYMEM_CACHEFLUSH, &sdc_mem_addr);

    return s32Ret;
}

int UtilsService::service_register() {
    m_fd_utils = open("/mnt/srvfs/utils.iaas.sdc", O_RDWR);
    if (m_fd_utils < 0) {
        DEBUG_LOG("open video failed, ret is: %i\n", m_fd_utils);
        return ERR;
    }
    return PAS;
}

void UtilsService::SDC_MemFree(SDC_MMZ_ALLOC_S *pstMemParas) {
    SDC_COMMON_HEAD_S head;
    head.version = SDC_VERSION;
    head.url = SDC_URL_MMZ;
    head.method = SDC_METHOD_DELETE;
    head.head_length = sizeof(head);
    head.content_length = sizeof(*pstMemParas);

    struct iovec iov[] = {
            {(void *) &head, sizeof(head)},
            {pstMemParas,    sizeof(*pstMemParas)}
    };

    (void) writev(m_fd_utils, iov, sizeof(iov) / sizeof(iov[0]));
    return;
}

int UtilsService::SDC_MemAlloc(unsigned int size, SDC_MMZ_ALLOC_S *mem_params) {
    /*用于摄像机(SDC)的内存申请函数
     * size: 需要申请的内存大小
     * mem_params: 用于保存申请到的内存信息
     * */

    int ret;
    char buf[1024];
    SDC_COMMON_HEAD_S *head = (SDC_COMMON_HEAD_S*)buf;
    head->version = SDC_VERSION;
    head->url = SDC_URL_MMZ;
    head->method = SDC_METHOD_CREATE;
    head->head_length = sizeof(SDC_COMMON_HEAD_S);
    head->content_length = sizeof(size);

    struct iovec iov[] = {
            {(void *) head, sizeof(SDC_COMMON_HEAD_S)},
            {&size,          sizeof(size)}};
    /*写入请求*/
    ret = writev(m_fd_utils, iov, 2);
    if (ret < 0) return ERR;
    /*传入pstMemParas指针用于接收内存信息*/
    iov[1].iov_base = mem_params;
    iov[1].iov_len = sizeof(SDC_MMZ_ALLOC_S);
    /*读取返回*/
    ret = readv(m_fd_utils, iov, 2);
    if (ret < 0) {
        DEBUG_LOG("ERR:SDC_MemAlloc readv failed,mmz_alloc_cached:1");
        return ERR;
    }
    if (head->code != SDC_CODE_200 || head->head_length != sizeof(SDC_COMMON_HEAD_S) || head->content_length != sizeof(*mem_params)) {
        DEBUG_LOG("ERR:mmz_alloc_cached:2,CODE:%i, mmz_size:%d", head->code, mem_params->size);
        return ERR;
    }
    //判断申请到的内存是否等于模型所需的内存大小
    if(mem_params->size!=size){
        DEBUG_LOG("ERR: Wrong memory size obtained,need: %d, get: %d",size, mem_params->size);
        return ERR;
    }
    return PAS;

}