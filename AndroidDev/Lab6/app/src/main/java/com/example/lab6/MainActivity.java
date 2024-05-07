package com.example.lab6;

import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;

import androidx.appcompat.app.AppCompatActivity;
import androidx.fragment.app.FragmentManager;
import androidx.fragment.app.FragmentTransaction;

import com.example.lab6.DBHelper;

public class MainActivity extends AppCompatActivity {

    private EditText nameEditText;
    private EditText ageEditText;
    private Button addButton;

    private DBHelper dbHelper;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        nameEditText = findViewById(R.id.nameEditText);
        ageEditText = findViewById(R.id.ageEditText);
        addButton = findViewById(R.id.addButton);

        dbHelper = new DBHelper(this);

        DataFragment dataFragment = new DataFragment();
        FragmentManager fragmentManager = getSupportFragmentManager();
        FragmentTransaction fragmentTransaction = fragmentManager.beginTransaction();
        fragmentTransaction.replace(R.id.container, dataFragment);
        fragmentTransaction.commit();

        addButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String name = nameEditText.getText().toString();
                int age = Integer.parseInt(ageEditText.getText().toString());

                DataFragment dataFragment = (DataFragment) getSupportFragmentManager().findFragmentById(R.id.container);
                if (dataFragment != null) {
                    dbHelper.insertData(name, age); // Вставка данных в базу данных через DBHelper
                    dataFragment.updateData();
                }
            }
        });
    }
}