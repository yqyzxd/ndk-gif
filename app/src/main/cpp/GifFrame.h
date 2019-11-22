//
// Created by 史浩 on 2019-11-22.
//

#ifndef NDK_GIF_GIFFRAME_H
#define NDK_GIF_GIFFRAME_H

#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#include "giflib/gif_lib.h"
#include "JavaInputSream.h"

class GifFrame {


public:
    GifFrame(JavaInputSream* inputSream);
    GifFrame(AAssetManager* asset, const char* filename);
    ~GifFrame();

    int getWidth();
    int getHeight();
    int getFrameCount();
    GifFileType* getGif();
private:
    int width;
    int height;
    int frameCount;
    GifFileType* mGif;

};


#endif //NDK_GIF_GIFFRAME_H
