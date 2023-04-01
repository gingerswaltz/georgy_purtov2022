using System;
using System.Collections.Generic;

class MainClass
{
    public static void Main(string[] args)
    {
        int n, m;
        string[] line;
        StreamWriter sw = new("out.txt");
     
        Console.WriteLine("Input N,M");
        // Считываем данные
        line = Console.ReadLine().Split(' ');
       

        n = int.Parse(line[0]);
        m = int.Parse(line[1]);
        sw.WriteLine($"{n}"+$" {m}");

        var result = TopSort(line, n,m, sw);
        // Проверяем, удалось ли провести топологическую сортировку
        if (result.Count != n)
        {
            Console.WriteLine("-1");
            sw.WriteLine("-1");
        }

        else
        {
            // Выводим результат
            Console.WriteLine("Result:");
            sw.WriteLine("Result:");
            foreach (int v in result)
            {
                Console.Write(v + " ");
                sw.Write(+v + " ");
            }

            Console.WriteLine();
        }
        sw.Close();
    }

    public static List<int> TopSort (string[] line, int n, int m, StreamWriter sw) 
    {
        // Инициализируем списки смежности и массив счетчиков входящих ребер
        List<int>[] adjList = new List<int>[n + 1];
        int[] inDegree = new int[n + 1];
        for (int i = 1; i <= n; i++)
        {
            adjList[i] = new List<int>();
            inDegree[i] = 0;
        }
        Console.WriteLine("Input digits: ");
        // Считываем ограничения и строим списки смежности
        for (int i = 0; i < m; i++)
        {
            line = Console.ReadLine().Split(' ');
            int u = int.Parse(line[0]);
            int v = int.Parse(line[1]);
            sw.WriteLine($"{u} {v}");
            adjList[u].Add(v);
            inDegree[v]++;
        }

        // Выполняем жадную топологическую сортировку
        List<int> result = new List<int>();
        for (int i = 1; i <= n; i++)
        {
            if (inDegree[i] == 0)
            {
                result.Add(i);
                foreach (int v in adjList[i])
                    inDegree[v]--;
            }
        }
        return result;
    }


}
