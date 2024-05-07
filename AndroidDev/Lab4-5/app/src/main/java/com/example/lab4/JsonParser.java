package com.example.lab4;

import com.google.gson.Gson;
import com.google.gson.reflect.TypeToken;

import java.lang.reflect.Type;
import java.util.List;

public class JsonParser {
    public List<Person> parseJson(String jsonString) {
        Gson gson = new Gson();
        Type personListType = new TypeToken<List<Person>>() {
        }.getType();
        List<Person> persons = gson.fromJson(jsonString, personListType);
        return persons;
    }
}
