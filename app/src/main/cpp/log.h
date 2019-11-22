//
// Created by 史浩 on 2019-11-22.
//

#ifndef NDK_GIF_LOG_H
#define NDK_GIF_LOG_H

#include <android/log.h>

#define  LOG_TAG    "NDKGIF"
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

#endif //NDK_GIF_LOG_H
