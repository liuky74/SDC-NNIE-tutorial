//
// Created by liuky on 2020-07-31.
//

#ifndef NNIE_TUTORIAL_ARRAY_QUEUE_HPP
#define NNIE_TUTORIAL_ARRAY_QUEUE_HPP

#include "sdc.hpp"
#include "common.hpp"

class ArrayQueue {
    /*万用数组队列,write_idx应永远大于等于read_idx,
     *实际的数组容量会比数组大小少1,因为write_idx指向的位置恒定为空*/
private:
    int m_read_idx;//读取下标
    int m_write_idx;//写入下标
    long long m_data_idx;//数据总量下标
    int m_item_size;//单个数据的大小
    int m_capacity;//数组容量
    pthread_mutex_t m_mutex;//线程锁
    char *m_buff;//缓存

public:
    ArrayQueue(int capacity, int item_size);

    ~ArrayQueue();
    int put(void *item);

    int get(void *item, int num, long long *data_idx);

};


#endif //NNIE_TUTORIAL_ARRAY_QUEUE_HPP
