using System.Diagnostics;

public static class  Fast
{
    public static double calcFast(int _a, int _b)
    {
        const int iter = 10000000;
        int i = 0;
        int count = 0;
        Stopwatch stopWatch = new();
        double time = 0;
        var sum = 0.0;
        
        double timeDouble = 0;
       while (count <= 4)
        {
            count++;
            stopWatch.Start();

            for(i=0; i<=iter; i++)
            {
                _a += _b;
            }
            
            stopWatch.Stop();

            time = stopWatch.ElapsedMilliseconds;
      
            time /= 1000; // получаем в секундах
            time /= iter; // получаем сколько одна итерация выполняется
            sum += time;
        }
        sum /= 4;
        return 1/sum;
    }
}

public static class MainFunc
{
   static void Main(string[] args)
    {

        var result=Fast.calcFast(1, 1);

        Console.WriteLine("Operations per sec = "+result );
    }
}
