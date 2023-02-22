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
        StreamWriter fs = new StreamWriter("../../../out.txt");
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

            /// Создание файлового потока с созданием/открытием файла
            try
            {
                // Записываем в текстовый файл время выполнения моей функции
                fs.WriteLine($"Время выполнения функции, проход {count} " + str);
            }
            catch (Exception e) // Если файл не создался, то бросим исключение
            {
                Console.WriteLine("Exception: " + e.Message);
            }
           

        }
        fs.Close();
    }
        
}