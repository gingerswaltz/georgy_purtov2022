package com.example.lab4;

import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.recyclerview.widget.RecyclerView;

import java.util.List;

public class PersonAdapter extends RecyclerView.Adapter<PersonAdapter.PersonViewHolder> {

    private List<Person> persons;
    private Context context;
    private OnItemClickListener itemClickListener;

    public PersonAdapter(Context context, List<Person> persons) {
        this.context = context;
        this.persons = persons;
    }

    public void setOnItemClickListener(OnItemClickListener listener) {
        itemClickListener = listener;
    }

    @NonNull
    @Override
    public PersonViewHolder onCreateViewHolder(@NonNull ViewGroup parent, int viewType) {
        View view = LayoutInflater.from(parent.getContext()).inflate(R.layout.item_person, parent, false);
        return new PersonViewHolder(view);
    }

    @Override
    public void onBindViewHolder(@NonNull PersonViewHolder holder, int position) {
        Person person = persons.get(position);
        holder.bind(person);
    }

    @Override
    public int getItemCount() {
        return persons.size();
    }

    public interface OnItemClickListener {
        void onItemClick(Person person);
    }

    public class PersonViewHolder extends RecyclerView.ViewHolder {

        public TextView nameTextView;
        public TextView phoneNumberTextView;
        public TextView emailTextView;
        public TextView addressTextView;

        public PersonViewHolder(@NonNull View itemView) {
            super(itemView);
            nameTextView = itemView.findViewById(R.id.nameTextView);
            phoneNumberTextView = itemView.findViewById(R.id.phoneNumberTextView);
            emailTextView = itemView.findViewById(R.id.emailTextView);
            addressTextView = itemView.findViewById(R.id.addressTextView);

            itemView.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View view) {
                    int position = getAdapterPosition();
                    if (position != RecyclerView.NO_POSITION && itemClickListener != null) {
                        Person person = persons.get(position);
                        itemClickListener.onItemClick(person);
                    }
                }
            });
        }

        public void bind(Person person) {
            nameTextView.setText(person.getName());
//            phoneNumberTextView.setText(person.getPhoneNumber());
//            emailTextView.setText(person.getEmail());
//            addressTextView.setText(person.getAddress());
        }
    }
}