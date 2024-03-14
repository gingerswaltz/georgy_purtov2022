package com.example.weathershowing

import android.os.Bundle
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.material3.MaterialTheme
import androidx.compose.material3.Surface
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.ui.Modifier
import androidx.compose.ui.tooling.preview.Preview
import com.example.weathershowing.ui.theme.WeatherShowingTheme


class MainActivity : ComponentActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        val weatherObj = WeatherClass(this)

        // Создаем новый поток для выполнения сетевой операции получения погоды
        val networkThread = Thread {
            weatherObj.getCurrentWeather(52.03, 113.50) { result ->
                // После получения результатов вызываем setContent для обновления пользовательского интерфейса
                runOnUiThread {
                    setContent {
                        WeatherShowingTheme {
                            // A surface container using the 'background' color from the theme
                            Surface(
                                modifier = Modifier.fillMaxSize(),
                                color = MaterialTheme.colorScheme.background
                            ) {
                                Greeting(result)
                            }
                        }
                    }
                }
            }
        }
        // Запускаем поток для выполнения операции получения погоды
        networkThread.start()
    }
}

@Composable
fun Greeting(name: String, modifier: Modifier = Modifier) {
    Text(
        text = "$name",
        modifier = modifier
    )
}

@Preview(showBackground = true)
@Composable
fun GreetingPreview() {
    WeatherShowingTheme {
        Greeting("Android")
    }
}


//
//import android.util.Log
//import androidx.appcompat.app.AppCompatActivity
//import com.android.volley.Request
//import com.android.volley.Response
//import com.android.volley.toolbox.StringRequest
//import com.android.volley.toolbox.Volley
//
//class MainActivity : AppCompatActivity() {
//    override fun onCreate(savedInstanceState: Bundle?) {
//        super.onCreate(savedInstanceState)
//        setContentView(R.layout.activity_main)
//
//        // Создаем очередь запросов Volley
//        val queue = Volley.newRequestQueue(this)
//
//        // URL, на который будет отправлен GET-запрос
//        val url = "https://www.example.com"
//
//        // Создаем строковый запрос типа GET
//        val stringRequest = StringRequest(Request.Method.GET, url,
//            Response.Listener<String> { response ->
//                // Успешный ответ от сервера
//                Log.d("Volley", "Response: $response")
//            },
//            Response.ErrorListener { error ->
//                // Ошибка при получении ответа от сервера
//                Log.e("Volley", "Error: ${error.message}")
//            })
//
//        // Добавляем запрос в очередь
//        queue.add(stringRequest)
//    }
//}
