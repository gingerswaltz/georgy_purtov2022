using System;
using System.Collections.Generic;

class MainClass
{
    public static void Main(string[] args)
    {
        int n, m;
        string[] line;

        // Считываем данные
        line = Console.ReadLine().Split(' ');
        n = int.Parse(line[0]);
        m = int.Parse(line[1]);

        // Инициализируем списки смежности и массив счетчиков входящих ребер
        List<int>[] adjList = new List<int>[n + 1];
        int[] inDegree = new int[n + 1];
        for (int i = 1; i <= n; i++)
        {
            adjList[i] = new List<int>();
            inDegree[i] = 0;
        }

        // Считываем ограничения и строим списки смежности
        for (int i = 0; i < m; i++)
        {
            line = Console.ReadLine().Split(' ');
            int u = int.Parse(line[0]);
            int v = int.Parse(line[1]);
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

        // Проверяем, удалось ли провести топологическую сортировку
        if (result.Count != n)
            Console.WriteLine("-1");
        else
        {
            // Выводим результат
            foreach (int v in result)
                Console.Write(v + " ");
            Console.WriteLine();
        }
    }
}
