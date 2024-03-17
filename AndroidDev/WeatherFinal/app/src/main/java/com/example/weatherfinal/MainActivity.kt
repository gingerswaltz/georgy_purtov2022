package com.example.weatherfinal

import android.content.Intent
import android.os.Bundle
import android.view.View
import android.widget.EditText
import android.widget.TextView
import androidx.activity.enableEdgeToEdge
import androidx.appcompat.app.AppCompatActivity
import androidx.core.view.ViewCompat
import androidx.core.view.WindowInsetsCompat

class MainActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        enableEdgeToEdge()
        setContentView(R.layout.activity_main)
        ViewCompat.setOnApplyWindowInsetsListener(findViewById(R.id.main)) { v, insets ->
            val systemBars = insets.getInsets(WindowInsetsCompat.Type.systemBars())
            v.setPadding(systemBars.left, systemBars.top, systemBars.right, systemBars.bottom)
            insets
        }
    }

    fun onSubmit(view: View) {
        val editLatitude = findViewById<EditText>(R.id.editLatitude)
        val latitudeValue = editLatitude.text.toString().toDouble() //  значение широты

        val editLongitude = findViewById<EditText>(R.id.editLongitude)
        val longitudeValue = editLongitude.text.toString().toDouble() // значение долготы

        val intentDegree = Intent(this, SecondActivity::class.java)
        intentDegree.putExtra(SecondActivity.LATITUDE, latitudeValue)
        intentDegree.putExtra(SecondActivity.LONGITUDE, longitudeValue)
        startActivity(intentDegree) // Запускаем SecondActivity с переданными данными о широте и долготе



    }

}