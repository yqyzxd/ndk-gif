//
// Created by 史浩 on 2019-11-22.
//
#include "com_wind_ndk_gif_GifFrame.h"
#include "../cpp/GifFrame.h"
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#include <android/bitmap.h>
#include "../cpp/log.h"
#define ARGB(a,r,g,b) ((a)<<24 | (b)<<16 | (g)<<8 | (r))

extern "C" JNIEXPORT jobject JNICALL Java_com_wind_ndk_gif_GifFrame_native_1init
        (JNIEnv *env, jclass jclazz, jobject jassetManager, jstring jfilename){

    AAssetManager* mgr=AAssetManager_fromJava(env,jassetManager);
    const  char* filename=env->GetStringUTFChars(jfilename,0);
    GifFrame* gifFrame=new GifFrame(mgr,filename);

    jclass gifFrameClazz=env->FindClass("com/wind/ndk/gif/GifFrame");
    //创建java对象
    jmethodID jconstructMethod=env->GetMethodID(gifFrameClazz,"<init>","(JIII)V");
    //注意这里是jlong而不是long，强转成long，后续将无法恢复GifFrame。切记
    jlong gifhandle= reinterpret_cast<jlong>(gifFrame);

    env->ReleaseStringUTFChars(jfilename,filename);

    jobject jgifFrame=env->NewObject(jclazz,jconstructMethod,gifhandle,gifFrame->getWidth(),gifFrame->getHeight(),
                   gifFrame->getFrameCount());
    return jgifFrame;

}
extern "C" JNIEXPORT jobject JNICALL Java_com_wind_ndk_gif_GifFrame_native_1init__Ljava_lang_Object_2
        (JNIEnv *, jclass, jobject jinputStream){

}

extern "C" JNIEXPORT jlong JNICALL Java_com_wind_ndk_gif_GifFrame_nativeGetFrame
        (JNIEnv *env, jobject, jlong nativeHandle,jobject jbitmap,jint frameindex){

    GifFrame* gifFrame= reinterpret_cast<GifFrame *>(nativeHandle);

    //使用jnigraphic操作bitmap
    uint32_t * pixels;
    AndroidBitmapInfo info;
    AndroidBitmap_getInfo(env,jbitmap,&info);
    AndroidBitmap_lockPixels(env, jbitmap, reinterpret_cast<void **>(&pixels));
    GifFileType* fileType=gifFrame->getGif();
    SavedImage savedImage=fileType->SavedImages[frameindex];
    GifImageDesc imageDesc=savedImage.ImageDesc;
    ColorMapObject * colorMapObject=fileType->SColorMap?fileType->SColorMap:imageDesc.ColorMap;
    LOGE("nativeGetFrame imageDesc.Height %d",imageDesc.Height);
    LOGE("nativeGetFrame imageDesc.Width %d",imageDesc.Width);
    for (int i = 0; i <imageDesc.Height ; ++i) {

        for (int j = 0; j < imageDesc.Width; ++j) {
            int index=i*imageDesc.Width+j;
            GifByteType  gifByteType=savedImage.RasterBits[index];

            GifColorType colorType=colorMapObject->Colors[gifByteType];

            pixels[index]=ARGB(0xff, colorType.Red,colorType.Green,colorType.Blue);
        }
    }


    AndroidBitmap_unlockPixels(env,jbitmap);

    GraphicsControlBlock gcb;
    DGifSavedExtensionToGCB(fileType,frameindex,&gcb);

    return gcb.DelayTime*10;//转成毫秒
}