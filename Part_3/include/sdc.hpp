//
// Created by liuky on 2020-07-30.
//

#ifndef NNIE_TUTORIAL_SDC_HPP
#define NNIE_TUTORIAL_SDC_HPP

#include <cstdint>
#include <hi_nnie.h>
#include "sys/ioctl.h"
#include "common.hpp"

/**
类型转定义
**/

typedef           char			CHAR;
typedef  unsigned char			UCHAR;
typedef signed char				INT8;
typedef unsigned char			UINT8;
typedef signed short			INT16;
typedef unsigned short			UINT16;
typedef signed int				INT32;
typedef unsigned int			UINT32;
typedef signed long long		INT64;
typedef unsigned long long		UINT64;

/**
* video.iaas.sdc服务的数据结构定义
*/

/* YUV Channel的数据格式定义*/
#define SDC_URL_YUV_CHANNEL 	0x00//通道URL
#define SDC_URL_YUV_DATA		0x01//数据URL
#define SDC_URL_YUV_TRAN        0x03//转换URL
/*---algorithm.iaas.sdc---*/
#define SDC_URL_NNIE_MODEL 0x00
#define SDC_URL_NNIE_FORWARD 0x01
#define SDC_URL_NNIE_FORWARD_BBOX 0x02
/*---utils.iaas.sdc*/
#define SDC_URL_MMZ	101
/*---event.paas.sdc*/
#define SDC_URL_PAAS_EVENTD_EVENT 0
#define SDC_HEAD_SHM_CACHED_EVENT 0xFFFF

#define SDC_HEAD_YUV_CACHED_COUNT_MAX 	0x01

#define SDC_YUV_420SP       0x00

#define SDC_VERSION 0x5331

#define SDC_METHOD_CREATE 1
#define SDC_METHOD_GET 2
#define SDC_METHOD_UPDATE 3
#define SDC_METHOD_DELETE 4

#define SDC_CODE_200	200 //正常返回
#define SDC_CODE_400	400
#define SDC_CODE_401	401
#define SDC_CODE_403	403
#define SDC_CODE_500	500 //服务内部错误
#define SDC_CODE_509	500 //缓冲区阻塞


#define MAX_MODULE_PATH 100


typedef struct
{
    uint16_t        version;
    uint8_t         url_ver;
#if defined(__BYTE_ORDER__) && defined(__ORDER_LITTLE_ENDIAN__) && defined(__ORDER_BIG_ENDIAN__)
#if (__BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__)
    uint8_t         method: 7;
    uint8_t         response: 1;
#elif (__BYTE_ORDER__ == __ORDER_BIG_ENDIAN__)
    uint8_t         response: 1;
        uint8_t         method: 7;
#else
#error "unknown __BYTE_ORDER__"
#endif
#else
#error "don't define __BYTE_ORDER__ or __ORDER_LITTLE_ENDIAN__ or __ORDER_BIG_ENDIAN__"
#endif
    uint16_t        url;
    uint16_t        code;
    uint16_t        head_length;
    uint16_t        trans_id;
    uint32_t        content_length;
} SDC_COMMON_HEAD_S;

typedef struct
{
    uint16_t type;
    uint16_t length;
    uint32_t reserve;
}SDC_EXTEND_HEAD_S;

typedef struct
{
    uint32_t channel;
}SDC_CHAN_QUERY_S;

typedef struct
{
    uint32_t width;
    uint32_t height;
}SDC_RESOLUTION_S;

typedef struct
{
    uint32_t channel;
    uint32_t width;
    uint32_t height;
    uint32_t fps;/*取0表使用缺省帧率*/
    uint32_t on_off;/*取0表示关闭,取1表示开启通道*/
    uint32_t format; // YUV_420SP
} SDC_YUV_CHANNEL_PARAM_S;

typedef struct
{
    SDC_YUV_CHANNEL_PARAM_S param;
    SDC_RESOLUTION_S max_resolution;/*通道支持的最大分辨率*/
    uint32_t is_snap_channel;/*是否为抓拍通道*/
    uint32_t src_id;
    uint32_t subscribe_cnt;/*通道的订阅量,大于1表示有多个线程订阅了同一个通道*/
    uint32_t nResolutionModitfy;/*此通道分辨率是否支持修改，0不支持修改，1支持修改*/
}SDC_YUV_CHANNEL_INFO_S;

typedef struct
{
    uint64_t addr_phy; /*虚拟地址,映射向数据的物理地址*/
    uint64_t addr_virt;/*物理地址,实际保存数据的内存地址*/
    uint32_t size;
    uint32_t width;
    uint32_t height;
    uint32_t stride;/*最后一个维度的步长,在shape=CxHxW,数据类型为UINT8的情况下stride=Widtch*sizeof(UINT8)*/
    uint32_t format; /*YUV_420SP*/
    uint32_t reserve;
    uint32_t cookie[4];
}SDC_YUV_FRAME_S;

typedef struct
{
    uint32_t channel;
    uint32_t reserve;
    uint64_t pts;
    uint64_t pts_sys;
    SDC_YUV_FRAME_S frame;
} SDC_YUV_DATA_S;

typedef struct sdc_nnie_forward_ctrl_stru
{
    uint32_t netseg_id;
    uint32_t max_batch_num;
    uint32_t max_bbox_num;
    uint32_t reserve;
}SDC_NNIE_FORWARD_CTRL_S;

typedef struct
{
    SVP_NNIE_MODEL_S model;
    SDC_NNIE_FORWARD_CTRL_S forward_ctrl;
    SVP_SRC_BLOB_S astSrc[16];
    SVP_DST_BLOB_S astDst[16];
}SDC_NNIE_FORWARD_S;

typedef struct
{
    UINT32 uWidth;
    UINT32 uHeight;

    //VW_PIXEL_FORMAT_E enPixelFormat;
    int enPixelFormat;
    /*RGB三通道,各个通道的物理内存位置指针*/
    UINT64 ulPhyAddr[3];
    /*RGB三通道,各个通道的虚拟内存位置指针*/
    UINT64 ulVirAddr[3];
    /*RGB三通道,各个通道的内存步长*/
    UINT32 uStride[3];

    UINT64 ullpts;

    UINT32 uVbBlk;
    UINT32 uPoolId;
    char* pYuvImgAddr;
    UINT32 uFrmSize;

} VW_YUV_FRAME_S;

typedef struct
{
    uint64_t addr_phy;
    uint64_t addr_virt;
    uint32_t size;
    uint32_t reserve;
    uint32_t cookie[4];
} SDC_MMZ_ALLOC_S;

typedef struct
{
    void* addr_phy;
    void* addr_virt;
    unsigned int size;
} SDC_MEM_S;

typedef struct
{
    uint64_t addr_phy;
    uint32_t size;
    uint32_t cookie;
}paas_shm_cached_event_s;


typedef struct
{
    void* addr_virt;
    unsigned long addr_phy;
    unsigned int size;
    unsigned int cookie;
    int ttl;
}SDC_SHM_CACHE_S;

typedef struct
{
    char publisher[16];   //发送事件的服务标识，调测使用
    char name[16];      //事件唯一标识，建议同域名定义避免冲突
    uint64_t src_timestamp;  //发生时的时间，单位毫秒（CLOCK_MONOTONIC时间）
    uint64_t tran_timestamp; //服务转发的时间，单位毫秒（CLOCK_MONOTONIC时间）
    uint32_t id;        //建议同IP地址一样管理，不同前缀对应事件分类，方便分类订阅。
    uint32_t length;   //事件内容的长度.
    char data[0];
}paas_event_s;

typedef struct
{
    paas_event_s base;
    char* data;
}LABEL_EVENT_DATA_S;


#define SRVFS_FT_PHYMEM 5
#define SDC_FT_CACHE 7

#define SRVFS_PHYMEM_CACHEFLUSH _IOW(SRVFS_FT_PHYMEM,0x03,SDC_MEM_S)
#define SDC_CACHE_ALLOC _IOR(SDC_FT_CACHE,0x00, SDC_SHM_CACHE_S)

#endif //NNIE_TUTORIAL_SDC_HPP
