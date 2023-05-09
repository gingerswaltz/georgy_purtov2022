using System;

public class Stack<T>
{
    private T[] items;
    private int top;

    public Stack(int size = 10)
    {
        items = new T[size];
        top = -1;
    }

    public void Push(T item)
    {
        if (top == items.Length - 1)
        {
            throw new Exception("Stack overflow");
        }

        top++;
        items[top] = item;
    }

    public T Pop()
    {
        if (top == -1)
        {
            throw new Exception("Stack underflow");
        }

        T item = items[top];
        top--;
        return item;
    }

    public T Peek()
    {
        if (top == -1)
        {
            throw new Exception("Stack is empty");
        }

        return items[top];
    }

    public bool IsEmpty()
    {
        return (top == -1);
    }

    public bool IsFull()
    {
        return (top == items.Length - 1);
    }
}

class Program
{
    static void Main(string[] args)
    {
        Console.Write("Введите строку: ");
        string str = Console.ReadLine();

        Stack<char> stack = new Stack<char>(str.Length);

        foreach (char c in str) // Положим все символы строки в стэк
        {
            stack.Push(c);
        }

        string reversedStr = "";

        while (!stack.IsEmpty()) // Извлекаем символы из стэка и создаем обратную строку
        {
            reversedStr += stack.Pop();
        }

        if (str == reversedStr) // Сравниваем исходную строку со строкой в обратном порядке
        {
            Console.WriteLine("Эта строка является палиндромом!");
        }
        else
        {
            Console.WriteLine("Эта строка не является палиндромом.");
        }
    }
}
