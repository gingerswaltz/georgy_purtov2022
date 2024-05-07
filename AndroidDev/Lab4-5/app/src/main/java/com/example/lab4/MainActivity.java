package com.example.lab4;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;

import com.google.gson.Gson;
import com.google.gson.reflect.TypeToken;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.lang.reflect.Type;
import java.util.List;
import androidx.recyclerview.widget.RecyclerView;
import androidx.recyclerview.widget.LinearLayoutManager;

public class MainActivity extends AppCompatActivity {
    private JsonParser jsonParser;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Создание экземпляра JsonParser
        jsonParser = new JsonParser();

        // Получение JSON-строки из файла
        String jsonString = readJsonFromFile();

        // Парсинг JSON-строки
        List<Person> persons = jsonParser.parseJson(jsonString);

        // Установка флага isLastItem на последний элемент списка
        for (int i = 0; i < persons.size(); i++) {
            Person person = persons.get(i);
            person.setLastItem(i == persons.size() - 1);
        }

        // Отображение данных в UI
        displayData(persons);
    }

    private String readJsonFromFile() {
        StringBuilder stringBuilder = new StringBuilder();
        try {
            InputStream inputStream = getAssets().open("data.json");
            BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(inputStream));
            String line;
            while ((line = bufferedReader.readLine()) != null) {
                stringBuilder.append(line);
            }
            bufferedReader.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
        return stringBuilder.toString();
    }


    private void displayData(List<Person> persons) {
        // Выполните действия для отображения данных в соответствующих элементах пользовательского интерфейса
        // Например, установите значения в TextView или RecyclerView Adapter
        RecyclerView recyclerView = findViewById(R.id.recyclerView);
        // Создание и настройка адаптера
        PersonAdapter adapter = new PersonAdapter(this, persons); // Исправленная строка
        recyclerView.setAdapter(adapter);
        recyclerView.setLayoutManager(new LinearLayoutManager(this));

        adapter.setOnItemClickListener(new PersonAdapter.OnItemClickListener() {
            @Override
            public void onItemClick(Person person) {
                Intent intent = new Intent(MainActivity.this, PersonDetailsActivity.class);
                intent.putExtra(PersonDetailsActivity.EXTRA_PERSON_NAME, person.getName());
                intent.putExtra(PersonDetailsActivity.EXTRA_PERSON_PHONE, person.getPhoneNumber());
                intent.putExtra(PersonDetailsActivity.EXTRA_PERSON_EMAIL, person.getEmail());
                intent.putExtra(PersonDetailsActivity.EXTRA_PERSON_ADDRESS, person.getAddress());
                startActivity(intent);
            }
        });
        // Обновление адаптера, если данные изменяются
        adapter.notifyDataSetChanged();
    }
}