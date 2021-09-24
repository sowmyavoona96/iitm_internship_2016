package com.example.sowmya.callme;

import android.os.Environment;

import java.io.File;

/**
 * Created by sowmya on 29/06/16.
 */
public class DTW_main {

    String testFileName = "";
    String recognizedWord = "";
    int noOfTrainFiles = 3;
    int noOfContacts = 0;

    String[] contactList;
    String[] contactNames;
    Double[] minScores;

    DTW_ndk dtw;

    public DTW_main(String testFileName){

        /* -- DTW_ndk is for ./computeFeatures    DtwSphinx for sphinx computed features --*/
        dtw = new DTW_ndk();


        this.testFileName = testFileName;
        contactList = new String[noOfTrainFiles];
    }

    public String funct(){
        Double scoremin,temp;

        String  contactsFolderPath = Environment.getExternalStorageDirectory().getAbsolutePath()+ File.separator +"callMe/Contacts";
        File contactsFolder = new File(contactsFolderPath);
        File[] fileList = contactsFolder.listFiles();

        noOfContacts = fileList.length;

        if(noOfContacts == 0)
            return "";

        contactNames = new String[noOfContacts];
        minScores = new Double[noOfContacts];

        for(int i=0;i<noOfContacts;i++) {
            contactNames[i] = fileList[i].getName();
            File eachContactFolder = new File(contactsFolderPath+"/"+contactNames[i]);
            File[] eachContactList = eachContactFolder.listFiles();
            scoremin = 100000000000000000.0;
            for (int j=0;j<noOfTrainFiles;j++){
                contactList[j]= eachContactList[j].getAbsolutePath();
                temp = dtw.findScore(testFileName,contactList[j]);
                System.out.println(testFileName+"- "+contactList[j]+": "+temp);
                if(temp<scoremin)
                    scoremin = temp;
            }
            minScores[i] = scoremin;

        }

        int index = 0;
        for (int i=0;i<noOfContacts;i++){
            if(minScores[i]<minScores[index])
                index = i;

            System.out.println("contact name: "+contactNames[i]+" minimum Score: "+minScores[i]);
        }


        recognizedWord = contactNames[index];
        System.out.println("recognized word: "+recognizedWord);
        return recognizedWord;
    }
}
