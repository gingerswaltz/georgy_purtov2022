package com.example.lab7;

import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

import androidx.fragment.app.Fragment;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

public class DataFragment extends Fragment {

    private RecyclerView recyclerView;
    private DataAdapter dataAdapter;
    private EditText nameEditText, ageEditText;
    private Button addButton;

    private DBHelper dbHelper;

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        View view = inflater.inflate(R.layout.fragment_data, container, false);
// Находим RecyclerView в макете и связываем его с переменной recyclerView
        recyclerView = view.findViewById(R.id.recyclerView);

// Устанавливаем менеджер макета для RecyclerView.
// LinearLayoutManager располагает элементы в виде списка в одном направлении.
// В данном случае используется вертикальное расположение элементов.
        recyclerView.setLayoutManager(new LinearLayoutManager(getActivity()));

// Создаем экземпляр адаптера данных для RecyclerView
        dataAdapter = new DataAdapter();

// Устанавливаем адаптер для RecyclerView.
// Адаптер отвечает за привязку данных к элементам списка и управление их отображением.
        recyclerView.setAdapter(dataAdapter);


        nameEditText = view.findViewById(R.id.nameEditText);
        ageEditText = view.findViewById(R.id.ageEditText);
        addButton = view.findViewById(R.id.addButton);
        addButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                // Получаем введенное имя и возраст из текстовых полей
                String name = nameEditText.getText().toString().trim();
                String ageString = ageEditText.getText().toString().trim();

                // Проверяем, что оба поля не пусты
                if (name.isEmpty() || ageString.isEmpty()) {
                    // Если хотя бы одно поле пустое, выводим сообщение об ошибке
                    Toast.makeText(getActivity(), "Please enter name and age", Toast.LENGTH_SHORT).show();
                    return; // Прерываем выполнение метода, чтобы не добавлять пустую запись
                }

                // Проверяем, что возраст представлен числом
                int age;
                try {
                    age = Integer.parseInt(ageString);
                } catch (NumberFormatException e) {
                    // Если возраст не является числом, выводим сообщение об ошибке
                    Toast.makeText(getActivity(), "Please enter a valid age", Toast.LENGTH_SHORT).show();
                    return; // Прерываем выполнение метода, чтобы не добавлять некорректную запись
                }

                // Проверяем, что возраст неотрицательный
                if (age < 0) {
                    // Если возраст отрицательный, выводим сообщение об ошибке
                    Toast.makeText(getActivity(), "Age cannot be negative", Toast.LENGTH_SHORT).show();
                    return; // Прерываем выполнение метода, чтобы не добавлять некорректную запись
                }

                // Если все проверки пройдены успешно, добавляем данные в базу данных
                dbHelper.insertData(name, age);

                // Обновляем отображение данных
                updateData();

                // Очищаем поля ввода
                nameEditText.setText("");
                ageEditText.setText("");
            }
        });

        // Создаем экземпляр DBHelper для работы с базой данных
        dbHelper = new DBHelper(getActivity());

        // Отображаем данные из базы данных
        displayData();

        return view;
    }

    // Метод для обновления отображения данных
    public void updateData() {
        displayData();
    }

    // Метод для отображения данных в RecyclerView
    private void displayData() {
        // Устанавливаем Cursor адаптеру, чтобы он мог отображать данные
        dataAdapter.setCursor(dbHelper.getAllData());
    }
}