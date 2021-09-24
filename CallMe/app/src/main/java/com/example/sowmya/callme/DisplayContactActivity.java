package com.example.sowmya.callme;

import android.app.AlertDialog;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.graphics.Color;
import android.graphics.PixelFormat;
import android.net.Uri;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.Gravity;
import android.view.View;
import android.view.WindowManager;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.BaseAdapter;
import android.widget.LinearLayout;
import android.widget.ListView;
import android.widget.RelativeLayout;
import android.widget.TextView;
import android.widget.Toast;

import java.util.ArrayList;

public class DisplayContactActivity extends AppCompatActivity {
    ArrayList<String> contactNames;
    ArrayList<String> contactNos;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        setContentView(R.layout.activity_display_contact);


        Intent intent = getIntent();

        contactNames = intent.getStringArrayListExtra(MainActivity.CONTACT_NAMES);
        contactNos = intent.getStringArrayListExtra(MainActivity.CONTACT_NUMBERS);

        final String[] trimmedNumbers = new String[contactNames.size()];
        for(int i=0;i<contactNames.size();i++){
            trimmedNumbers[i] = contactNos.get(i).trim();

        }

        ArrayList<ContactDetails> cdList = new ArrayList<>();
        ContactDetails cd;
        for (int i=0;i<contactNames.size();i++){
            cd = new ContactDetails(contactNames.get(i),contactNos.get(i));
            cdList.add(cd);
        }

        TwoTextListAdapter adapter = new TwoTextListAdapter(this,R.layout.contact_item,cdList);
        ListView listView = (ListView) findViewById(R.id.contactList);
        listView.setAdapter(adapter);

        listView.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> adapterView, View view, int position, long l) {

                Toast.makeText(getApplicationContext(),trimmedNumbers[position],Toast.LENGTH_SHORT).show();
                Intent callIntent = new Intent(Intent.ACTION_CALL);
                callIntent.setData(Uri.parse("tel:"+trimmedNumbers[position]));
                startActivity(callIntent);

            }
        });

    }


}
