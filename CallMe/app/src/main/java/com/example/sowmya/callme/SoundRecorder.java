package com.example.sowmya.callme;

import android.media.MediaPlayer;
import android.media.MediaRecorder;

/**
 * Created by sowmya on 4/7/16.
 */
public class SoundRecorder {
    private MediaRecorder mediaRecorder;
    private MediaPlayer mediaPlayer;
    public SoundRecorder(){

    }

    public boolean recordSound(String outputFile){
        try{
            mediaRecorder = new MediaRecorder();
            mediaRecorder.setAudioSource(MediaRecorder.AudioSource.MIC);
            mediaRecorder.setOutputFormat(MediaRecorder.OutputFormat.THREE_GPP);
            mediaRecorder.setAudioEncoder(MediaRecorder.AudioEncoder.AMR_NB);
            mediaRecorder.setOutputFile(outputFile);

            mediaRecorder.prepare();
            mediaRecorder.start();

            return true;

        }catch (Exception e){
            e.printStackTrace();
            return false;
        }
    }

    public void stopRecording(){
        mediaRecorder.stop();
        mediaRecorder.reset();
        mediaRecorder.release();
        mediaRecorder = null;
    }

    public boolean playRecording(String outputFile){
        try{
            mediaPlayer = new MediaPlayer();
            mediaPlayer.setDataSource(outputFile);
            mediaPlayer.prepare();
            mediaPlayer.start();
            return  true;

        }catch (Exception e){
            e.printStackTrace();
            return  false;
        }
    }

    public void stopPlaying(){
        mediaPlayer.stop();
    }
}
