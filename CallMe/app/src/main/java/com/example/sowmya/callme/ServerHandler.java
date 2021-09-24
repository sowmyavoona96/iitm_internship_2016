package com.example.sowmya.callme;

import android.util.Log;

import java.io.BufferedInputStream;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.URL;
import java.net.URLConnection;

/**
 * Created by sowmya on 8/7/16.
 */

public class ServerHandler {

    String serverUrl = "http://192.168.1.6/callMe/";
    String computeFeaturesUrl = serverUrl + "scripts/computeFeatures.php";
    String uploadUrl = serverUrl + "scripts/UploadToServer.php";

    class UploadWavFile implements Runnable{

        URL connectURL;
        String sourceFilePath;
        FileInputStream fileInputStream = null;
        boolean isUploaded = false;

        UploadWavFile(String sourcepath){
            sourceFilePath = sourcepath;
        }

        @Override
        public void run() {
            try {
                connectURL = new URL(uploadUrl);
                fileInputStream = new FileInputStream(sourceFilePath);

                Log.i("connectURL: ",connectURL.toString());

            } catch (Exception ex) {
                ex.printStackTrace();
                Log.i("HttpFileUpload", "URL Malformatted");
                isUploaded = false;
            }

            String lineEnd = "\r\n";
            String twoHyphens = "--";
            String boundary = "*****";
            String Tag = "fSnd";
            int maxBufferSize = 1024 * 1024;

            try {
                Log.e(Tag, "Starting Http File Sending to URL");

                HttpURLConnection conn = (HttpURLConnection) connectURL.openConnection();// Open a HTTP connection to the URL

                conn.setDoInput(true);// Allow Inputs
                conn.setDoOutput(true);// Allow Outputs
                conn.setUseCaches(false);// Don't use a cached copy.

                conn.setRequestMethod("POST");// Use a post method.
                conn.setRequestProperty("Connection", "Keep-Alive");
                conn.setRequestProperty("ENCTYPE", "multipart/form-data");
                conn.setRequestProperty("Content-Type", "multipart/form-data;boundary=" + boundary);
                conn.setRequestProperty("uploaded_file",sourceFilePath);

                Log.i("sourcePath: ",sourceFilePath);
                Log.i("setProperty: ","done");

                DataOutputStream dos = new DataOutputStream(conn.getOutputStream());

                System.out.println("created dos");

                dos.writeBytes(twoHyphens + boundary + lineEnd);
                dos.writeBytes("Content-Disposition: form-data; name=\"uploaded_file\"; filename=\"" + sourceFilePath + "\"" + lineEnd);
                dos.writeBytes(lineEnd);

                Log.e(Tag, "Headers are written");

                int bytesAvailable = fileInputStream.available();

                int bufferSize = Math.min(bytesAvailable, maxBufferSize);
                byte[] buffer = new byte[bufferSize];

                // read file and write it into form...
                int bytesRead = fileInputStream.read(buffer, 0, bufferSize);

                while (bytesRead > 0) {
                    dos.write(buffer, 0, bufferSize);
                    bytesAvailable = fileInputStream.available();
                    bufferSize = Math.min(bytesAvailable, maxBufferSize);
                    bytesRead = fileInputStream.read(buffer, 0, bufferSize);
                }
                dos.writeBytes(lineEnd);
                dos.writeBytes(twoHyphens + boundary + twoHyphens + lineEnd);

                // close streams
                fileInputStream.close();

                dos.flush();

                Log.e(Tag, "File Sent, Response: " + String.valueOf(conn.getResponseCode()));

                InputStream is = new DataInputStream(conn.getInputStream());

                // retrieve the response from server
                int ch;

                StringBuilder b = new StringBuilder();
                while ((ch = is.read()) != -1) {
                    b.append((char) ch);
                }
                String s = b.toString();
                Log.i("Response", s);
                dos.close();

                isUploaded = true;

            } catch (MalformedURLException ex) {
                Log.e(Tag, "URL error: " + ex.getMessage(), ex);
                isUploaded = false;
                return;

            } catch (IOException ioe) {
                Log.e(Tag, "IO error: " + ioe.getMessage(), ioe);
                isUploaded = false;
                return;

            }catch (Exception e){
                e.printStackTrace();
                return;
            }
        }

        public  boolean getIsUploaded(){
            return isUploaded;
        }
    }

    class ComputeFeatures implements  Runnable{
        boolean isComputed = false;

        @Override
        public void run() {
            try {
                URL url = new URL(computeFeaturesUrl);

                HttpURLConnection conn = (HttpURLConnection) url.openConnection();
                conn.setReadTimeout(5000);
                conn.setConnectTimeout(10000);

                if( conn.getResponseCode() == HttpURLConnection.HTTP_OK ){
                    InputStream is = conn.getInputStream();
                    int ch;

                    StringBuilder b = new StringBuilder();
                    while ((ch = is.read()) != -1) {
                        b.append((char) ch);
                    }
                    String s = b.toString();
                    System.out.println("success: "+s);
                    // do something with the data here
                    isComputed = true;

                }else{
                    InputStream err = conn.getErrorStream();
                    int ch;

                    StringBuilder b = new StringBuilder();
                    while ((ch = err.read()) != -1) {
                        b.append((char) ch);
                    }
                    String s = b.toString();
                    System.out.println("fail: "+s);
                    isComputed = false;
                }

            }catch (MalformedURLException mue){
                mue.printStackTrace();
                isComputed = false;
                return;

            }catch (IOException ioe){
                ioe.printStackTrace();
                isComputed = false;
                return;
            }

        }

        public  boolean getIsComputed(){
            return  isComputed;
        }
    }

    class DownloadFile implements Runnable{
        String sourcePath;
        String destinationPath;
        boolean isDownloaded = false;

        public DownloadFile(String sourcepath,String destpath){
            sourcePath = sourcepath;
            destinationPath = destpath;
        }

        @Override
        public void run() {

            try
            {
                URL url = new URL(sourcePath);

                URLConnection ucon = url.openConnection();
                ucon.setReadTimeout(5000);
                ucon.setConnectTimeout(10000);

                System.out.println("url set time out finished");

                InputStream is = ucon.getInputStream();
                BufferedInputStream inStream = new BufferedInputStream(is, 1024 * 5);

                System.out.println("after buffered input stream");

                File file = new File(destinationPath);

                if (file.exists())
                    file.delete();

                file.createNewFile();

                FileOutputStream outStream = new FileOutputStream(file);
                byte[] buff = new byte[5 * 1024];

                int len;
                while ((len = inStream.read(buff)) != -1)
                {
                    outStream.write(buff, 0, len);
                }

                outStream.flush();
                outStream.close();
                inStream.close();
                System.out.println("finished downloading");

                isDownloaded = true;

            }
            catch (Exception e)
            {
                e.printStackTrace();
                isDownloaded = false;
                return;

            }


        }

        public boolean getIsDownloaded(){
            return isDownloaded;
        }
    }

    public boolean uploadFile(String sourcePath){

        UploadWavFile uploadWavFile = new UploadWavFile(sourcePath);
        Thread uploadThread = new Thread(uploadWavFile);
        uploadThread.start();

        try{
            uploadThread.join();
            return uploadWavFile.getIsUploaded();

        }catch (InterruptedException ie){
            ie.printStackTrace();
            return false;
        }
    }

    public boolean computeFeatures(){
        ComputeFeatures computefeat = new ComputeFeatures();
        Thread computeThread = new Thread(computefeat);
        computeThread.start();

        try{
            computeThread.join();
            return  computefeat.getIsComputed();

        }catch (InterruptedException ie){
            ie.printStackTrace();
            return false;
        }
    }

    public boolean downloadFile(String sourcepath, String destpath){
        DownloadFile downfile = new DownloadFile(sourcepath,destpath);
        Thread downloadThread = new Thread(downfile);
        downloadThread.start();

        try {
            downloadThread.join();
            return  downfile.getIsDownloaded();

        }catch (InterruptedException ie){
            ie.printStackTrace();
            return false;
        }

    }
}
