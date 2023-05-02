using System;
using System.Linq;
using System.Text;
using System.Threading.Tasks;




class MainF
{
    enum DigitKind { ones, tens };

    static void Distribute(int[] L, Queue<int>[] digitQueue, int n, DigitKind kind)
    {
        int i;
        for (i = 0; i < n; i++)
        {
            if (kind == DigitKind.ones)
                digitQueue[L[i] % 10].Enqueue(L[i]);
            else
                digitQueue[L[i] / 10].Enqueue(L[i]);
        }
    }

    static void Collect(Queue<int>[] digitQueue, int[] L)
    {
        int i = 0, digit = 0;
        for (digit = 0; digit < 10; digit++)
        {
            while (digitQueue[digit].Count > 0)
            {
                L[i++] = digitQueue[digit].Dequeue();
            }
        }
    }

    static void PrintArray(int[] L, int n)
    {
        int i = 0;
        while (i < n)
        {
            Console.Write("{0,5}", L[i]);
            if (++i % 10 == 0)
                Console.WriteLine();
        }
        Console.WriteLine();
    }

    static void Main(string[] args)
    {
        Queue<int>[] digitQueue = new Queue<int>[10];
        for (int i = 0; i < 10; i++)
        {
            digitQueue[i] = new Queue<int>();
        }

        int[] L = new int[50];
        Random rnd = new Random();
        for (int i = 0; i < 50; i++)
        {
            L[i] = rnd.Next(100);
        }

        global::MainF.Distribute(L, digitQueue, 50, DigitKind.ones);
        global::MainF.Collect(digitQueue, L);
        global::MainF.PrintArray(L, 50);

        global::MainF.Distribute(L, digitQueue, 50, DigitKind.tens);
        global::MainF.Collect(digitQueue, L);
        global::MainF.PrintArray(L, 50);
    }
}




