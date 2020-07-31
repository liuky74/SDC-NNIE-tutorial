//
// Created by liuky on 2020-07-31.
//
#include <pthread.h>
#include <cstring>
#include <cstdio>
#include "array_queue.hpp"

ArrayQueue::ArrayQueue(int capacity, int item_size) {
    pthread_mutex_init(&m_mutex, NULL);
    m_read_idx = 0;
    m_write_idx = 0;
    m_data_idx = 0;
    m_capacity = capacity+1;
    m_item_size = item_size;
    m_buff = new char[m_capacity * m_item_size];
}
ArrayQueue::~ArrayQueue() {
    delete m_buff;
}

int ArrayQueue::put(void *item) {
    /*先判断+1后是否队列已满,不为满则添加数据*/
    pthread_mutex_lock(&m_mutex);
    /*整体数据下标这个参数用于判断我们是否由于处理不及时漏掉了一部分视频帧,因此无论如何都要+1*/
    m_data_idx++;
    int ret = PAS;
    int next = (m_capacity + m_write_idx + 1) % m_capacity;
    if (next == m_read_idx) {
        ret = QUEUE_FULL;
    } else {
        void *ptr = m_buff + m_write_idx * m_item_size;
        memcpy(ptr, item, m_item_size);
        m_write_idx = next;
    }
    pthread_mutex_unlock(&m_mutex);
    return ret;
}
int ArrayQueue::get(void *item, int num = 1, long long *data_idx=NULL) {
    /*取数据,可以连续取num个数据*/
    /*先判断队列是否为空,不为空则取数据后指针+1*/
    pthread_mutex_lock(&m_mutex);
    int ret = PAS;
    int idx, read_idx;
    void *ptr;
    if (m_read_idx == m_write_idx) {
        ret = QUEUE_EMPTY;
    } else {
        DEBUG_LOG("m_read_idx: %i",m_read_idx);
        read_idx = m_read_idx;
        for (idx = 0; idx < num; idx++) {
            ptr = m_buff + read_idx * m_item_size;
            memcpy(item, ptr, m_item_size);
            read_idx = (m_capacity + read_idx + 1) % m_capacity;
        }
        /*在连续取数据的情况下read指针也只+1*/
        m_read_idx = (m_capacity + m_read_idx + 1) % m_capacity;
        if (data_idx!=NULL){
            *data_idx = m_data_idx;
        }
    }
    pthread_mutex_unlock(&m_mutex);
    return ret;
}