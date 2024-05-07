package com.example.lab7;

import android.os.Bundle;
import androidx.appcompat.app.AppCompatActivity;


public class MainActivity extends AppCompatActivity {

    private DataFragment dataFragment;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        dataFragment = (DataFragment) getSupportFragmentManager().findFragmentById(R.id.dataFragmentContainer);

        if (dataFragment == null) {
            dataFragment = new DataFragment();
            getSupportFragmentManager().beginTransaction()
                    .add(R.id.dataFragmentContainer, dataFragment)
                    .commit();
        }
    }

    @Override
    protected void onResume() {
        super.onResume();
        dataFragment.updateData();
    }
}