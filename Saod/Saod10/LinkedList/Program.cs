using System;
using System.Runtime.InteropServices;

public class LinkedList<T>
{
    private Node<T> front, rear; //  указатели на начало и конец списка
    private Node<T> prevPtr, currPtr; //  указатели, используемые для извлечения, вставки и удаления данных.
    private int size; //  число элементов в списке.
    private int position; // текущее положение в списке, используется методом Reset.

    private class Node<T> // представляет узел списка и имеет два поля
    {
        public T Data; // данные
        public Node<T> Next; // указатель на следующий узел в списке.
        public Node(T data)
        {
            Data = data; // присвоим данные узлу
            Next = null; // и ссылки на следующий нет - узел первый в списке
        }
    }

    public LinkedList() // конструктор по умолчанию, инициализирует переменные-члены значениями по умолчанию (null и 0).
    {
        front = rear = prevPtr = currPtr = null;
        size = position = 0;
    }

    public LinkedList(LinkedList<T> L) // конструктор копирования, инициализирует переменные-члены значениями по умолчанию (null и 0)
    {
        front = rear = prevPtr = currPtr = null;
        size = position = 0;
        CopyList(L);
    }

    ~LinkedList() // деструктор
    {
        ClearList(); // для удаления всех элементов списка и освобождения памяти.
    }
    public void ClearList()
    {
        Node<T> curr = front; // объявление указателя на первый элемент списка
        while (curr != null) // пока указатель не указывает на null
        {
            Node<T> temp = curr; // создание временного указателя на текущий элемент списка
            curr = curr.Next; // переход к следующему элементу списка
            FreeNode(temp); // удаление временного указателя
        }
        front = null; // обнуление указателя на первый элемент
        rear = null; // обнуление указателя на последний элемент
        currPtr = null; // обнуление указателя на текущий элемент
        prevPtr = null; // обнуление указателя на предыдущий элемент
        size = 0; // обнуление размера списка
        position = -1; // обнуление позиции текущего элемента
    }

    public void Assign(LinkedList<T> L)
    {
        if (this != L) // если текущий объект не является тем же самым объектом, что и L
        {
            ClearList(); // очистить текущий список
            CopyList(L); // скопировать содержимое списка L в текущий список
        }
    }

    public int ListSize()
    {
        return size; // возвращает размер списка
    }

    public bool ListEmpty()
    {
        return size == 0; // возвращает true, если размер списка равен 0
    }

    private void FreeNode(Node<T> p)
    {
        if (p != null) // если указатель p не указывает на null
        {
            FreeNode(p.Next); // вызов этой же функции для следующего элемента списка
            p = null; // удаляем текущий элемент списка
        }
    }


    private void CopyList(LinkedList<T> L)
    {
        if (L.front == null) // Если переданный список пуст, то обнуляем поля текущего списка.
        {
            front = null;
            rear = null;
            size = 0;
        }
        else
        {
            Node<T> currPtr = L.front; //  currPtr указывает на текущий узел в списке L
            Node<T> lastPtr = null; //  lastPtr указывает на последний скопированный узел в текущем списке.
            while (currPtr != null) //Пока не конец списка L.
            {
                Node<T> newNode = new Node<T>(currPtr.Data); //  новый узел, который содержит данные из текущего узла списка L.
                if (front == null) // Если текущий список пуст
                {
                    front = newNode; //  новый узел становится первым 
                }
                else
                {
                    lastPtr.Next = newNode; //  иначе новый узел добавляется в конец списка.
                }

                // Обновляем lastPtr и currPtr на новый узел и следующий узел списка L соответственно.
                lastPtr = newNode;
                currPtr = currPtr.Next;
            }
            rear = lastPtr; // Обновляем поле на последний скопированный узел
            size = L.size; // Обновляем поле  на размер списка L
        }
    }


    // Метод, который устанавливает текущую позицию в списке на позицию pos.
    public void Reset(int pos = 0)
    {
        if (pos >= 0 && pos <= size) // Проверяем, что позиция находится в пределах списка.

        {
            position = pos; // Обновляем поле position
            currPtr = front; // устанавливаем на первый узел списка
            prevPtr = null; //  обнуляем.
            for (int i = 0; i < position; i++) //Переходим на узел с позицией position,
                                               //чтобы prevPtr указывал на предыдущий узел.
            {
                prevPtr = currPtr;
                currPtr = currPtr.Next;
            }
        }
    }

    // метод для перехода к следующему элементу списка
    public void Next()
    {
        //   текущий указатель не равен null, т.е.  элемент, на который указывает currPtr не является последним в списке
        if (currPtr != null)
        {
            prevPtr = currPtr; //  сохранение текущего указателя
            currPtr = currPtr.Next; // перемещение текущего указателя на следующий элемент
            position++; // увеличение значения переменной position, чтобы отразить изменение текущей позиции в списке
        }
    }


    //  метод для проверки, достигнут ли конец списка
    public bool EndOfList()
    {
        return currPtr == null;
    }


    // метод для получения текущей позиции в списке
    public int CurrentPosition()
    {
        return position; // eсли метод Reset() не был вызван, то значение по умолчанию равно 0.
    }

    //  объявление метода для вставки элемента в начало списка.
    public void InsertFront(T item)
    {
        Node<T> newNode = new Node<T>(item); //  создание нового узла с переданным элементом.
        if (front == null) // проверка, что список пустой.
        {
            rear = newNode;//  если список пустой, то новый элемент будет последним в списке.
        }
        else
        {
            newNode.Next = front;// - новый элемент указывает на первый элемент списка.
        }
        front = newNode; // новый элемент становится первым в списке.
        size++; //  - увеличение размера списка.
    }

    //  объявление метода для вставки элемента в конец списка.
    public void InsertRear(T item)
    {
        Node<T> newNode = new Node<T>(item); // - создание нового узла с переданным элементом.
        if (front == null) // проверка, что список пустой.
        {
            front = newNode; // - если список пустой, то новый элемент будет первым в списке.
        }
        else
        {
            rear.Next = newNode; //  последний элемент списка указывает на новый элемент.
        }
        rear = newNode; // новый элемент становится последним в списке.
        size++;
    }

    // объявление метода для вставки элемента перед текущим элементом.
    public void InsertAt(T item)
    {
        if (currPtr == null) //  проверка, что текущий элемент не задан.
        {
            InsertRear(item); // если текущий элемент не задан, то элемент вставляется в конец списка.
        }
        else if (prevPtr == null) // проверка, что текущий элемент первый в списке.
        {
            InsertFront(item); // - если текущий элемент первый в списке, то элемент вставляется в начало списка.
        }
        else //  если текущий элемент не первый и не последний в списке.
        {
            Node<T> newNode = new Node<T>(item); //  создание нового узла с переданным элементом.
            newNode.Next = currPtr; // новый элемент указывает на текущий элемент.
            prevPtr.Next = newNode; //  предыдущий элемент указывает на новый элемент.
            size++;
        }
    }

    public T DeleteFront()
    {
        if (front == null)
        {
            throw new InvalidOperationException("List is empty.");
        }
        T data = front.Data;
        front = front.Next;
        if (front == null)
        {
            rear = null;
        }
        size--;
        return data;
    }

    // объявление метода InsertAfter, который принимает элемент типа T и добавляет его в список после текущей позиции.
    public void InsertAfter(T item)
    {
        if (currPtr == null) // проверка, что текущий указатель равен null, то есть список пустой.
        {
            InsertRear(item); // если список пустой, то вызываем метод InsertRear, чтобы вставить элемент в конец списка.
        }
        else
        {
            Node<T> newNode = new Node<T>(item); //  создание нового узла, содержащего переданный элемент.
            newNode.Next = currPtr.Next; //  устанавливаем следующий указатель нового узла на следующий элемент после текущего.
            currPtr.Next = newNode; // устанавливаем следующий указатель текущего узла на новый узел.
            if (currPtr == rear) // является ли текущий узел последним элементом в списке. 
            {
                rear = newNode; //  Если да, то устанавливаем указатель на последний элемент на новый узел.
            }
            size++;
        }
    }

    public T Data()
    {
        if (currPtr == null)
        {
            throw new InvalidOperationException("No current element.");
        }
        return currPtr.Data;
    }

    public void DeleteRear()
    {
        if (rear == null) // проверяется, что список не пустой
        {
            throw new InvalidOperationException("List is empty."); // exception 
        }
        if (front == rear) // является ли удаляемый элемент последним элементом в списке.
        {
            // Если front и rear указывают на один и тот же узел
            front = null; // обнуляются указатели на голову и хвост списка.
            rear = null;
        }
        else // Если же rear не указывает на последний узел в списке
        {
            Node<T> currPtr = front;
            //  то происходит перебор элементов с головы списка,
            //  пока текущий элемент не будет указывать на предпоследний узел
            while (currPtr.Next != rear)
            {
                currPtr = currPtr.Next;
            }
            currPtr.Next = null; // currPtr.Next устанавливается в null, тк последний элемент больше не является частью списка
            rear = currPtr; // обновляется указатель на rear так, чтобы он указывал на новый последний элемент.
        }
        size--;
    }

    public void DeleteAt(int pos)
    {
        // Проверка, что позиция находится в допустимом диапазоне
        if (pos < 0 || pos >= size)
        {
            throw new ArgumentOutOfRangeException(nameof(pos), "Position is out of range.");
        }

        // Если позиция равна 0, вызываем метод DeleteFront() для удаления первого элемента списка и возвращаемся
        if (pos == 0)
        {
            DeleteFront();
            return;
        }

        Node<T> currPtr = front;
        Node<T> prevPtr = null;

        // Перебираем элементы списка до позиции, которую нужно удалить
        for (int i = 0; i < pos; i++)
        {
            prevPtr = currPtr;
            currPtr = currPtr.Next;
        }

        // Устанавливаем указатель предыдущего элемента на следующий элемент, пропуская текущий элемент и удаляя его из списка
        prevPtr.Next = currPtr.Next;

        // Если после удаления текущего элемента следующий элемент стал равен null, обновляем указатель на последний элемент
        if (prevPtr.Next == null)
        {
            rear = prevPtr;
        }

        // Уменьшаем размер списка на единицу
        size--;
    }

    public void BubbleSort()
    {
        if (size <= 1) return; // если список пуст или состоит из одного элемента, то он уже отсортирован

        bool swapped = true;
        while (swapped)
        {
            swapped = false;
            Node<T> prev = null;
            Node<T> curr = front;
            Node<T> next = curr.Next;

            while (next != null)
            {
                if (Comparer<T>.Default.Compare(curr.Data, next.Data) > 0) // если текущий элемент больше следующего
                {
                    swapped = true;
                    if (prev != null) // если мы не находимся в начале списка
                    {
                        prev.Next = next; // перенаправляем ссылку предыдущего элемента на следующий элемент
                    }
                    else // если мы находимся в начале списка
                    {
                        front = next; // обновляем указатель на начало списка
                    }

                    curr.Next = next.Next; // перенаправляем ссылку текущего элемента на следующий элемент после следующего
                    next.Next = curr; // меняем ссылки у следующего элемента

                    Node<T> temp = curr; // меняем указатели на текущий и следующий узлы
                    curr = next;
                    next = temp;
                }

                prev = curr;
                curr = curr.Next;
                next = curr.Next;
            }
        }
    }

    public static void PrintList(LinkedList<T> L)
    {
        for (L.Reset(); !L.EndOfList(); L.Next())
        {

            Console.Write(L.Data()+" ");
        }
        Console.WriteLine();

    }

    public void RemoveDuplicates()
    {
        // Создаем словарь для хранения уникальных элементов списка
        Dictionary<T, bool> dict = new Dictionary<T, bool>();

        // Устанавливаем указатель на начало списка
        Node<T> current = front;

        // Устанавливаем указатель на предыдущий элемент списка
        Node<T> previous = null;

        // Перебираем все элементы списка
        while (current != null)
        {
            // Если элемент уже встречался ранее, удаляем его из списка
            if (dict.ContainsKey(current.Data))
            {
                previous.Next = current.Next;
                size--;
            }
            else
            {
                // Если элемент встречается впервые, добавляем его в словарь
                dict.Add(current.Data, true);
                previous = current;
            }

            // Переходим к следующему элементу списка
            current = current.Next;
        }
    }


}








class Program
    {
        static void Main(string[] args)
        {
            LinkedList<int> list = new LinkedList<int>();
            list.InsertRear(2);
            list.InsertRear(10);
            list.InsertRear(3);
            list.InsertRear(5);
            list.InsertRear(2);
            list.InsertRear(7);
            list.InsertRear(10);

        Console.WriteLine("Исходный список");
        LinkedList<int>.PrintList(list);
        list.BubbleSort();
        Console.WriteLine("Отсортированный список");
        LinkedList<int>.PrintList(list);
        list.RemoveDuplicates();
        Console.WriteLine("Конечный список");
        LinkedList<int>.PrintList(list);
    }

}

