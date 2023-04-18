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
            Console.Write(n +" ");
            Console.Write(xx[n] +" ");
            Console.Write(yy[n]+" ");
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
    

    public static void Adams(double x0, double y0, double h, double k)
    {
        double[] xx = new double[11] { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
        double[] yy = new double[11] { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
        xx[0] = x0;
        yy[0] = y0;
        // method m=1
        Console.ForegroundColor = ConsoleColor.Red;
        Console.WriteLine("\tyn A1");
        Console.ResetColor();
        for (int n=0; n<k; n++)
        {
            Console.Write(yy[n] + " ");
             if (n < 1)
            {
                xx[n + 1] = xx[n] + h;
                dynamic z1 = h * f(xx[n], yy[n]);
                dynamic z2 = h * f(xx[n] + h / 2, yy[n] + z1 / 2);
                dynamic z3 = h * f(xx[n] + h / 2, yy[n] + z2 / 2);
                dynamic z4 = h * f(xx[n] + h, yy[n] + z3); 
                yy[n + 1] = yy[n] + (z1 + 2 * z2 + 2 * z3 + z4) / 6;
            }else
               if (n < k)
            {
                xx[n + 1] = xx[n] + h;
                dynamic a = f(xx[n], yy[n]);
                dynamic b = f(xx[n - 1], yy[n - 1]);
                dynamic c = 3 * a - b;
                yy[n + 1] = yy[n] + (h / 2) * c;

            }
        }

        Console.WriteLine();
        Console.ForegroundColor = ConsoleColor.Red;
        Console.WriteLine("\tyn A2");
        Console.ResetColor();

        // method m=2
        for (int n=0; n<k; n++)
        {

            Console.Write(yy[n] + " ");
             if (n < 2)
            {
                xx[n + 1] = xx[n] + h;
                dynamic z1 = h * f(xx[n], yy[n]);
                dynamic z2 = h * f(xx[n] + h / 2, yy[n] + z1 / 2);
                dynamic z3 = h * f(xx[n] + h / 2, yy[n] + z2 / 2);
                dynamic z4 = h * f(xx[n] + h, yy[n] + z3);
                yy[n + 1] = yy[n] + (z1 + 2 * z2 + 2 * z3 + z4) / 6;

            } else
                if (n < k)
            {
                xx[n + 1] = xx[n] + h;
                dynamic a = f(xx[n], yy[n]);
                dynamic b = f(xx[n - 1], yy[n - 1]);
                dynamic c = f(xx[n - 2], yy[n - 2]);
                dynamic d = 23 * a - 16 * b + 5 * c;
                yy[n + 1] = yy[n] + (h / 12) * d;
            }
        }
        Console.WriteLine();
        // method m=3
        Console.ForegroundColor = ConsoleColor.Red;
        Console.WriteLine("\tyn A3");
        Console.ResetColor();
        for (int n=0; n<k; n++)
       {


            Console.Write(yy[n] + " ");
            if (n < 3)
            {
                xx[n + 1] = xx[n] + h;
               dynamic z1 = h * f(xx[n], yy[n]);
                dynamic z2 = h * f(xx[n] + h / 2, yy[n] + z1 / 2);
                dynamic z3 = h * f(xx[n] + h / 2, yy[n] + z2 / 2);
                dynamic z4 = h * f(xx[n] + h, yy[n] + z3);
                yy[n + 1] = yy[n] + (z1 + 2 * z2 + 2 * z3 + z4) / 6;
            } else if (n < k)
            {
                xx[n + 1] = xx[n] + h;
                dynamic a = f(xx[n], yy[n]);
                dynamic b = f(xx[n - 1], yy[n - 1]);
                dynamic c = f(xx[n - 2], yy[n - 2]);
                dynamic d = f(xx[n - 3], yy[n - 3]);
                dynamic e = 55 * a - 59 * b + 37 * c - 9 * d;
                yy[n + 1] = yy[n] + (h / 24) * e;

            }

        }

    }
    
    static void Main(string[] args) 
    {
        Console.ForegroundColor = ConsoleColor.Green;
        Console.WriteLine("Euler: ");
        Console.ResetColor();
        Euler(0, 1, 0.1, 10);
        Console.WriteLine();

        Console.ForegroundColor = ConsoleColor.Green;
        Console.WriteLine("\nEulerMod: ");
        Console.ResetColor();
        EulerMod(0, 1, 0.1, 10);
        Console.WriteLine();


        Console.ForegroundColor = ConsoleColor.Green;
        Console.WriteLine("\nRunge Kutt: ");
        Console.ResetColor();
        RungeKutt(0, 1, 0.1, 10);
        Console.WriteLine();



        Console.ForegroundColor = ConsoleColor.Green;
        Console.WriteLine("\nAdams: ");
        Console.ResetColor();
        Adams(0, 1, 0.1, 10);
    }

}
