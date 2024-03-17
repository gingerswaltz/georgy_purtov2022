package com.example.weatherfinal

import android.os.Bundle
import android.os.Handler
import android.os.Looper
import android.widget.TextView
import androidx.activity.enableEdgeToEdge
import androidx.appcompat.app.AppCompatActivity
import androidx.core.view.ViewCompat
import androidx.core.view.WindowInsetsCompat
import java.util.concurrent.Executor
import java.util.concurrent.Executors

class SecondActivity : AppCompatActivity() {

    companion object {
        const val LATITUDE = "latitudeValue"
        const val LONGITUDE = "longitudeValue"
    }

    private val weatherClass = WeatherClass(this) // Создаем экземпляр WeatherClass

    // Определяем виджет TextView, в который будем выводить погоду
    private lateinit var weatherTextView: TextView

    // Определяем объект Handler для обновления интерфейса из потока
    private val handler = Handler(Looper.getMainLooper())

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        enableEdgeToEdge()
        setContentView(R.layout.activity_second)
        // Находим TextView по его ID
        weatherTextView = findViewById(R.id.weatherTextView)
        ViewCompat.setOnApplyWindowInsetsListener(findViewById(R.id.main)) { v, insets ->
            val systemBars = insets.getInsets(WindowInsetsCompat.Type.systemBars())
            v.setPadding(systemBars.left, systemBars.top, systemBars.right, systemBars.bottom)
            insets
        }
        showCurrentWeather();
    }

    // Метод для отображения текущей погоды
    private fun showCurrentWeather(){
        val executor = Executors .newSingleThreadExecutor()

        // выполняем код в отдельном потоке
        executor.execute {
            // Получаем широту и долготу из констант компаньона
            val latitude = intent.getDoubleExtra(LATITUDE, 0.0)
            val longitude = intent.getDoubleExtra(LONGITUDE, 0.0)
            weatherClass.getCurrentWeather(latitude, longitude) { weather ->
                handler.post {
                    weatherTextView.text = weather
                }
            }
        }

    }
}