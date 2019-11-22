package com.wind.ndk.gif;

import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.ColorFilter;
import android.graphics.Paint;
import android.graphics.PixelFormat;
import android.graphics.Rect;
import android.graphics.drawable.Animatable;
import android.graphics.drawable.Drawable;
import android.os.SystemClock;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;

/**
 * Created By wind
 * on 2019-11-22
 */
public class GifDrawable extends Drawable implements Animatable,Runnable {

    private Paint mPaint;
    private GifFrame mGifFrame;
    private Bitmap mBitmap;

    private int mGifWidth;
    private int mGifHeight;
    private int mGifFrameCount;

    private boolean mRunning;
    private long mNextFrameDelay;

    Rect srcRect;
    private int frameIndex;
    public GifDrawable(GifFrame gifFrame){
        mGifFrame=gifFrame;
        mGifWidth=gifFrame.getFrameWidth();
        mGifHeight=gifFrame.getFrameHeight();
        mGifFrameCount=gifFrame.getFrameCount();

        mPaint=new Paint(Paint.ANTI_ALIAS_FLAG);
        mBitmap= Bitmap.createBitmap(mGifWidth,mGifHeight, Bitmap.Config.ARGB_8888);



        srcRect=new Rect(0,0,mGifWidth,mGifHeight);

        mNextFrameDelay=gifFrame.getFrame(mBitmap,0);
        System.out.println("mNextFrameDelay:"+mNextFrameDelay);
    }

    public int getFrameIndex(){
        frameIndex++;
        return frameIndex<mGifFrameCount?frameIndex:(frameIndex=0);
    }
    private long time;
    @Override
    public void draw(@NonNull Canvas canvas) {

        canvas.drawBitmap(mBitmap,0,0,mPaint);
        time= SystemClock.uptimeMillis();
        if (isRunning()){
            scheduleSelf(this,time+mNextFrameDelay);
        }
    }

    @Override
    public void setAlpha(int alpha) {
        mPaint.setAlpha(alpha);
    }

    @Override
    public void setColorFilter(@Nullable ColorFilter colorFilter) {
        mPaint.setColorFilter(colorFilter);
    }

    @Override
    public int getOpacity() {
        return PixelFormat.TRANSLUCENT;
    }


    @Override
    public void start() {
        if (!isRunning()){
            mRunning=true;
            scheduleSelf(this,SystemClock.uptimeMillis());
        }
    }

    @Override
    public void stop() {
        if (isRunning()){
            mRunning=false;
            unscheduleSelf(this);
        }
    }

    @Override
    public boolean isRunning() {
        return mRunning;
    }

    @Override
    public void run() {
        long start=System.currentTimeMillis();
        mNextFrameDelay=mGifFrame.getFrame(mBitmap,getFrameIndex());
        long end=System.currentTimeMillis();
        System.out.println("end-start:"+(end-start));
       // System.out.println("mNextFrameDelay:"+mNextFrameDelay);
        invalidateSelf();
    }
}
