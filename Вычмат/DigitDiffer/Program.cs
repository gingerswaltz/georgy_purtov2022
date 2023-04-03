using System.Globalization;

public static class Differentiation
{
    const double Pi = 3.141592654;
    public static double f(double x)
    {
        return Math.Pow(Math.Cos(x),3);
    }
    
    
    public static (double, double) Solution1(double h1, double h2)
    {
        dynamic m1 = 21;
        dynamic m2 = 183;
        dynamic x0 = Pi / 4;
        dynamic eps = 0.001;

       dynamic diff1=(f(x0+h1)-f(x0-h1)) / (2*h1);

       dynamic diff2=(f(x0-2*h2)-8*f(x0-h2)+8*f(x0+h2)-f(x0+2*h2))/(12*h2);
        
        return (diff1, diff2);
    }

    public static void Solution2(double h)
    {
        const int n = 7;
        double []x=new double[7];
        double[,]y=new double[7,7];

        for (int i = 0; i < 7; i++)
        {
            x[i] = 4+h*i;
            y[i, 0] = Math.Pow((1 + x[i] * x[i]), 0.5);
            
        }

        for (int j = 1; j < 7; j++)
        {
            for (int i = 0; i < n - j; i++)
            {
                y[i, j] = (y[i + 1, j - 1] - y[i, j - 1]);
                string s1 = string.Format("{0:F6}", y[i, j]);
                Console.WriteLine($"    y'x0={s1}"+'\t'+" ");
            }
            
        }
        Console.Write("\n");


        double s = 0;
        double d = -1;
        double Delta = 0;
        for (int j = 1; j < n - 1; j++)
        {
            d = (-1) * d;
            s = s + d * y[0, j] / (j * h);
            Delta = Math.Abs(y[0, j + 1]) / ((j + 1) * h);
            Console.Write($"    Delta {j}:" + Delta+'\t'+" ");
        }
    }

    public static void Main(string[] args)
    {
        Console.WriteLine("Постановка 1");
        Console.WriteLine("Input h1: ");
        double.TryParse(Console.ReadLine(), out var h1);
        Console.WriteLine("Input h2: ");
        double.TryParse(Console.ReadLine(), out var h2);
        Console.WriteLine("Производная по 1 формуле: "+Solution1(h1, h2).Item1+"\n"+
            "Производная по 2 формуле: " + Solution1(h1, h2).Item2+'\n');

        Console.WriteLine("Постановка 2");
        Solution2(0.1);

    }
}