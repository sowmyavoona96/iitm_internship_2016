package com.example.sowmya.callme;

/**
 * Created by sowmya on 1/7/16.
 */
public class DTW_ndk {
    static {
        System.loadLibrary("DtwLibrary");
    }

    public native double findScore(String test,String train);
}
