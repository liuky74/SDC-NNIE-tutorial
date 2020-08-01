//
// Created by liuky on 2020-07-30.
//

#ifndef NNIE_TUTORIAL_COMMON_HPP
#define NNIE_TUTORIAL_COMMON_HPP

#ifdef NDEBUG
#define DEBUG_LOG(msg, ...) void(0)
#else
#define DEBUG_LOG(msg, ...) printf("%s:%d\t" msg "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#endif

#define QUEUE_EMPTY -2
#define QUEUE_FULL -3
#define PAS 0
#define ERR -1

#include <stdio.h>
#include <fcntl.h>
#include <cstdlib>


#endif //NNIE_TUTORIAL_COMMON_HPP
