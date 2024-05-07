//package com.example.lab8java;
//
//import android.app.Activity;
//import android.os.Bundle;
//
//import androidx.wear.widget.WearableLinearLayoutManager;
//import androidx.wear.widget.WearableRecyclerView;
//import androidx.recyclerview.widget.LinearLayoutManager;
//
//
//public class SubCategoryActivity extends Activity {
//    private WearableRecyclerView recyclerView;
//    private MyAdapter adapter;
//
//    @Override
//    protected void onCreate(Bundle savedInstanceState) {
//        super.onCreate(savedInstanceState);
//        setContentView(R.layout.activity_sub_category);
//
//        // Получаем выбранную категорию из интента
//        String category = getIntent().getStringExtra("category");
//
//        // Находим WearableRecyclerView в макете
//        recyclerView = findViewById(R.id.sub_recycler_view);
//
//        // Создаем и настраиваем LinearLayoutManager
//        LinearLayoutManager layoutManager = new LinearLayoutManager(this);
//        recyclerView.setLayoutManager(layoutManager);
//
//        // Создаем массив данных для списка разных видов категории
//        String[] subCategories;
//
//        // Заполняем массив данных в зависимости от выбранной категории
//        if (category.equals("Фрукты")) {
//            subCategories = new String[]{
//                    "Яблоко",
//                    "Банан",
//                    "Апельсин",
//                    "Клубника"
//            };
//        } else if (category.equals("Овощи")) {
//            subCategories = new String[]{
//                    "Морковь",
//                    "Огурец",
//                    "Помидор",
//                    "Салат"
//            };
//        } else if (category.equals("Мясо")) {
//            subCategories = new String[]{
//                    "Говядина",
//                    "Свинина",
//                    "Курица",
//                    "Баранина"
//            };
//        } else if (category.equals("Рыба")) {
//            subCategories = new String[]{
//                    "Лосось",
//                    "Тунец",
//                    "Скумбрия",
//                    "Карп"
//            };
//        } else {
//            // Если выбранная категория неизвестна, выход из активности
//            finish();
//            return;
//        }
//
//        // Создаем адаптер и устанавливаем его для списка разных видов категории
//        adapter = new MyAdapter(subCategories);
//        recyclerView.setAdapter(adapter);
//    }
//}