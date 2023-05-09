using System;
using System.Collections.Generic;

class Program
{
    static void Main(string[] args)
    {
        int[] numbers = { 1704, 453, 75, 90, 802, 24, 2, 66 };
        int maxDigitCount = GetMaxDigitCount(numbers); // Определяем максимальное количество цифр в числах
        Console.WriteLine("Заданный массив: ");
        foreach (int number in numbers)
        {
            Console.Write(number + " ");
        }


        Console.WriteLine();
        for (int i = 0; i < maxDigitCount; i++)
        {
            Queue<int>[] digitQueues = new Queue<int>[10];

            for (int j = 0; j < 10; j++)
            {
                digitQueues[j] = new Queue<int>();
            }

            // Распределяем числа по корзинам согласно i-й цифре
            for (int j = 0; j < numbers.Length; j++)
            {
                int digit = GetDigit(numbers[j], i);
                digitQueues[digit].Enqueue(numbers[j]);
            }

            // Собираем числа из корзин в исходный массив
            int index = 0;
            for (int j = 0; j < 10; j++)
            {
                while (digitQueues[j].Count > 0)
                {
                    numbers[index++] = digitQueues[j].Dequeue();
                }
            }
        }

        Console.WriteLine("Отсортированный массив: ");
        foreach (int number in numbers)
        {
            Console.Write(number + " ");
        }
        Console.ReadKey();
    }

    // Функция для определения максимального количества цифр в числах
    static int GetMaxDigitCount(int[] numbers)
    {
        int maxDigitCount = 0;

        for (int i = 0; i < numbers.Length; i++)
        {
            int digitCount = GetDigitCount(numbers[i]);

            if (digitCount > maxDigitCount)
            {
                maxDigitCount = digitCount;
            }
        }

        return maxDigitCount;
    }

    // Функция для определения количества цифр в числе
    static int GetDigitCount(int number)
    {
        if (number == 0)
        {
            return 1;
        }

        int count = 0;

        while (number != 0)
        {
            number /= 10;
            count++;
        }

        return count;
    }

    // Функция для получения i-й цифры числа (i начинается с нуля справа)
    static int GetDigit(int number, int i)
    {
        return (number / (int)Math.Pow(10, i)) % 10;
    }
}
/*Инициализируем массив чисел и определяем максимальное количество цифр в числах в массиве с помощью функции GetMaxDigitCount.

Запускаем цикл по количеству цифр в числах. На каждом шаге создаем массив из десяти очередей digitQueues для разделения чисел по i-й цифре.

Проходим по массиву чисел и добавляем их в соответствующую очередь digitQueues в зависимости от i-й цифры числа с помощью функции GetDigit.

После того, как все числа разложены в очереди digitQueues, мы собираем их в исходном порядке, извлекая их из очередей по очереди и добавляя их обратно в исходный массив чисел.

Повторяем шаги 2-4 для каждой цифры в числах, начиная с последней.

Выводим отсортированный массив чисел в консоль.*/