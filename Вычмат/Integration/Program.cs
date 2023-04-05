
public static class Integration
{
    const double Pi = 3.14159265358979;


    public static double f(double x)
    {
        return Math.Sin(x)/x;
    }


    public static double SolutionTrapecia() 
    
    {
        dynamic n = 5000;
        dynamic a = 2 * Pi;
        dynamic b =3*Pi;
        dynamic h = (b - a) / n;
        dynamic s = 0;

        for (int k = 0; k < n-1; k++)
        {
            s = s + f(a + k * h);
        }
        s=(h/2)*(f(a) + f(b)+2*s);
        return s;
    }


    public static double SolutionSimpson()
    {
        dynamic n = 16;
        dynamic m = n/2;
        dynamic a = 2 * Pi;
        dynamic b = 3 * Pi;
        dynamic h = (b - a) / n;
        dynamic s1 = 0;

        for (int k = 1;k <= m;k++) 
        {
            s1= s1+ f(a + (2*k-1) * h);  
        }
        
        dynamic s2 = 0;
        
        for (int k = 1; k<=m-1; k++)
        {
            s2=s2+f(a+2*k*h); 
        }
        s2=(h/3)*(f(a)+f(b)+4*s1+2*s2);

        return s2;
    }



    public static void Main(string[] args)
    {
        Console.WriteLine("Метод Трапеций: "+SolutionTrapecia());
        Console.WriteLine("Метод Симпсона: " + SolutionSimpson());

    }
}
