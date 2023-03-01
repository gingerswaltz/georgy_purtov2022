class Interpolation
{
    static void SplineCube(double[] _x, double[]_y, double [] _z)
    {
        double[] a = new double[_x.Length];
        double[] b = new double[_x.Length];
        double[] c=new double[_x.Length];
        double[] z= new double[_x.Length];
        double d = 0;
        double e = 0;
        
        for (int k = 1; k < _x.Length; k++)
        {
            d = _x[k] - _x[k - 1];
            e =  _y[k]- _y[k - 1];
            a[k] = e / (d * d) - z[k - 1] / d;
            b[k] = 2 * e/d-z[k - 1];
            c[k] = _y[k];
            z[k] = b[k];
        }

        Console.WriteLine("a[k]\n");
        for (int i=1; i<a.Length; i++)
        {
            Console.Write(a[i]+" \t");
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


    public static void Main(string[] args)
    {
        double[] x = new double[7] { -5, -3, -2, 0, 4, 5, 8 };
        double[] y = new double[7] {7,6,5,10,-10,-7,6 };
        double[] z = new double[7] { -1, 0, 0, 0, 0, 0, 0};

        SplineCube(x, y, z);

    }
}
