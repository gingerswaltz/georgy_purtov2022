package com.example.lab7;

import android.content.ContentValues;
import android.content.Context;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;

public class DBHelper extends SQLiteOpenHelper {

    // Имя базы данных
    private static final String DATABASE_NAME = "mydatabase.db";
    // Версия базы данных
    private static final int DATABASE_VERSION = 1;
    // Имя таблицы в базе данных
    private static final String TABLE_NAME = "mytable";

    // Конструктор класса DBHelper
    public DBHelper(Context context) {
        // Вызываем конструктор родительского класса SQLiteOpenHelper
        super(context, DATABASE_NAME, null, DATABASE_VERSION);
    }

    // Метод вызывается при создании базы данных
    @Override
    public void onCreate(SQLiteDatabase db) {
        // Логика создания таблицы и определения ее структуры
        String createTableQuery = "CREATE TABLE mytable ("
                + "id INTEGER PRIMARY KEY,"
                + "name TEXT,"
                + "age INTEGER)";
        db.execSQL(createTableQuery); // Выполняем SQL-запрос для создания таблицы
    }

    // Метод вызывается при обновлении базы данных
    @Override
    public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion) {
        // Логика обновления схемы базы данных при изменении версии
        if (oldVersion < 2) {
            // Если текущая версия базы данных меньше 2, выполняем необходимые изменения
            String alterTableQuery = "ALTER TABLE mytable ADD COLUMN email TEXT";
            db.execSQL(alterTableQuery); // Выполняем SQL-запрос для изменения схемы таблицы
        }
    }

    // Метод для обновления данных в таблице
    public void updateData(int id, String newName, int newAge) {
        SQLiteDatabase db = this.getWritableDatabase(); // Получаем доступ для записи в базу данных
        ContentValues values = new ContentValues(); // Создаем объект ContentValues для хранения значений столбцов
        values.put("name", newName); // Устанавливаем новое значение имени
        values.put("age", newAge); // Устанавливаем новое значение возраста
        String whereClause = "id = ?"; // Условие для выбора строки по идентификатору
        String[] whereArgs = {String.valueOf(id)}; // Аргументы для условия выборки
        db.update("mytable", values, whereClause, whereArgs); // Обновляем данные в таблице
        db.close(); // Закрываем соединение с базой данных
    }

    // Метод для вставки новых данных в таблицу
    public void insertData(String name, int age) {
        SQLiteDatabase db = getWritableDatabase(); // Получаем доступ для записи в базу данных
        ContentValues values = new ContentValues(); // Создаем объект ContentValues для хранения значений столбцов
        values.put("name", name); // Устанавливаем значение имени
        values.put("age", age); // Устанавливаем значение возраста
        db.insert("mytable", null, values); // Вставляем новую запись в таблицу
        db.close(); // Закрываем соединение с базой данных
    }

    // Метод для удаления данных из таблицы
    public void deleteData(int id) {
        SQLiteDatabase db = this.getWritableDatabase(); // Получаем доступ для записи в базу данных
        db.delete(TABLE_NAME, "id=?", new String[]{String.valueOf(id)}); // Удаляем строку по заданному идентификатору
        db.close(); // Закрываем соединение с базой данных
    }

    // Метод для получения всех данных из таблицы
    public Cursor getAllData() {
        SQLiteDatabase db = getReadableDatabase(); // Получаем доступ для чтения данных из базы данных
        String[] projection = {"id", "name", "age"}; // Список столбцов, которые нужно получить из таблицы
        return db.query("mytable", projection, null, null, null, null, null); // Получаем данные из таблицы
    }
}
