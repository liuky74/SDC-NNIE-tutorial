//
// Created by liuky on 2020-07-31.
//

#include <cstring>
#include <sys/uio.h>
#include <unistd.h>
#include "algorithm_service.hpp"
//#include "utils_service.hpp"

AlgorithmService::AlgorithmService(VideoService *video_service,UtilsService *utils_service){
    m_video_service = video_service;
    m_utils_service = utils_service;
    if(service_register()<0){
        exit(0);
    }
};

int AlgorithmService::SDC_ModelDecript(SDC_MMZ_ALLOC_S *pstMmzAddr)
{
    if(pstMmzAddr == NULL)
    {
        DEBUG_LOG("ERR:Err in SDC_ModelDecript, pstMmzAddr is null\n");
        return ERR;
    }
    return PAS;
}

int AlgorithmService::SDC_load_model(const char *model_file_name,unsigned int load_mode=1) {
    /*模型读取,分为以下步骤:
     * 1 读取模型文件
     * 2 申请SDC内存
     * 3 将模型文件拷贝到SDC申请的内存中
     * 4 将SDC内存中的模型文件解析为NNIE结构的对象(SVP_NNIE_MODEL_S)
     * 5 将解析后的NNIE模型对象保存到成员变量中
     * */
    if(model_file_name == NULL){
        DEBUG_LOG("ERR:SDC_load_model,model_file_name is null");
        return ERR;
    }

    int ret;
    char buf[1024]={0};
    unsigned int file_size;/*记录模型文件的大小*/
    SDC_MMZ_ALLOC_S mmz_addr;/*保存申请到的内存信息(虚拟地址/物理地址)*/
    /*写入通讯头*/
    SDC_COMMON_HEAD_S *common_head=(SDC_COMMON_HEAD_S*)buf;
    common_head->version = SDC_VERSION;
    common_head->url = SDC_URL_NNIE_MODEL;
    common_head->method = SDC_METHOD_CREATE;
    common_head->head_length = sizeof(SDC_COMMON_HEAD_S);
    common_head->content_length = MAX_MODULE_PATH;
    SDC_EXTEND_HEAD_S *extend_head;

    /*声明一个结构体用于保存返回值*/
    struct rsp_struct{
        SDC_COMMON_HEAD_S head;
        SVP_NNIE_MODEL_S model;
    } rsp_s;
    /*声明一个通讯用的结构体,根据读取模式的不同会对该对象修改*/
    struct iovec iov[2]={
            {buf, sizeof(SDC_COMMON_HEAD_S)+ sizeof(SDC_EXTEND_HEAD_S)},/*请求报头*/
            {NULL, MAX_MODULE_PATH}/*请求报文内容*/
    };

    DEBUG_LOG("loading model, model name: %s",model_file_name);
    /*模式 1，本文使用的方法,带扩展头，扩展头参数指定为内存方式加载*/
    if(load_mode == 1){
/*---1 读取模型文件----------------------------------------------------------------------------------------------------*/
        FILE *fp = fopen(model_file_name, "rb");/*打开模型文件*/
        if(fp == NULL)
        {
            DEBUG_LOG("modelfile fopen %s fail!", model_file_name);
            return ERR;
        }
        ret = fseek(fp,0L,SEEK_END);/*将文件指针调整到文件末尾*/
        if(ret != 0)
        {
            DEBUG_LOG("check nnie file SEEK_END, fseek fail.");
            fclose(fp);
            return ERR;
        }
        file_size = ftell(fp);/*计算文件头到指针之间的字节数,即为文件的字节大小,注意上文已经将指针调整到文件末尾*/
        ret = fseek(fp,0L,SEEK_SET);/*重新将指针移动到文件头*/
        if(0 != ret)
        {
            DEBUG_LOG("check nnie file SEEK_SET, fseek fail.");
            fclose(fp);
            return ERR;
        }
/*---2 根据获取的模型文件大小申请SDC内存--------------------------------------------------------------------------------*/
        mmz_addr.size = file_size;
        ret = m_utils_service->SDC_MemAlloc(file_size,&mmz_addr);
        /*判断得到的内存大小是否与申请的相等*/
        if(ret != mmz_addr.size){
            DEBUG_LOG("ERR:SDC_MmzAlloc ret %d, readsize %d", ret, mmz_addr.size);
            return ERR;
        }
/*---3 打开mode file文件句柄fp,将模型文件拷贝到SDC申请的内存中-----------------------------------------------------------*/
        ret = fread((HI_VOID*)(uintptr_t)mmz_addr.addr_virt, 1, mmz_addr.size, fp);
        /*二次判断申请到的内存地址是否充足*/
        if(ret != mmz_addr.size)
        {
            DEBUG_LOG("ERR:filesize %d, readsize %d", ret, mmz_addr.size);
            return ERR;
        }
        /*如果模型文件用户自己进行过加密,则这里可以开始解密*/
        if(SDC_ModelDecript(&mmz_addr)!=PAS)
        {
            DEBUG_LOG("SDC_ModelDecript Fail!");
            return ERR;
        }
        /*编辑扩展头,*/
        extend_head = (SDC_EXTEND_HEAD_S*)(buf+common_head->head_length);
        extend_head->type = 1;
        extend_head->length = sizeof(SDC_EXTEND_HEAD_S);
        extend_head->reserve = 0;/*0 或者不带是内存方式，1 是文件名方式*/
        common_head->head_length+= sizeof(SDC_EXTEND_HEAD_S);/*将扩展头添加到报文头中*/
        iov[1].iov_base = &mmz_addr;/*保存有模型文件内容的SDC内存地址*/

    } else{
        DEBUG_LOG("ERR: wrong load_mode");
        return ERR;
    }

/*---4 写入请求,将SDC内存中的模型文件解析为NNIE网络结构并加载到SDC中-----------------------------------------------------*/
    ret = writev(m_fd_algorithm,iov,2);
    if (ret < 0) DEBUG_LOG("ERR:creat nnie,write to algorithm.iaas.sdc fail: %m");
    /*读取加载后的返回值,保存在rsp_s中*/
    ret = read(m_fd_algorithm, &rsp_s, sizeof(rsp_s));
    /*错误检查*/
    if(ret == ERR)
    {
        DEBUG_LOG("ERR:get_channel_data fail: %m");
        return ERR;
    }
    if(ret > sizeof(rsp_s))
    {
        DEBUG_LOG("ERR: get_channel_data truncated, data len: %d > %zu", ret, sizeof(rsp_s));
        return ERR;
    }
    if (ret < 0 || rsp_s.head.code != SDC_CODE_200 || rsp_s.head.content_length <= 0)
    {
        DEBUG_LOG("ERR: get nnie create response, read from algorithm.iaas.sdc fail,s32Ret:%d, code=%d,length=%d",
                ret, rsp_s.head.code, rsp_s.head.content_length);
    }
    else
    {
/*---5 将加载成功的模型保存到成员变量m_model中(以地址的形式)-------------------------------------------------------------*/
        memcpy(&m_model.stModel, &rsp_s.model,sizeof(SVP_NNIE_MODEL_S));
//        memcpy(pstModel, &rsp_s.model,sizeof(SVP_NNIE_MODEL_S));
    }
    return PAS;

}

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
