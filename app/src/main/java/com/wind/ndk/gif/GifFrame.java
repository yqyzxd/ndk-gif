package com.wind.ndk.gif;

import android.content.res.AssetManager;
import android.graphics.Bitmap;

import java.io.InputStream;

/**
 * Created By wind
 * on 2019-11-22
 */
public class GifFrame {

    static {
        System.loadLibrary("gif-lib");
    }


    private int mFrameWidth;
    private int mFrameHeight;
    private int mFrameCount;
    private long mNativeHandle;
    private GifFrame(long nativeHandle,int frameWidth,int frameHeight,int frameCount){
        this.mNativeHandle=nativeHandle;
        this.mFrameWidth=frameWidth;
        this.mFrameHeight=frameHeight;
        this.mFrameCount=frameCount;
    }

    public static GifFrame init(AssetManager assetManager,String filepath){
        return native_init(assetManager,filepath);
    }



    public static GifFrame init(InputStream ips){
        return native_init(ips);
    }


    /**
     * 返回当前帧播放时间也是下一帧延迟时间
     *
     * @return
     */
    public long getFrame(Bitmap bitmap,int frameIndex){
        return nativeGetFrame(mNativeHandle,bitmap,frameIndex);
    }



    public int getFrameCount() {
        return mFrameCount;
    }

    public int getFrameHeight() {
        return mFrameHeight;
    }

    public int getFrameWidth() {
        return mFrameWidth;
    }



    private static native GifFrame native_init(AssetManager assetManager,String filepath);
    private static native GifFrame native_init(InputStream ips);
    private native long nativeGetFrame(long nativeHandle,Bitmap bitmap,int frameIndex);
}
