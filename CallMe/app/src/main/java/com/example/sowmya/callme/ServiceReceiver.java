package com.example.sowmya.callme;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.telephony.PhoneStateListener;
import android.telephony.TelephonyManager;

public class ServiceReceiver extends BroadcastReceiver {
    private String incomingNumber;
    @Override
    public void onReceive(final Context context, Intent intent) {


        //PhoneStateChangeListener pscl = new PhoneStateChangeListener();
        final TelephonyManager telephony = (TelephonyManager)context.getSystemService(Context.TELEPHONY_SERVICE);
       // telephony.listen(pscl,PhoneStateListener.LISTEN_CALL_STATE);


        telephony.listen(new PhoneStateListener(){

            @Override
            public void onCallStateChanged(int state, String number) {
                if(TelephonyManager.CALL_STATE_RINGING == state){
                    incomingNumber = number;
                    System.out.println("incomingNumber : "+incomingNumber+" "+context);

                    ContactContainer contactContainer = new ContactContainer();
                    if(!contactContainer.isExist(context,incomingNumber)) {
                        System.out.println("not exists");
                        showSimplePopUp(context);
                    }

                }

                super.onCallStateChanged(state, incomingNumber);

            }
        },PhoneStateListener.LISTEN_CALL_STATE);

    }

    private void showSimplePopUp(Context context) {

        Intent intent = new Intent(context, PopupActivity.class);

        intent.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
        intent.addFlags(Intent.FLAG_ACTIVITY_SINGLE_TOP);
        intent.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK | Intent.FLAG_ACTIVITY_CLEAR_TASK  | Intent.FLAG_ACTIVITY_EXCLUDE_FROM_RECENTS | Intent.FLAG_ACTIVITY_NO_ANIMATION);

        intent.putExtra("incomingNumber",incomingNumber);
        context.startActivity(intent);

    }

}

