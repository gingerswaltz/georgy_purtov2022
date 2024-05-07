package com.example.lab8java;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;
import androidx.wear.widget.BoxInsetLayout;
import androidx.wear.widget.WearableLinearLayoutManager;
import androidx.wear.widget.WearableRecyclerView;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

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
                "Яблоко",
                "Банан",
                "Апельсин",
                "Клубника",
                "Морковь",
                "Огурец",
                "Помидор",
                "Салат",
                "Говядина",
                "Свинина",
                "Курица",
                "Баранина"

        };

        // Создаем адаптер и устанавливаем его для списка категорий
        adapter = new MyAdapter(categories);
        recyclerView.setAdapter(adapter);

        // Устанавливаем обработчик щелчка по элементу списка категорий
//        adapter.setOnItemClickListener(new MyAdapter.OnItemClickListener() {
//            @Override
//            public void onItemClick(int position) {
//                // Получаем выбранную категорию
//                String category = categories[position];
//
//                // Открываем новую активность, передавая выбранную категорию
//                Intent intent = new Intent(MainActivity.this, SubCategoryActivity.class);
//                intent.putExtra("category", category);
//                startActivity(intent);
//            }
//        });
    }
}