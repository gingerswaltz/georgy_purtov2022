public class LinkedList<T>
{
    // Класс узла списка
    public class Node
    {
        public T Data;
        public Node Next;

        public Node(T data)
        {
            Data = data;
            Next = null;
        }
    }

    public Node head; // Голова списка
    private Node tail; // Хвост списка
    private int count; // Количество элементов в списке
    // Конструктор для создания пустого списка
    public LinkedList()
    {
        head = null;
        tail = null;
        count = 0;
    }
    public Node GetHead()
    {
        return head;
    }

    // Методы проверки состояния списка
    public int ListSize()
    {
        return count;
    }

    public bool ListEmpty()
    {
        return count == 0;
    }

    // Метод для очистки списка
    public void ClearList()
    {
        head = null;
        tail = null;
        count = 0;
    }

    // Метод для вставки нового элемента в начало списка
    public void InsertFront(T data)
    {
        Node newNode = new Node(data);

        if (head == null)
        {
            head = newNode;
            tail = newNode;
        }
        else
        {
            newNode.Next = head;
            head = newNode;
        }

        count++;
    }
    

    // Метод для вставки нового элемента в конец списка
    public void InsertRear(T data)
    {
        Node newNode = new Node(data);

        if (head == null)
        {
            head = newNode;
            tail = newNode;
        }
        else
        {
            tail.Next = newNode;
            tail = newNode;
        }

        count++;
    }

    // Метод для вставки нового элемента в заданную позицию списка
    public void InsertAt(T data, int index)
    {
        if (index < 0 || index > count)
        {
            throw new ArgumentOutOfRangeException(nameof(index));
        }

        if (index == 0)
        {
            InsertFront(data);
        }
        else if (index == count)
        {
            InsertRear(data);
        }
        else
        {
            Node currentNode = head;
            for (int i = 0; i < index - 1; i++)
            {
                currentNode = currentNode.Next;
            }

            Node newNode = new Node(data);
            newNode.Next = currentNode.Next;
            currentNode.Next = newNode;

            count++;
        }
    }

    // Метод для вставки нового элемента после заданного элемента списка
    public void InsertAfter(T existingData, T newData)
    {
        Node currentNode = head;
        while (currentNode != null && !currentNode.Data.Equals(existingData))
        {
            currentNode = currentNode.Next;
        }

        if (currentNode == null)
        {
            throw new ArgumentException("The specified existingData is not found in the list.");
        }

        Node newNode = new Node(newData);
        newNode.Next = currentNode.Next;
        currentNode.Next = newNode;

        if (tail == currentNode)
        {
            tail = newNode;
        }

        count++;
    }

    // Метод для удаления первого элемента списка
    public void DeleteFront()
    {
        if (head == null)
        {
            throw new InvalidOperationException("The list is empty.");
        }

        if (head == tail)
        {
            head = null;
            tail = null;
        }
        else
        {
            head = head.Next;
        }

        count--;
    }

    // Метод для удаления элемента из заданной позиции списка
    public void DeleteAt(int index)
    {
        if (index < 0 || index >= count)
        {
            throw new ArgumentOutOfRangeException(nameof(index));
        }
        if (index == 0)
        {
            DeleteFront();
        }
        else
        {
            Node currentNode = head;
            for (int i = 0; i < index - 1; i++)
            {
                currentNode = currentNode.Next;
            }

            if (tail == currentNode.Next)
            {
                tail = currentNode;
            }

            currentNode.Next = currentNode.Next.Next;

            count--;
        }



    }

    // Метод сортировки списка пузырьком
    public void BubbleSort()
    {
        // Если список пустой или содержит только один элемент, возвращаемся
        if (head == null || head.Next == null)
        {
            return;
        }
        // Флаг swapped указывает, была ли выполнена перестановка элементов
        bool swapped;

        // Выполняем сортировку пузырьком, пока происходят перестановки
        do
        {
            // Устанавливаем флаг swapped в false перед каждой итерацией
            swapped = false;

            // Инициализируем переменные для трех узлов: предыдущего, текущего и следующего
            Node prevNode = null;
            Node currentNode = head;
            Node nextNode = head.Next;

            // Перебираем все пары соседних узлов
            while (nextNode != null)
            {
                // Если текущий узел больше следующего, меняем их местами
                if (Comparer<T>.Default.Compare(currentNode.Data, nextNode.Data) > 0)
                {
                    // Если текущий узел не является головой списка, то меняем указатель предыдущего узла на следующий
                    if (prevNode != null)
                    {
                        prevNode.Next = nextNode;
                    }
                    // Если текущий узел - голова списка, то меняем указатель на голову списка на следующий узел
                    else
                    {
                        head = nextNode;
                    }

                    // Меняем указатель текущего узла на следующий после nextNode
                    currentNode.Next = nextNode.Next;

                    // Меняем указатель следующего узла на текущий узел
                    nextNode.Next = currentNode;

                    // Если следующий узел является хвостом списка, то меняем указатель хвоста на текущий узел
                    if (tail == nextNode)
                    {
                        tail = currentNode;
                    }

                    // Устанавливаем флаг swapped в true, чтобы указать, что выполнена перестановка
                    swapped = true;

                    // Меняем местами currentNode и nextNode для продолжения итерации
                    Node temp = nextNode;
                    nextNode = currentNode;
                    currentNode = temp;
                }

                // Переходим к следующей паре узлов
                prevNode = currentNode;
                currentNode = currentNode.Next;
                nextNode = currentNode.Next;
            }

        } while (swapped); // Повторяем итерации до тех пор, пока флаг swapped не станет false

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

        list.BubbleSort();

        Node<int> currentNode = list.head;
        Node<int> prevNode = null;

        while (currentNode != null)
        {
            // Проверяем, равен ли текущий узел предыдущему
            if (prevNode != null && prevNode.Data.Equals(currentNode.Data))
            {
                // Если равен, удаляем текущий узел
                prevNode.Next = currentNode.Next;
                currentNode = currentNode.Next;
                list.count--;
            }
            else
            {
                // Если не равен, продвигаемся к следующему узлу
                prevNode = currentNode;
                currentNode = currentNode.Next;
            }
        }

    }
    }
