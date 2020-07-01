//
// Created by Administrator on 2020/6/28.
//

#ifndef DEBUG_DEAD_LOCK_NFPLATFORM_H
#define DEBUG_DEAD_LOCK_NFPLATFORM_H
#include <iostream>
#include <functional>
#include <map>
#include <memory>
#include <chrono>
#include <thread>
#include <vector>
// Integer formats of fixed bit width
typedef uint32_t NFUINT32;
typedef uint16_t NFUINT16;
typedef uint8_t NFUINT8;
typedef int32_t NFINT32;
typedef int16_t NFINT16;
typedef int8_t NFINT8;
typedef uint64_t NFUINT64;
typedef int64_t NFINT64;
typedef int64_t NFSOCK;


#define NF_SHARED_PTR std::shared_ptr
#define NF_NEW new
#define GET_CLASS_NAME(class) #class
#endif //DEBUG_DEAD_LOCK_NFPLATFORM_H
