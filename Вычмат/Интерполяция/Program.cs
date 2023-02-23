public class Interpolation
{
    public static double Lagrange(double[] x_, double [] y_, double _x)
    {
        var n = x_.Length;
        double chislitel, znamenatel = 0;
        int k, i, j  = 0;
        double _lagrange = 0;
        for( k=0; k<n; k++)
        {
             chislitel = 1;
                for(i=0; i<n; i++)
            {
                if (i != k)
                    chislitel *= (_x - x_[i]);
                 znamenatel = 1;
            }
                for (j=0; j<n; j++)
            {
                if (j != k)
                {
                    znamenatel *= (x_[k] - x_[j]);
                }
            }
            _lagrange = _lagrange + y_[k] * (chislitel / znamenatel);

        }
        return _lagrange;
    }

    public static double Newton_Up(double[] x_, double[] y_, double[,] y1_, double _x)
    {
        int n = x_.Length;  
        double _newton = y_[0];
        double prod = 1;
        int k, i, j = 0;

        for (k=1; k<n; k++)
        {
            prod*=(_x - x_[k-1]);
            _newton += y1_[0, k] * prod;
        }
        return _newton;
    }

    public static double Newton_Down(double[] x_, double[] y_, double[,] y1_, double _x)
    {
        double _newton = y_[y_.Length-1];
        double prod = 1;
       

        for (int k = 1; k < y_.Length; k++)
        {
            prod *= _x - x_[y_.Length - k];
            _newton += y1_[y_.Length - k-1, k] * prod;
        }
        return _newton;
    }
   

}

public class MainFunc
{
    public static void Main(string[] args)
    {
        double[] x = { 1.2, -0.9, 0.7, 1.1, 1.7, 2.9 };
        double[] y = { 3.38688, 1.50579, 16.99677, 25.85121, 28.70127, 0.55419 };
        double x1 = -0.2;

        Console.WriteLine("Lagrange : ");

        var result = Interpolation.Lagrange(x, y, x1);
        Console.WriteLine(result+'\n');


        int l = 6;
        int h = 6;
        double[,] y1 = new double[l, h];
        double n = x.Length;
        int k = 0;
        for (int m = 1; m < n; m++)
        {
            // вычисляется по формуле
            for (k = 0; k < n-m; k++)
            {
                // где каждый элемент заданной функции Y
                if (m == 1)
                    // вычисляется отношением разности следующих
                    y1[k,m] = (y[k + 1] - y[k]) / (x[k + 1] - x[k]); // элементов с текущими и разности узлов
                else
                    // при этом вычисляется сначала разность
                    y1[k, m] = (y1[k + 1, m - 1] - y1[k, m - 1]) / (x[k + m] - x[k]); 
                // первого порядка в узлах xk и xk + 1, а лишь потом
            }
            // разделённая разность порядка m
        }




        Console.WriteLine("Newton Upper : ");
       
        result = Interpolation.Newton_Up(x, y, y1, x1);
        Console.WriteLine(result + '\n');


        Console.WriteLine("Newton down : ");

        result =Interpolation.Newton_Down(x, y, y1, x1);
        Console.WriteLine(result + '\n');


    }
}