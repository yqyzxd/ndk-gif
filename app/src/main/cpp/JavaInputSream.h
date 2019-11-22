//
// Created by 史浩 on 2019-11-22.
//

#ifndef NDK_GIF_JAVAINPUTSREAM_H
#define NDK_GIF_JAVAINPUTSREAM_H

#include <jni.h>

class JavaInputSream {


public:
    JavaInputSream(JNIEnv* env,jobject jinputStream,jbyteArray byteArray);
    size_t read(void * buffer,size_t size);

private:
    JNIEnv* mEnv;
    const jobject mInputSream;
    const jbyteArray  mByteArray;
    const  size_t mByteArrayLength;


public:
    static jmethodID readMethodId;
};


#endif //NDK_GIF_JAVAINPUTSREAM_H
