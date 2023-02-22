using System.Diagnostics;

public static class  Fast
{
    public static List<long> calcFast(int _a, int _b)
    {
        const int iter = 1000000;
        int i = 0;
        Stopwatch stopWatch = new Stopwatch();
        TimeSpan ts = new TimeSpan();
        List<long> timeList = new List<long> { };
        stopWatch.Start();
        while (i<=iter)
        {
            
            i++;
            _a += _b;
                       

        }
        stopWatch.Stop();

        ts = stopWatch.Elapsed;
        timeList.Add((int)(stopWatch.ElapsedMilliseconds / 1000000));

        return timeList;
    }
}

public static class MainFunc
{
   static void Main(string[] args)
    {
        List<int> timeList = new List<int> { };

        timeList = Fast.calcFast(1, 1);

        Console.WriteLine("Average time (ms) = "+ timeList.Average());
    }
}
