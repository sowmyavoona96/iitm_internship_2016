package com.example.sowmya.callme;

import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.TextView;

import java.util.List;

/**
 * Created by sowmya on 28/6/16.
 */
public class  TwoTextListAdapter extends ArrayAdapter<ContactDetails> {

    /** To cache views of item */
    private static class ViewHolder {
        private TextView text1;
        private TextView text2;

        /**
         * General constructor
         */
        ViewHolder() {
            // nothing to do here
        }
    }

    /** Inflater for list items */
    private final LayoutInflater inflater;

    /**
     * General constructor
     *
     * @param context
     *
     * @param textViewResourceId
     * @param objects
     */
    public TwoTextListAdapter(final Context context,
                               final int textViewResourceId,
                               final List<ContactDetails> objects) {
        super(context,textViewResourceId, objects);

        this.inflater = LayoutInflater.from(context);
    }

    @Override
    public View getView(final int position, final View convertView, final ViewGroup parent) {

        View itemView = convertView;
        ViewHolder holder = null;
        final ContactDetails item = getItem(position);

        if(null == itemView) {
            itemView = this.inflater.inflate(R.layout.contact_item, parent, false);

            holder = new ViewHolder();

            holder.text1 = (TextView)itemView.findViewById(R.id.contactName);
            holder.text2 = (TextView)itemView.findViewById(R.id.contactNumber);

            itemView.setTag(holder);
        } else {
            holder = (ViewHolder)itemView.getTag();
        }

        holder.text1.setText(item.getContactName());
        holder.text2.setText(item.getContactNumber());

        return itemView;
    }
}

