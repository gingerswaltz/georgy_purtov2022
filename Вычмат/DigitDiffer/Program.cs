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



    public static void Main(string[] args)
    {
        Console.WriteLine("Постановка 1");
        Console.WriteLine("Input h1: ");
        double.TryParse(Console.ReadLine(), out var h1);
        Console.WriteLine("Input h2: ");
        double.TryParse(Console.ReadLine(), out var h2);
        Console.WriteLine("Производная по 1 формуле: "+Solution1(h1, h2).Item1+"\n"+
            "Производная по 2 формуле: " + Solution1(h1, h2).Item2);

        Console.WriteLine("Постановка 2");

    }
}