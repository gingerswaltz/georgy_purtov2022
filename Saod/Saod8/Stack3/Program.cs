using System;

class DecimalToBaseConverter
{
    static void Main(string[] args)
    {
        int number, baseNumber;
        do
        {
            Console.Write("Введите целое положительное число: ");
        } while (!int.TryParse(Console.ReadLine(), out number) || number < 0);

        do
        {
            Console.Write("Введите основание системы счисления (от 2 до 9): ");
        } while (!int.TryParse(Console.ReadLine(), out baseNumber) || baseNumber < 2 || baseNumber > 9);

        Stack<int> stack = new Stack<int>(); // Создаем стек для хранения цифр нового числа

        while (number > 0)
        {
            int remainder = number % baseNumber; // Вычисляем остаток от деления на новую систему счисления
            stack.Push(remainder); // Добавляем остаток в стек
            number /= baseNumber; // Делим число на новую систему счисления
        }

        Console.Write("Результат преобразования: ");
        while (!stack.IsEmpty())
        {
            int digit = stack.Pop(); // Извлекаем цифру из стека
            Console.Write(digit); // Выводим цифру на экран
        }

        Console.WriteLine(); // Переходим на новую строку
    }
}
