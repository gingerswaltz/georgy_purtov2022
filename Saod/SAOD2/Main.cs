namespace Program;
using System;



class MainFunc
{
    public static void Main(string [] args)
    {
        
        
        // инициализация переменных и обьекта класса
        Point point = new Point();
        float value = 0;
        float value2 = 0;
        int count = 0;
        List<Point> listPoint = new List<Point>();
        /// Создание файлового потока с созданием/открытием файла
        StreamWriter fs = new StreamWriter("../../../out.txt");
        fs.WriteLine("Напишите программу, определяющую какая из двух точек,\nзаданных своими координатами, расположена ближе к началу координат.\nКакой случай для алгоритма является наилучшим? Нанхудшим?\nСколько сравнений требуется этому алгоритму? Результаты тестирования вывести в текстовый файл.\n");

        while (count<5) // делаем 5 кругов
        {
        
            count++;
            Console.WriteLine($"Count {count} of 5\n");
            // ввод точек x1,y1
            Console.WriteLine("Input point x1, y1");
            value = (float)Convert.ToDecimal(Console.ReadLine());
            value2 = (float)Convert.ToDecimal(Console.ReadLine());
            point.set_FirstPoint(value, value2); // сеттер 


            // ввод точек x2,y2
            Console.WriteLine("Input point x2, y2");
            value = (float)Convert.ToDecimal(Console.ReadLine());
            value2 = (float)Convert.ToDecimal(Console.ReadLine());
            point.set_SecondPoint(value, value2); // сеттер

            listPoint.Add(point); // Добавим в коллекцию ссылку на обьект

            string str = point.calcDist(); // Расчёт + получение данных о времени выполнения работы

            
           fs.WriteLine ($"Время выполнения функции, проход {count}, точки x1, y1 {point.get_FirstPoint()}, точки x2,y2 {point.get_SecondPoint()}:  " + str);
            
           

        }
        fs.Close();
    }
        
}