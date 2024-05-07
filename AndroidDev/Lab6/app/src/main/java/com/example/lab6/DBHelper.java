package com.example.lab6;

import android.content.ContentValues;
import android.content.Context;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;

public class DBHelper extends SQLiteOpenHelper {

    private static final String DATABASE_NAME = "mydatabase.db";
    private static final int DATABASE_VERSION = 1;
    private static final String TABLE_NAME = "mytable"; // Добавьте эту строку

    public DBHelper(Context context) {
        super(context, DATABASE_NAME, null, DATABASE_VERSION);
    }

    @Override
    public void onCreate(SQLiteDatabase db) {
        // Логика создания таблиц и других объектов базы данных
        String createTableQuery = "CREATE TABLE mytable ("
                + "id INTEGER PRIMARY KEY,"
                + "name TEXT,"
                + "age INTEGER)";
        db.execSQL(createTableQuery);
    }

    @Override
    public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion) {
        // Логика обновления схемы базы данных
        if (oldVersion < 2) {
            // Добавление новых столбцов или изменение схемы таблицы
            String alterTableQuery = "ALTER TABLE mytable ADD COLUMN email TEXT";
            db.execSQL(alterTableQuery);
        }
    }

    public void insertData(String name, int age) {
        SQLiteDatabase db = getWritableDatabase();
        ContentValues values = new ContentValues();
        values.put("name", name);
        values.put("age", age);
        db.insert("mytable", null, values);
        db.close();
    }

    public void deleteData(int id) {
        SQLiteDatabase db = this.getWritableDatabase();
        db.delete(TABLE_NAME, "id=?", new String[]{String.valueOf(id)});
        db.close();
    }

    public Cursor getAllData() {
        SQLiteDatabase db = getReadableDatabase();
        String[] projection = {"id", "name", "age"}; // Добавить "id" в список столбцов
        return db.query("mytable", projection, null, null, null, null, null);
    }
}