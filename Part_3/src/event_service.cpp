//
// Created by liuky on 2020-08-12.
//

#include <sys/uio.h>
#include <sys/mman.h>
#include "event_service.hpp"

EventService::EventService(char *app_name) {
    service_register();
    m_app_name = app_name;
}
int EventService::service_register() {
    m_fd_event = open("/mnt/srvfs/event.paas.sdc", O_RDWR);
    if (m_fd_event < 0) {
        DEBUG_LOG("open event failed, ret is: %i\n", m_fd_event);
        return ERR;
    }
    m_fd_cache = open("/dev/cache",O_RDWR);
    if (m_fd_cache < 0) {
        DEBUG_LOG("open event failed, ret is: %i\n", m_fd_cache);
        return ERR;
    }
    return PAS;
}

int EventService::get_fd() {
    return m_fd_event;
}

int EventService::SDC_LabelEventDel(unsigned int baseid, unsigned int id) {
    int nDataLen;
    int nResult;
    char *pcTemp = NULL;

    paas_shm_cached_event_s shm_event;
    SDC_EXTEND_HEAD_S shm_head = {
            .type = SDC_HEAD_SHM_CACHED_EVENT,
            .length = 8,
    };

    SDC_COMMON_HEAD_S head;
    head.version = SDC_VERSION;
    head.url = SDC_URL_PAAS_EVENTD_EVENT;
    head.method = SDC_METHOD_CREATE;
    head.head_length = sizeof(head) + sizeof(shm_head);
    head.content_length = sizeof(shm_event);

    struct iovec iov[3];
    iov[0].iov_base = &head;
    iov[0].iov_len = sizeof(head);
    iov[1].iov_base = &shm_head;
    iov[1].iov_len = sizeof(shm_head);
    iov[2].iov_base = &shm_event;
    iov[2].iov_len = sizeof(shm_event);

    SDC_SHM_CACHE_S shm_cache;
    memset(&shm_cache, 0, sizeof(shm_cache));

    LABEL_EVENT_DATA_S *pevent = NULL;
    nDataLen = sizeof(label);
    shm_cache.size = sizeof(LABEL_EVENT_DATA_S) + nDataLen;
    shm_cache.ttl = 0;
    //printf("ioctl fail\n");

    nResult = ioctl(m_fd_cache, SDC_CACHE_ALLOC, &shm_cache);
    if (nResult != 0) {
        printf("ioctl fail\n");
        goto EVENT_FAIL;
    }
    pevent = (LABEL_EVENT_DATA_S *) shm_cache.addr_virt;

    pevent->data = (char *) pevent + sizeof(LABEL_EVENT_DATA_S);
    pevent->base.id = baseid;

    (void) sprintf(pevent->base.name, "%s", ("tag.saas.sdc"));

    pevent->base.length = nDataLen;
    memset(pevent->data, 0, sizeof(nDataLen));
    pcTemp = pevent->data;

    *(uint32_t *) pcTemp = 0;//add
    pcTemp += sizeof(uint32_t);

    strcpy_s(pcTemp, 32, m_app_name); //app name
    pcTemp += 32;

    *(uint64_t *) pcTemp = id;

    shm_event.addr_phy = shm_cache.addr_phy;
    shm_event.size = shm_cache.size;
    shm_event.cookie = shm_cache.cookie;
    nResult = writev(m_fd_event, iov, 3);
    if (nResult == -1) {
        printf("ioctl fail\n");
        goto EVENT_FAIL;
    }
    munmap(pevent, sizeof(LABEL_EVENT_DATA_S) + nDataLen);

    return 0;
    EVENT_FAIL:
    if (pevent) {
        munmap(pevent, sizeof(LABEL_EVENT_DATA_S) + nDataLen);
    }

    return -1;

}
int EventService::SDC_LabelEventPublish(unsigned int baseid, int iDataLen, char *cEventMsg, uint64_t pts)
{
    /*pts 是yuv_420sp的影像地址*/
    int nResult;
    paas_shm_cached_event_s shm_event;
    SDC_EXTEND_HEAD_S shm_head = {
            .type = SDC_HEAD_SHM_CACHED_EVENT,
            .length = 8,
    };

    SDC_COMMON_HEAD_S head;
    head.version = SDC_VERSION;
    head.url = SDC_URL_PAAS_EVENTD_EVENT;
    head.method = SDC_METHOD_CREATE;
    head.head_length = sizeof(head) + sizeof(shm_head);
    head.content_length = sizeof(shm_event);

    struct iovec iov[3];
    iov[0].iov_base = &head;
    iov[0].iov_len = sizeof(head);
    iov[1].iov_base = &shm_head;
    iov[1].iov_len = sizeof(shm_head);
    iov[2].iov_base = &shm_event;
    iov[2].iov_len = sizeof(shm_event);


    SDC_SHM_CACHE_S shm_cache;
    memset(&shm_cache, 0, sizeof(shm_cache));

    LABEL_EVENT_DATA_S * pevent = NULL;
    //nDataLen= sizeof(label) + uiPolygonNum * sizeof(polygon) + iPointNum * sizeof(point) + (uiTagNum - '0')*sizeof(tag) + iStrNum;
    shm_cache.size  = sizeof(LABEL_EVENT_DATA_S) + iDataLen;
    nResult = ioctl(m_fd_cache, SDC_CACHE_ALLOC,&shm_cache);
    if(nResult != 0)
    {
        printf("ioctl fail\n");
        goto EVENT_FAIL;
    }
    pevent = (LABEL_EVENT_DATA_S *)shm_cache.addr_virt;
    pevent->data = (char *)pevent + sizeof(LABEL_EVENT_DATA_S);
    pevent->base.id = baseid;
    pevent->base.src_timestamp = pts;
    pevent->base.tran_timestamp = pts + 10;/*默认填写*/
    (void)sprintf(pevent->base.name, "%s", "tag.saas.sdc");
    (void)sprintf(pevent->base.publisher, "%s", "test");

    pevent->base.length = iDataLen;
    memcpy_s(pevent->data, iDataLen, cEventMsg, iDataLen);

    //printf("length= %d\n",iDataLen);

    shm_event.addr_phy = shm_cache.addr_phy;
    shm_event.size = shm_cache.size;
    shm_event.cookie = shm_cache.cookie;
    nResult = writev(m_fd_event, iov, 3);
    if(nResult == -1)
    {
        printf("writev fail\n");
        goto EVENT_FAIL;
    }
    munmap(pevent, sizeof(LABEL_EVENT_DATA_S) + iDataLen);

    return 0;
    EVENT_FAIL:
    if(pevent)
    {
        munmap(pevent, sizeof(LABEL_EVENT_DATA_S) + iDataLen);
    }

    return -1;

}
