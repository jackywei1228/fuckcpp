//
// Created by 25810 on 2018/12/22.
//

#ifndef FUCKCPP_JKTYPES_H
#define FUCKCPP_JKTYPES_H

#include <android/log.h>

#define JK_OK 0
#define JK_ERROR -1
#define JK_ERROR_NO_SPACE 1


#define JK_TRUE 1
#define JK_FALSE 0

#define TAG    "JKRO"
#define LOGD(...)  __android_log_print(ANDROID_LOG_ERROR,TAG,__VA_ARGS__)

//typedef unsigned char* JKByte;

typedef unsigned char jk_uint8;
typedef char jk_int8;

typedef unsigned short jk_uint16;
typedef short jk_int16;
typedef unsigned int jk_uint32;
typedef int jk_int32;

#ifndef NULL
#define NULL 0
#endif //NULL

#endif //FUCKCPP_JKTYPES_H
