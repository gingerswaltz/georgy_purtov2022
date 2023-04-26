

using System.Diagnostics;

public static class Search
{
    public static int BinarySearch<T>(T[] array, T key) where T : IComparable<T> 
        // название метода, где <T> - это обобщенный тип, который позволяет использовать метод с различными типами данных.
        //where T : IComparable<T> - ограничение типа, которое гарантирует, что тип T будет реализовывать интерфейс IComparable<T>, который позволяет сравнивать объекты типа T.

    {
        int left = 0;
        int right = array.Length - 1;
        while (left <= right) //  цикл продолжается до тех пор, пока левая граница не станет больше правой.
        {
            int middle = (left + right) / 2; // - определяет средний индекс в массиве, округленный в меньшую сторону, путем сложения левой и правой границ и деления на 2.
            int comparison = key.CompareTo(array[middle]); // сравнивает ключ с элементом массива по среднему индексу и сохраняет результат в переменную comparison.
            if (comparison == 0) // - если результат сравнения равен 0, значит, ключ найден в массиве, и метод возвращает индекс этого элемента в массиве.
            {
                return middle;
            }
            else if (comparison < 0) //  - если результат сравнения меньше 0, значит, искомый элемент находится в левой половине массива, и правая граница поиска становится равной среднему индексу минус 1.
            {
                right = middle - 1;
            }
            else //  если результат сравнения больше 0, значит, искомый элемент находится в правой половине массива, и левая граница поиска становится равной среднему индекс
            {
                left = middle + 1;
            }
        }
        return -1;
    }

}

public static class MainF
{
    public static void Main(string[] args)
    {
        Random rand = new Random();
        int[] intArray = new int[500];
        double[] doubleArray = new double[500];
        for (int i = 0; i < 500; i++)
        {
            intArray[i] = rand.Next(1000);
            doubleArray[i] = rand.NextDouble() * 1000;
        }
               
        Stopwatch stopwatch = new Stopwatch(); // слздаем таймер
        stopwatch.Start(); // запускаем таймер
        int intIndex = Search.BinarySearch(intArray, 42); // выполняем бинарный поиск по интовому массиву
        stopwatch.Stop(); // остановили
        TimeSpan intTime = stopwatch.Elapsed; // сняли время
        stopwatch.Reset(); // обнулили и по новой для double массива
        stopwatch.Start();
        int doubleIndex = Search.BinarySearch(doubleArray, 42.0);
        stopwatch.Stop();
        TimeSpan doubleTime = stopwatch.Elapsed;
        File.WriteAllText("results.txt", $"Integer search time: {intTime}\nDouble search time: {doubleTime}"); // вывод в текстовый файл

    }
}
