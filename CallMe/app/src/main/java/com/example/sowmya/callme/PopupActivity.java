package com.example.sowmya.callme;

import android.app.Activity;
import android.app.AlertDialog;
import android.content.DialogInterface;
import android.content.Intent;
import android.os.Bundle;

import android.os.Environment;
import android.text.Editable;
import android.text.TextWatcher;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

import java.io.File;
import java.util.ArrayList;

/**
 * Created by sowmya on 3/7/16.
 */
public class PopupActivity  extends Activity {

    int noOfTrainFiles = 3;
    Button recordButton;
    Button stopButton;
    Button saveButton;
    Button okButton;

    TextView textView;
    EditText editText;

    String incomingNumber;
    String contactDirectoryPath = "";
    String directoryPath = "";
    String serverDirectoryPath = "http://192.168.1.6/callMe/";
    String contactPath = "";
    String contactName;

    ArrayList<String> trainWavPaths;
    ArrayList<String> trainTextPaths;
    ArrayList<String> train3gppPaths;

    int trainCount = 0;
    boolean isSaved = false;

    //WavAudioRecorder mediaRecorder;
    SoundRecorder soundRecorder;

    ServerHandler serverHandler;
    FileManager fileManager;

    ContactContainer contactContainer;
    ContactDetails contactDetails;

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);

        /* ----------------------- pop  up ---------------------------------*/
        Intent intent = getIntent();
        incomingNumber = intent.getStringExtra("incomingNumber");
        AlertDialog.Builder builder = new AlertDialog.Builder(this);
        builder
                .setTitle("unknown caller")
                .setMessage("want to save number: "+ incomingNumber +"?")
                .setCancelable(false)
                .setPositiveButton("Yes", new DialogInterface.OnClickListener()
                {
                    public void onClick(DialogInterface dialog, int id)
                    {
                        dialog.cancel();
                        Toast.makeText(getApplicationContext(),"Please record the name for 3 times",Toast.LENGTH_SHORT).show();

                    }
                })

                .setNegativeButton("No", new DialogInterface.OnClickListener()
                {
                    public void onClick(DialogInterface dialog, int id)
                    {
                        dialog.cancel();
                        finish();
                    }
                });
        AlertDialog alert = builder.create();
        alert.show();

        setContentView(R.layout.popup);

        // initialize classes
        fileManager = new FileManager();
        serverHandler = new ServerHandler();
        soundRecorder = new SoundRecorder();

        //set paths
        directoryPath = Environment.getExternalStorageDirectory().getAbsolutePath()+"/callMe/";
        contactDirectoryPath = directoryPath + "Contacts/";

        if(!(fileManager.isExists(directoryPath))) {
            if (!(fileManager.create(directoryPath))) {
                Toast.makeText(getApplicationContext(),"couldn't create app directory",Toast.LENGTH_SHORT).show();
                finish();
            }
        }


        if(!fileManager.isExists(contactDirectoryPath)) {
            if(!(fileManager.create(contactDirectoryPath))){
                Toast.makeText(getApplicationContext(),"couldn't create contact directory",Toast.LENGTH_SHORT).show();
                finish();
            }
        }


        textView = (TextView) findViewById(R.id.contactNumber);
        textView.setText(incomingNumber);

        editText = (EditText)findViewById(R.id.contactName);
        okButton = (Button)findViewById(R.id.okButton);

        recordButton = (Button)findViewById(R.id.recordButton);
        stopButton = (Button)findViewById(R.id.stopRecording);
        saveButton = (Button)findViewById(R.id.saveButton);

        recordButton.setEnabled(false);
        stopButton.setEnabled(false);
        saveButton.setEnabled(false);

        train3gppPaths = new ArrayList<>();
        trainWavPaths = new ArrayList<>();
        trainTextPaths = new ArrayList<>();
        /*----------------------------------saving number---------------------*/

        editText.addTextChangedListener(new TextWatcher() {
            @Override
            public void beforeTextChanged(CharSequence s, int start, int count, int after) {

            }

            @Override
            public void onTextChanged(CharSequence s, int start, int before, int count) {

            }

            @Override
            public void afterTextChanged(Editable s) {
                if(editText.getText().toString().length()>0)
                    okButton.setEnabled(true);
            }
        });

        okButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                contactName = editText.getText().toString();
                if(contactName == null || contactName.equals(""))
                    Toast.makeText(getApplicationContext(),"Please enter a name",Toast.LENGTH_SHORT).show();
                else{
                    contactPath = contactDirectoryPath + contactName +"/";

                    if(fileManager.isExists(contactPath)){
                        Toast.makeText(getApplicationContext(),"contact name already exists",Toast.LENGTH_SHORT).show();
                        editText.setText("");

                    }
                    else {
                        if(fileManager.create(contactPath)) {
                            editText.setEnabled(false);
                            okButton.setEnabled(false);
                            recordButton.setEnabled(true);

                            contactDetails = new ContactDetails(contactName,incomingNumber);
                        }
                        else{
                            Toast.makeText(getApplicationContext(),"something went wrong,please enter again",Toast.LENGTH_SHORT).show();
                            editText.setText("");
                        }
                    }
                }

            }

        });
        
        /*------------------------------------recording--------------------------*/
        recordButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String trainWavPath;
                String trainTextPath;
                String train3gppPath;

                trainCount++;

                train3gppPath = contactPath + "train_"+trainCount+".3gpp";
                trainWavPath = contactPath + "train_"+trainCount+".wav";
                trainTextPath = contactPath + "train_"+trainCount+".txt";

                train3gppPaths.add(train3gppPath);
                trainWavPaths.add(trainWavPath);
                trainTextPaths.add(trainTextPath);

                /*mediaRecorder = WavAudioRecorder.getInstanse();
                mediaRecorder.setOutputFile(trainWavPath);
                mediaRecorder.prepare();
                mediaRecorder.start();
                */

                //mediaRecorder.getState() == WavAudioRecorder.State.RECORDING
                if(soundRecorder.recordSound(train3gppPath)){
                    Toast.makeText(getApplicationContext(),"recording",Toast.LENGTH_SHORT).show();
                    stopButton.setEnabled(true);
                }
                else{
                    Toast.makeText(getApplicationContext(),"recording",Toast.LENGTH_SHORT).show();
                }

            }
        });

        stopButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                /*
                mediaRecorder.stop();
                mediaRecorder.reset();
                mediaRecorder.release();
                */

                soundRecorder.stopRecording();
                recordButton.setEnabled(true);
                stopButton.setEnabled(false);

                if(trainCount == noOfTrainFiles){
                    Toast.makeText(getApplicationContext(),"trained the voice,please save the contact",Toast.LENGTH_SHORT).show();
                    saveButton.setEnabled(true);
                    recordButton.setEnabled(false);

                }

            }
        });

        saveButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                int saveCount=0;

                //send .3gpp file to server
                for(int i=0;i<noOfTrainFiles;i++){
                    if(serverHandler.uploadFile(train3gppPaths.get(i))){
                        //run php script to compute features;
                        if(serverHandler.computeFeatures()){
                            //download txt files from server
                            if(serverHandler.downloadFile(serverDirectoryPath+"uploads/test.txt",trainTextPaths.get(i))){
                                //delete recorded wav file
                                fileManager.delete(train3gppPaths.get(i));
                                saveCount++;
                            }else {
                                Toast.makeText(getApplicationContext(),"couldn't upload recorded files",Toast.LENGTH_SHORT).show();
                                finish();
                            }
                        }else {
                            Toast.makeText(getApplicationContext(),"couldn't upload  recorded  files",Toast.LENGTH_SHORT).show();
                            finish();
                        }
                    }
                    else {
                        Toast.makeText(getApplicationContext(),"couldn't upload recorded  files",Toast.LENGTH_SHORT).show();
                        finish();
                    }
                }

                if(saveCount == 3)
                    isSaved = true;

                //save contact in contact list
                contactDetails = new ContactDetails(contactName,incomingNumber);
                contactContainer = new ContactContainer();
                contactContainer.saveContact(getApplicationContext(),contactDetails);
                Toast.makeText(getApplicationContext(),"contact saved",Toast.LENGTH_SHORT).show();

                finish();
            }
        });

    }

    @Override
    protected void onDestroy() {
        if(!isSaved){
            File contactDirectory = new File(contactPath);
            if (contactDirectory.isDirectory())
                for (File child : contactDirectory.listFiles())
                    child.delete();

            contactDirectory.delete();

            //delete from contact list

            if(contactDetails!=null) {
                contactContainer = new ContactContainer();
                contactContainer.deleteContact(getApplicationContext(), contactDetails);
            }
        }

        super.onDestroy();
    }
}
