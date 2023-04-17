using System.Security.Cryptography.X509Certificates;

public class Koshi
{
    public static double f(double x, double y)
    {
        return Math.Sin(x) * Math.Cos(y);
    }

    
    public static void Euler(double x0, double y0, double h, double k)
    {
        double[] xx= new double[11] {0,1,2,3,4,5,6,7,8,9,10 };
        double[] yy = new double[11] { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
        for (int n = 0; n < k; n++)
        {
            Console.Write("\n" + n +" ");
            Console.Write("\n"+ xx[n] +" ");
            Console.Write("\n" + yy[n]+" ");
            if (n<k)
            {
                xx[n + 1] = xx[n] + h;
                yy[n + 1] = yy[n] + h*f(xx[n], yy[n]);
            }
        }
    }

    public static void EulerMod(double x0, double y0, double h, double k) 
    {
        double[] xx = new double[11] { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
        double[] yy = new double[11] { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
        xx[0] = x0;
        yy[0] = y0;
        for (int n =0; n < k; n++)
        {
            Console.Write(yy[n] +" ");
            if (n< k)
            {
                xx[n+1] = xx[n] + h;
                yy[n+1] = yy[n] + h * f(xx[n]+h/2, yy[n] + (h / 2) * f(xx[n], yy[n]));
            }
        }


    }

    public static void RungeKutt(double x0, double y0, double h, double k)
    {
        double[] xx = new double[11] { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
        double[] yy = new double[11] { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
        xx[0] = x0;
        yy[0] = y0;
        for (int n = 0; n < k; n++)
        {
            Console.Write(yy[n] + " ");
              if (n< k)
            {
                xx[n + 1] = xx[n] + h;
                dynamic z1 = h * f(xx[n], yy[n]);
                dynamic z2 = h * f(xx[n] + h / 2, yy[n] + z1 / 2);
                dynamic z3 = h * f(xx[n] + h / 2, yy[n] + z2 / 2);
                dynamic z4 = h * f(xx[n] + h, yy[n] + z3);
                yy[n + 1] = yy[n] + (z1 + 2 * z2 + 2 * z3 + z4) / 6;

            }
        }
    }
    

    
    
    static void Main(string[] args) 
    {
        Console.WriteLine("Euler: ");
        Euler(0, 1, 0.1, 10);
        Console.WriteLine("\nEulerMod: ");
        EulerMod(0, 1, 0.1, 10);
        Console.WriteLine("\nRunge Kutt: ");
        RungeKutt(0, 1, 0.1, 10);
    }

}
