package com.example.lab8java;

import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;
import android.widget.Toast;

import androidx.annotation.NonNull;
import androidx.recyclerview.widget.RecyclerView;
import androidx.wear.widget.WearableLinearLayoutManager;
import androidx.wear.widget.WearableRecyclerView;

public class MyAdapter extends RecyclerView.Adapter<MyAdapter.MyViewHolder> {
    private String[] data;
    private OnItemClickListener onItemClickListener;
    private OnLongItemClickListener onLongItemClickListener;

    public MyAdapter(String[] data) {
        this.data = data;
    }

    public void setOnItemClickListener(OnItemClickListener listener) {
        this.onItemClickListener = listener;
    }

    public void setOnLongItemClickListener(OnLongItemClickListener listener) {
        this.onLongItemClickListener = listener;
    }

    @NonNull
    @Override
    public MyViewHolder onCreateViewHolder(@NonNull ViewGroup parent, int viewType) {
        View view = LayoutInflater.from(parent.getContext()).inflate(R.layout.custom_item_layout, parent, false);
        return new MyViewHolder(view);
    }

    @Override
    public void onBindViewHolder(@NonNull MyViewHolder holder, int position) {
        String item = data[position];
        holder.textView.setText(item);

        holder.itemView.setOnLongClickListener(new View.OnLongClickListener() {
            @Override
            public boolean onLongClick(View v) {
                int clickedPosition = holder.getAdapterPosition();
                if (onLongItemClickListener != null && clickedPosition != RecyclerView.NO_POSITION) {
                    onLongItemClickListener.onLongItemClick(clickedPosition);
                    return true;
                }
                return false;
            }
        });

        holder.itemView.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                int clickedPosition = holder.getAdapterPosition();
                if (onItemClickListener != null && clickedPosition != RecyclerView.NO_POSITION) {
                    onItemClickListener.onItemClick(clickedPosition);
                }
            }
        });
    }

    @Override
    public int getItemCount() {
        return data.length;
    }

    public interface OnItemClickListener {
        void onItemClick(int position);
    }

    public interface OnLongItemClickListener {
        void onLongItemClick(int position);
    }

    public static class MyViewHolder extends RecyclerView.ViewHolder {
        public TextView textView;

        public MyViewHolder(View itemView) {
            super(itemView);
            textView = itemView.findViewById(R.id.item_text);
        }
    }
}