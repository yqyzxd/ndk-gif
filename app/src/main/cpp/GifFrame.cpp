//
// Created by 史浩 on 2019-11-22.
//

#include "GifFrame.h"
#include "log.h"
static int readFunc(GifFileType *fileType, GifByteType *byteType, int size){
    AAsset* aAsset= (AAsset*)(fileType->UserData);
    return AAsset_read(aAsset,byteType,(size_t)size);

}
static int readByJInputSream(GifFileType *fileType, GifByteType *byteType, int size){
    JavaInputSream* stream=(JavaInputSream*)fileType->UserData;
    return (int)stream->read(byteType,size);

}
GifFrame::GifFrame(JavaInputSream* inputSream) {
    mGif=DGifOpen(inputSream,readByJInputSream,NULL);
    if(mGif){
        DGifSlurp(mGif);
    }

}
GifFrame::GifFrame(AAssetManager* mgr,const char* filename) {
    int err;
    if(mgr){

        AAsset* aAsset=AAssetManager_open(mgr,filename,AASSET_MODE_STREAMING);
        mGif=DGifOpen(aAsset,readFunc,&err);
    } else{
        mGif=DGifOpenFileName(filename,&err);
    }
    LOGE(" mGif %p",mGif);
    //获取gif总的播放时长
    if(mGif){
        DGifSlurp(mGif);
    /*    width=mGif->SWidth;
        height=mGif->SHeight;
        frameCount=mGif->ImageCount;*/
       /* int totalTimeMs=0;
        for (int i = 0; i < frameCount; ++i) {
            GraphicsControlBlock *gcb;
            DGifSavedExtensionToGCB(mGif,i,gcb);
            totalTimeMs+=(gcb->DelayTime*10);
        }*/

    }
}

GifFrame::~GifFrame() {

}


GifFileType* GifFrame::getGif() {
    return mGif;
}

int GifFrame::getWidth() {
    LOGE(" mGif->SWidth %d",mGif->SWidth);
    return mGif? mGif->SWidth:0;
}
int GifFrame::getHeight() {
    LOGE(" mGif->SHeight %d",mGif->SHeight);
    return mGif? mGif->SHeight:0;
}
int GifFrame::getFrameCount() {
    LOGE(" mGif->ImageCount %d",mGif->ImageCount);
    return mGif? mGif->ImageCount:0;
}