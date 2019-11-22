//
// Created by 史浩 on 2019-11-22.
//

#include "JavaInputSream.h"
#define min(a,b) a<b?a:b


JavaInputSream::JavaInputSream(JNIEnv *env, jobject jinputStream, jbyteArray byteArray) :
        mEnv(env),
        mInputSream(jinputStream),
        mByteArray(byteArray),
        mByteArrayLength(env->GetArrayLength(byteArray)) {

}

size_t JavaInputSream::read(void *buffer, size_t size) {
    size_t totalBytesRead=0;

    do{
        size_t minSize=min(size,mByteArrayLength);
        jint bytesRead=mEnv->CallIntMethod(mInputSream,readMethodId,mByteArray,0,minSize);
        if (mEnv->ExceptionCheck() || bytesRead<0){
            mEnv->ExceptionClear();
            return 0;
        }
        mEnv->GetByteArrayRegion(mByteArray,0,bytesRead,static_cast<jbyte *>(buffer));
        buffer=(char*)buffer+bytesRead;
        size-=bytesRead;
        totalBytesRead+=bytesRead;
    }while (size>0);

    return totalBytesRead;
}