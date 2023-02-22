namespace Program;

using System;
using System.Diagnostics;
using System.Threading;

class Point
{
    private float _x1; // x1
    private float _x2; // x2
    private float _y1; // y1
    private float _y2; // y2

    /// Конструктор 1 с параметрами
    public Point(float value1, float value2, float value3, float value4)
    {
        set_FirstPoint(value1, value2);
        set_SecondPoint(value3,value4);
    }

    /// Конструктор 2 без параметров
    public Point()
    {
        
    }

    // Сеттер x1,y1
    public void set_FirstPoint(float value1, float value2)

    {
        _x1 = value1;
        _y1 = value2;

     }

    // get x1,y1 (кортеж)
    public (float, float) get_FirstPoint() { return (_x1, _y1); }


    // сеттер x2,y2
    public void set_SecondPoint(float value1, float value2 )
    {
        _x2 = value1;
        _y2 = value2;
    }
    
    // get x2,y2 (кортеж)
    public (float, float) get_SecondPoint() { return (_x2, _y2); }
    
    // Процедура вычисления
    public string calcDist() 
    {

        // инициализация объекта таймера 
        Stopwatch stopWatch = new Stopwatch();
        stopWatch.Start();

        if ((_x1 == 0) && (_y1 == 0))
        {
            Console.WriteLine("1-я точка ближе");
            stopWatch.Stop();
            TimeSpan ts1 = stopWatch.Elapsed;
            Console.WriteLine("Время выполнения функции: " + ts1.ToString() + '\n');
            return ts1.ToString();

        }
        else

            if ((_x2 == 0) && (_y2 == 0))
        {
            Console.WriteLine("2-я точка ближе");
            stopWatch.Stop();
            TimeSpan ts1 = stopWatch.Elapsed;
            Console.WriteLine("Время выполнения функции: " + ts1.ToString() + '\n');
            return ts1.ToString();
        } else

            if (((_x1 * _x1) + (_y1 * _y1)) < ((_x2 * _x2) + (_y2 * _y2)))
            Console.WriteLine("1-я точка ближе");
        else if (((_x1 * _x1) + (_y1 * _y1) == (_x2 * _x2) + (_y2 * _y2)))
            Console.WriteLine("Точки равноудалены");
        else Console.WriteLine("2-ая точка ближе");

        // big O(16)
        stopWatch.Stop();
        TimeSpan ts = stopWatch.Elapsed;

        Console.WriteLine("Время выполнения функции: "+ts.ToString()+'\n');
        return ts.ToString();

    }
}
