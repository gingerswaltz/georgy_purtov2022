package com.example.lab7;

import android.app.AlertDialog;
import android.content.DialogInterface;
import android.database.Cursor;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

import androidx.annotation.NonNull;
import androidx.recyclerview.widget.RecyclerView;

public class DataAdapter extends RecyclerView.Adapter<DataAdapter.DataViewHolder> {

    private Cursor cursor;

    public void setCursor(Cursor cursor) {
        this.cursor = cursor;
        notifyDataSetChanged();
    }

    @NonNull
    @Override
    public DataViewHolder onCreateViewHolder(@NonNull ViewGroup parent, int viewType) {
        View itemView = LayoutInflater.from(parent.getContext()).inflate(R.layout.fragment_data_item, parent, false);
        return new DataViewHolder(itemView);
    }

    @Override
    public void onBindViewHolder(@NonNull DataViewHolder holder, int position) {
        if (cursor != null && cursor.moveToPosition(position)) {
            int id = cursor.getInt(cursor.getColumnIndexOrThrow("id"));
            String name = cursor.getString(cursor.getColumnIndexOrThrow("name"));
            int age = cursor.getInt(cursor.getColumnIndexOrThrow("age"));
            holder.bindData(id, name, age);
        }
    }

    @Override
    public int getItemCount() {
        return cursor != null ? cursor.getCount() : 0;
    }

    public class DataViewHolder extends RecyclerView.ViewHolder  {

        private TextView dataTextView;
        private Button deleteButton, editButton; // добавляем кнопку для редактирования

        public DataViewHolder(@NonNull View itemView) {
            super(itemView);
            dataTextView = itemView.findViewById(R.id.dataTextView);
            deleteButton = itemView.findViewById(R.id.deleteButton);
            editButton = itemView.findViewById(R.id.editButton); // находим кнопку для редактирования
        }

        public void bindData(int id, String name, int age) {
            dataTextView.setText("ID: " + id + ", Name: " + name + ", Age: " + age);
            deleteButton.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View v) {
                    showDialog(id);
                }
            });

            setEditButtonClickListener(id, name, age); // устанавливаем обработчик для кнопки редактирования
        }

        private void setEditButtonClickListener(final int id, final String name, final int age) {
            editButton.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View v) {
                    showEditDialog(id, name, age); // вызываем метод для отображения диалога редактирования
                }
            });
        }



        private void showDialog(final int id) {
            AlertDialog.Builder builder = new AlertDialog.Builder(itemView.getContext());
            builder.setTitle("Delete Data");
            builder.setMessage("Are you sure you want to delete this data?");
            builder.setPositiveButton("Delete", new DialogInterface.OnClickListener() {
                @Override
                public void onClick(DialogInterface dialog, int which) {
                    DBHelper dbHelper = new DBHelper(itemView.getContext());
                    dbHelper.deleteData(id);
                    cursor = dbHelper.getAllData();
                    notifyDataSetChanged();
                }
            });
            builder.setNegativeButton("Cancel", null);
            builder.show();
        }

        private  void showEditDialog(final int id, String name, int age) {
            AlertDialog.Builder builder = new AlertDialog.Builder(itemView.getContext());
            builder.setTitle("Edit Data");

            View view = LayoutInflater.from(itemView.getContext()).inflate(R.layout.dialog_edit_data, null);
            final EditText nameEditText = view.findViewById(R.id.nameEditText);
            final EditText ageEditText = view.findViewById(R.id.ageEditText);

            nameEditText.setText(name);
            ageEditText.setText(String.valueOf(age));

            builder.setView(view);
            builder.setPositiveButton("Save", new DialogInterface.OnClickListener() {
                @Override
                public void onClick(DialogInterface dialog, int which) {
                    String newName = nameEditText.getText().toString().trim();
                    String ageString = ageEditText.getText().toString().trim();

                    // Проверка на пустоту полей
                    if (newName.isEmpty() || ageString.isEmpty()) {
                        Toast.makeText(itemView.getContext(), "Name and age cannot be empty", Toast.LENGTH_SHORT).show();
                        return;
                    }

                    int newAge;
                    try {
                        newAge = Integer.parseInt(ageString);
                    } catch (NumberFormatException e) {
                        Toast.makeText(itemView.getContext(), "Invalid age format", Toast.LENGTH_SHORT).show();
                        return;
                    }

                    // Проверка на корректность возраста (например, неотрицательное значение)
                    if (newAge < 0) {
                        Toast.makeText(itemView.getContext(), "Age cannot be negative", Toast.LENGTH_SHORT).show();
                        return;
                    }

                    DBHelper dbHelper = new DBHelper(itemView.getContext());
                    dbHelper.updateData(id, newName, newAge);
                    cursor = dbHelper.getAllData();
                    notifyDataSetChanged();
                }
            });
            builder.setNegativeButton("Cancel", null);
            builder.show();
        }
    }
}
