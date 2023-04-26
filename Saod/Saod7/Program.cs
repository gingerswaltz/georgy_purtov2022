using System;
using System.Diagnostics;
using System.IO;
using System;

public static class Sort
{
    public static void BubbleSort<T>(T[] arr) where T : IComparable<T>
    {
        for (int i = 0; i < arr.Length - 1; i++)
        {
            for (int j = 0; j < arr.Length - i - 1; j++)
            {
                if (arr[j].CompareTo(arr[j + 1]) > 0)
                {
                    Swap(arr, j, j + 1);
                }
            }
        }
    }

    public static void SelectionSort<T>(T[] arr) where T : IComparable<T>
    {
        int minIndex;
        for (int i = 0; i < arr.Length - 1; i++)
        {
            minIndex = i;
            for (int j = i + 1; j < arr.Length; j++)
            {
                if (arr[j].CompareTo(arr[minIndex]) < 0)
                {
                    minIndex = j;
                }
            }
            if (minIndex != i)
            {
                Swap(arr, i, minIndex);
            }
        }
    }

    public static void InsertionSort<T>(T[] arr) where T : IComparable<T>
    {
        T key;
        int j;
        for (int i = 1; i < arr.Length; i++)
        {
            key = arr[i];
            j = i - 1;
            while (j >= 0 && arr[j].CompareTo(key) > 0)
            {
                arr[j + 1] = arr[j];
                j--;
            }
            arr[j + 1] = key;
        }
    }

    private static void Swap<T>(T[] arr, int i, int j)
    {
        T temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }


    public static void QuickSort<T>(T[] array, int left, int right) where T : IComparable<T>
    {
        if (left >= right)
        {
            return;
        }

        T pivot = array[(left + right) / 2];
        int partitionIndex = Partition(array, left, right, pivot);

        QuickSort(array, left, partitionIndex - 1);
        QuickSort(array, partitionIndex, right);
    }

    private static int Partition<T>(T[] array, int left, int right, T pivot) where T : IComparable<T>
    {
        while (left <= right)
        {
            while (array[left].CompareTo(pivot) < 0)
            {
                left++;
            }

            while (array[right].CompareTo(pivot) > 0)
            {
                right--;
            }

            if (left <= right)
            {
                Swap(array, left, right);
                left++;
                right--;
            }
        }

        return left;
    }

    public static void ShellSort<T>(T[] array) where T : IComparable<T>
    {
        int gap = array.Length / 2;

        while (gap > 0)
        {
            for (int i = gap; i < array.Length; i++)
            {
                T temp = array[i];
                int j = i;

                while (j >= gap && array[j - gap].CompareTo(temp) > 0)
                {
                    array[j] = array[j - gap];
                    j -= gap;
                }

                array[j] = temp;
            }

            gap = gap / 2;
        }
    }



}


class Program
{
    static void Main(string[] args)
    {
        int[] sizes = { 10000, 20000, 30000, 40000 };
        string filePath = "sort_results.txt";

        using (StreamWriter writer = new StreamWriter(filePath))
        {
            foreach (int size in sizes)
            {
                int[] array = GenerateRandomArray(size);

                Stopwatch stopwatch = new Stopwatch();

                // Bubble sort
                stopwatch.Start();
                Sort.BubbleSort(array);
                stopwatch.Stop();
                writer.WriteLine($"Bubble sort time ({size}): {stopwatch.ElapsedMilliseconds} ms");

                // Selection sort
                array = GenerateRandomArray(size);
                stopwatch.Restart();
                Sort.SelectionSort(array);
                stopwatch.Stop();
                writer.WriteLine($"Selection sort time ({size}): {stopwatch.ElapsedMilliseconds} ms");

                // Insertion sort
                array = GenerateRandomArray(size);
                stopwatch.Restart();
                Sort.InsertionSort(array);
                stopwatch.Stop();
                writer.WriteLine($"Insertion sort time ({size}): {stopwatch.ElapsedMilliseconds} ms");

                // Quick sort
                array = GenerateRandomArray(size);
                stopwatch.Restart();
                Sort.QuickSort(array, 0, size - 1);
                stopwatch.Stop();
                writer.WriteLine($"Quick sort time ({size}): {stopwatch.ElapsedMilliseconds} ms");

                // Shell sort
                array = GenerateRandomArray(size);
                stopwatch.Restart();
                Sort.ShellSort(array);
                stopwatch.Stop();
                writer.WriteLine($"Shell sort time ({size}): {stopwatch.ElapsedMilliseconds} ms");
            }
        }

        Console.WriteLine($"Sorting results written to file: {filePath}");
        Console.ReadLine();
    }

    static int[] GenerateRandomArray(int size)
    {
        Random random = new Random();
        int[] array = new int[size];
        for (int i = 0; i < size; i++)
        {
            array[i] = random.Next();
        }
        return array;
    }
}