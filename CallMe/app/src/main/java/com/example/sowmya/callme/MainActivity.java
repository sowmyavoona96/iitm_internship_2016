package com.example.sowmya.callme;

import android.app.ProgressDialog;
import android.content.Intent;
import android.media.MediaPlayer;
import android.os.Bundle;
import android.os.Environment;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.widget.Button;
import android.widget.Toast;

import java.io.File;
import java.util.ArrayList;

public class MainActivity extends AppCompatActivity {
    Button recordB,stopB,playB,submitContact;
    String contactStr;
    private ArrayList<String> conNames;
    private ArrayList<String> conNumbers;

    public final static String CONTACT_NAMES = "com.mycompany.myfirstapp.contact_name";
    public final static String CONTACT_NUMBERS = "com.mycompany.myfirstapp.contact_number";
    boolean successMkdirContact = true;
    boolean successMkdirCallMe = true;

    String directoryPath;
    String contactPath;
    String mRcordFilePath;
    String testPathOnPhone;

    SoundRecorder soundRecorder;
    MediaPlayer mediaPlayer;

    String serverDirectoryPath = "http://192.168.1.6/callMe/";


    ProgressDialog progress;

   // boolean fileSent = false;
   // boolean computedFeatures = false;


    FileManager fileManager;
    ServerHandler serverHandler;

    @Override
    protected void onCreate(Bundle savedInstanceState) {

        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        //initialize all classes
        fileManager = new FileManager();
        serverHandler = new ServerHandler();
        soundRecorder = new SoundRecorder();

        //paths
        directoryPath = Environment.getExternalStorageDirectory()+File.separator+"callMe/";
        contactPath = directoryPath + "Contacts/";
        mRcordFilePath = directoryPath +"test.3gpp";
        testPathOnPhone = directoryPath + "test.txt";

        //buttons
        recordB = (Button) findViewById(R.id.recordButton);
        stopB = (Button) findViewById(R.id.stopButton);
        playB = (Button) findViewById(R.id.playButton);
        submitContact = (Button) findViewById(R.id.submitContact);

        //enable only after recording
        stopB.setEnabled(false);
        playB.setEnabled(false);
        submitContact.setEnabled(false);

        // create directory for app if not exists
        if(!(fileManager.isExists(directoryPath)))
            successMkdirCallMe  = fileManager.create(directoryPath);

        //create directory for contacts
        if(!(fileManager.isExists(contactPath)))
            successMkdirContact = fileManager.create(contactPath);


        if(!(successMkdirContact && successMkdirCallMe)) {
            Toast.makeText(getApplicationContext(),"couldn't create directories",Toast.LENGTH_SHORT).show();
            finish();
        }

        /*--------------------------------- recording and storing wav file--------------------------------------- */

            recordB.setOnClickListener(new View.OnClickListener(){
                public void onClick(View v){

                    if(soundRecorder.recordSound(mRcordFilePath)) {
                        Toast.makeText(getApplicationContext(),"recording ",Toast.LENGTH_SHORT).show();
                        recordB.setEnabled(false);
                        stopB.setEnabled(true);
                    }
                    else {
                        Toast.makeText(getApplicationContext(), "something went wrong", Toast.LENGTH_SHORT).show();
                    }
                }
            });

            stopB.setOnClickListener(new View.OnClickListener(){
                public void onClick(View v){

                    soundRecorder.stopRecording();
                    Toast.makeText(getApplicationContext(), "recording stopped", Toast.LENGTH_SHORT).show();
                    stopB.setEnabled(false);
                    playB.setEnabled(true);
                    submitContact.setEnabled(true);

                }
            });

            playB.setOnClickListener(new View.OnClickListener(){
                public void onClick(View v){
                   try {
                       mediaPlayer = new MediaPlayer();
                       mediaPlayer.setDataSource(mRcordFilePath);
                       mediaPlayer.prepare();
                       mediaPlayer.start();

                       Toast.makeText(getApplicationContext(), "Playing audio", Toast.LENGTH_SHORT).show();

                   }
                    catch(Exception e) {
                        e.printStackTrace();
                        Toast.makeText(getApplicationContext(), "couldn't play the audio", Toast.LENGTH_SHORT).show();
                    }

                }
            });


        /* -------------------------------- take string input to search in contacts --------------------------------*/

            submitContact.setOnClickListener(new View.OnClickListener(){
                @Override
                public void onClick(View view) {
                    submitContact.setEnabled(false);
                    recordB.setEnabled(true);
                    playB.setEnabled(false);


                   // connect to php server to send recorded file and computeFeatures

                    progress = ProgressDialog.show(MainActivity.this, "Connect to server", "uploading file", true);


                    if(serverHandler.uploadFile(mRcordFilePath)) {
                        progress.dismiss();
                        //computeFeatures
                        if(serverHandler.computeFeatures()){

                            //delete wav file recording on phonee
                            fileManager.delete(mRcordFilePath);

                            //download text file
                            if(serverHandler.downloadFile(serverDirectoryPath+"uploads/test.txt",testPathOnPhone)){
                                //find dtw
                                String testPath = directoryPath + "test.txt";
                                DTW_main dtw_main = new DTW_main(testPath);

                                //store it in contactStr
                                contactStr = dtw_main.funct();

                                //delete mfcc of recorded file
                                if(fileManager.delete(directoryPath+"test.txt"))
                                    Toast.makeText(getApplicationContext(),"deleted test.txt file successfully",Toast.LENGTH_SHORT).show();

                                conNames = new ArrayList<>();
                                conNumbers = new ArrayList<>();
                                ContactContainer cc = new ContactContainer();

                                ArrayList<ContactDetails> contacts =  cc.getContact(getContentResolver(),contactStr);
                                Intent intent = new Intent(MainActivity.this,DisplayContactActivity.class);

                                if(!(contacts.size()>0) || contactStr.equals("")) {
                                    Toast.makeText(getApplicationContext(),"no such contact",Toast.LENGTH_SHORT).show();

                                }

                                else {
                                    for(int i=0;i<contacts.size();i++){
                                        conNames.add(contacts.get(i).getContactName());
                                        conNumbers.add(contacts.get(i).getContactNumber());

                                    }
                                    intent.putExtra(CONTACT_NAMES, conNames);
                                    intent.putExtra(CONTACT_NUMBERS,conNumbers);

                                    startActivity(intent);
                                }

                            }

                        }
                    }
                    else{
                        progress.dismiss();
                        Toast.makeText(getApplicationContext(),"couldn't upload wav file",Toast.LENGTH_SHORT).show();

                    }

                }

            });
    }

    @Override
    protected void onDestroy() {
        if(fileManager.isExists(mRcordFilePath))
            fileManager.delete(mRcordFilePath);

        if(fileManager.isExists(testPathOnPhone))
            fileManager.delete(testPathOnPhone);

        super.onDestroy();
    }
}
