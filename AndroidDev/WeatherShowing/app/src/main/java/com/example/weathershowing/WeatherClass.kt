package com.example.weathershowing

import android.content.Context
import android.util.Log
import com.android.volley.Request
import com.android.volley.Response
import com.android.volley.toolbox.JsonObjectRequest
import com.android.volley.toolbox.Volley
import org.json.JSONException
import org.json.JSONObject

class WeatherClass(private val context: Context) {
    private val TAG = "WeatherClass"
    private val API_KEY = "35b137e1f615ced62d56912af244e45e" // API ключ OpenWeatherMap

    // Глобальная переменная для ссылки на запрос
    private var currentWeatherRequest: JsonObjectRequest? = null

    // Метод для получения текущей погоды по координатам
    fun getCurrentWeather(latitude: Double, longitude: Double, callback: (String) -> Unit) {
        val url = "https://api.openweathermap.org/data/2.5/weather?lat=$latitude&lon=$longitude&appid=$API_KEY&units=metric"

        val queue = Volley.newRequestQueue(context)

        currentWeatherRequest?.cancel() // Отмена предыдущего запроса, если есть

        currentWeatherRequest = JsonObjectRequest(
            Request.Method.GET, url, null,
            { response ->
                // Обработка успешного ответа
                Log.d(TAG, "Response: $response")
                try {
                    val weatherDescription = response.getJSONArray("weather").getJSONObject(0).getString("description")
                    val temperature = response.getJSONObject("main").getString("temp")
                    val cityName = response.getString("name")
                    val result = "Weather in $cityName: $weatherDescription, Temperature: $temperature°C"
                    callback(result)
                } catch (e: JSONException) {
                    Log.e(TAG, "Error parsing JSON: ${e.message}")
                    callback("Error: Failed to parse weather data")
                }
            },
            { error ->
                // Обработка ошибок
                Log.e(TAG, "Error: $error")
                callback("Error occurred while fetching weather data")
            }
        )

        // Добавление запроса в очередь
        currentWeatherRequest?.let { queue.add(it) }
    }
}
