package com.wind.ndk.gif;

import android.os.Bundle;
import android.widget.ImageView;

import androidx.appcompat.app.AppCompatActivity;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;

public class MainActivity extends AppCompatActivity {


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);


        ImageView iv=findViewById(R.id.iv);

        GifDrawable gifDrawable;
        iv.setImageDrawable(gifDrawable=new GifDrawable(GifFrame.init(getAssets(),"demo.gif")));

        gifDrawable.start();
    }


    private void inputStreamTest(){

        try {
            InputStream ips=new FileInputStream("");
            byte[] buffer=new byte[1024];
            int length=-1;
            while ((length=ips.read(buffer))!=-1){

            }
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }

    }

}
