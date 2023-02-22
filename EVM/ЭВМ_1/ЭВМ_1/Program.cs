﻿using System.Diagnostics;

public static class  Fast
{
    public static decimal calcFast(int _a, int _b)
    {
        const int iter = 1000000;
        int i = 0;
        int count = 0;
        Stopwatch stopWatch = new();
        TimeSpan ts = new TimeSpan();
        decimal sum = 0;
        bool flag = false;
       while (count <= 4)
        {
            count++;
            stopWatch.Start();

            for(i=0; i<=iter; i++)
            {
                _a += _b;
            }
            
            stopWatch.Stop();
            ts = stopWatch.Elapsed;
            sum += stopWatch.ElapsedMilliseconds+ts.Minutes+ts.Seconds;
            
        }
        
        sum /= 4;
        return sum;




    }
}

public static class MainFunc
{
   static void Main(string[] args)
    {

        var result=Fast.calcFast(1, 1);

        Console.WriteLine("Average time (ms) = "+result );
    }
}
