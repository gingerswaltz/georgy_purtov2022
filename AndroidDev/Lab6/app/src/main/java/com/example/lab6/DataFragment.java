package com.example.lab6;

import android.database.Cursor;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.LinearLayout;
import android.widget.TextView;

import androidx.fragment.app.Fragment;

public class DataFragment extends Fragment {

    private View view;
    private TextView dataTextView;

    private DBHelper dbHelper;

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        view = inflater.inflate(R.layout.fragment_data, container, false);

        dataTextView = view.findViewById(R.id.dataTextView);

        dbHelper = new DBHelper(getActivity());

        displayData();

        return view;
    }

    public void updateData() {
        displayData();
    }

    private void displayData() {
        StringBuilder stringBuilder = new StringBuilder();
        Cursor cursor = dbHelper.getAllData();

        LinearLayout layout = view.findViewById(R.id.container);
        layout.removeAllViews(); // Очистка контейнера перед добавлением новых элементов

        LayoutInflater inflater = LayoutInflater.from(getActivity());

        while (cursor.moveToNext()) {
            final int id = cursor.getInt(cursor.getColumnIndexOrThrow("id"));
            String name = cursor.getString(cursor.getColumnIndexOrThrow("name"));
            int age = cursor.getInt(cursor.getColumnIndexOrThrow("age"));
            stringBuilder.append("ID: ").append(id).append(", Name: ").append(name).append(", Age: ").append(age).append("\n");

            View itemView = inflater.inflate(R.layout.fragment_data_item, layout, false);

            TextView dataTextView = itemView.findViewById(R.id.dataTextView);
            dataTextView.setText("ID: " + id + ", Name: " + name + ", Age: " + age);

            Button deleteButton = itemView.findViewById(R.id.deleteButton);
            deleteButton.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View v) {
                    dbHelper.deleteData(id);
                    displayData();
                }
            });

            layout.addView(itemView);
        }

        cursor.close();
    }
}