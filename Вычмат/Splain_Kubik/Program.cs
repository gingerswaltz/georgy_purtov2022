class Interpolation
{
    static void Cube(double[] _x, double[] _y, double[] _z)
    {
        double[] a = new double[_x.Length];
        double[] b = new double[_x.Length];
        double[] c = new double[_x.Length];
        double[] z = new double[_x.Length];
        double d = 0;
        double e = 0;

        for (int k = 1; k < _x.Length; k++)
        {
            d = _x[k] - _x[k - 1];
            e = _y[k] - _y[k - 1];
            a[k] = (e / (d * d)) - (z[k - 1] / d);
            b[k] = (2 * e / d) - z[k - 1];
            c[k] = _y[k];
            z[k] = b[k];
            


        }

        Console.WriteLine("a[k]\n");
        for (int i = 1; i < a.Length; i++)
        {
            Console.Write(a[i] + " \t");
        }
        Console.WriteLine('\n');
        Console.WriteLine("b[k]\n");
        for (int i = 1; i < b.Length; i++)
        {
            Console.Write(b[i] + " \t");
        }


        Console.WriteLine();
        Console.WriteLine("c[k]\n");
        for (int i = 1; i < c.Length; i++)
        {
            Console.Write(c[i] + " \t");
        }


        Console.WriteLine('\n');
        Console.WriteLine("z[k]\n");
        for (int i = 1; i < z.Length; i++)
        {
            Console.Write(z[i] + " \t");
        }
        Console.WriteLine('\n');
    }




//    For k = 1 To n
//dx = x(k) - x(k - 1)
//dy = y(k) - y(k - 1)
//a(k) = dy / (dxô3) - z(k - 1) / (dxô2) - w(k - 1) / (2 * dx) b(k) = 3 * dy / (dxô2) - 3 * z(k - 1) / dx - w(k - 1)
//c(k) = 3 * dy / dx - 2 * z(k - 1) - w(k - 1) * dx / 2
//d(k) = y(k)
//z(k) = c(k)
//w(k) = 2 * b(k)

    static void Splain(double[] _x, double[] _y, double[] _z, double[] _w)
    {
        double dx = 0;
        double dy = 0;
        double[] a = new double[_x.Length];
        double[] b = new double[_x.Length];
        double[] c = new double[_x.Length];
        double[] z = new double[_x.Length];
        double[] d = new double[_x.Length];


        for (int k=1; k<_x.Length; k++)
        {
            dx = _x[k] - _x[k - 1];
            dy = _y[k] - _y[k - 1];
            a[k] = (dy / Math.Pow(dx, 3)) - (z[k - 1] / (dx * dx)) - (_w[k - 1] / (2 * dx));
            b[k] = ((3 * dy) / (dx * dx)) - ((3 * z[k - 1]) / dx) - _w[k - 1];
            c[k]= 3 * dy / dx - 2 * z[k - 1] - _w[k - 1]*dx/2;
            d[k] = _y[k];
            z[k] = c[k];
            _w[k] = 2 * b[k];
        }
        Console.WriteLine("\t\na[k]");
        for (int i = 1; i < a.Length; i++)
        {
            Console.Write(a[i] + " \t\n");
        }
        
        Console.WriteLine("\t\nb[k]");
        for (int i = 1; i < b.Length; i++)
        {
            Console.Write(b[i] + " \t\n");
        }


       
        Console.WriteLine("\t\nc[k]");
        for (int i = 1; i < c.Length; i++)
        {
            Console.Write(c[i] + " \t\n");
        }


        Console.WriteLine("\t\nz[k]");
        for (int i = 1; i < z.Length; i++)
        {
            Console.Write(z[i] + " \t\n");
        }
        

        Console.WriteLine("\t\nd[k]");
        for (int i = 1; i < d.Length; i++)
        {
            Console.Write(d[i] + " \t\n");
        }

        Console.WriteLine("\t\nw[k]");
        for (int i = 1; i < _w.Length; i++)
        {
            Console.Write(_w[i] + " \t\n");
        }
    }



    public static void Main(string[] args)
    {
        double[] x = new double[7] { -5, -3, -2, 0, 4, 5, 8 };
        double[] y = new double[7] { 7, 6, 5, 10, -10, -7, 6 };
        double[] z = new double[7] { -1, 0, 0, 0, 0, 0, 0 };
        double[] w = new double[7] { 1, 0, 0, 0, 0, 0, 0 };
        Cube(x, y, z);
        Console.WriteLine("----------------------Spline 2----------------------");

        Splain(x, y, z, w);
    }
}


    

