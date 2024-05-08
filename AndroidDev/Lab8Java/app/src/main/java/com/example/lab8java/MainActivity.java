package com.example.lab8java;

import android.app.Activity;
import android.content.Context;
import android.os.Bundle;
import android.widget.Toast;

import androidx.recyclerview.widget.RecyclerView;
import androidx.wear.widget.WearableLinearLayoutManager;
import androidx.wear.widget.WearableRecyclerView;

public class MainActivity extends Activity {
    private WearableRecyclerView recyclerView;
    private MyAdapter adapter;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Находим WearableRecyclerView в макете
        recyclerView = findViewById(R.id.recycler_view);

        // Создаем и настраиваем WearableLinearLayoutManager
        WearableLinearLayoutManager layoutManager = new WearableLinearLayoutManager(this);
        recyclerView.setLayoutManager(layoutManager);

        // Создаем массив данных для списка категорий
        String[] categories = {
                "Бобэр",
                "Яблоко",
                "Апельсин",
                "Клубника",
                "Морковь",
                "Кнопка взрыва",
                "Помидор",
                "Ракета",
                "Говядина",
                "Свинина",
                "Бекон",
                "Баранина"
        };

        // Создаем адаптер и устанавливаем его для списка категорий
        adapter = new MyAdapter(categories);
        recyclerView.setAdapter(adapter);

        // Устанавливаем слушатель долгого нажатия на элемент списка
        adapter.setOnLongItemClickListener(new MyAdapter.OnLongItemClickListener() {
            @Override
            public void onLongItemClick(int position) {
                // Выводим сообщение с названием выбранного элемента по долгому нажатию
                String selectedItem = categories[position];
                Context context = getApplicationContext();
                Toast.makeText(context, "Долгое нажатие: " + selectedItem, Toast.LENGTH_SHORT).show();
            }
        });
    }
}
