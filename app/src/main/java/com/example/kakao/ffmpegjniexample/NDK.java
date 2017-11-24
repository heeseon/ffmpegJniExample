package com.example.kakao.ffmpegjniexample;

/**
 * Created by kakao on 2017. 11. 20..
 */

public class NDK {

    static {

        System.loadLibrary("ffmpeg");

    }



    public native int run_ffmpeg(String com[]);


}
