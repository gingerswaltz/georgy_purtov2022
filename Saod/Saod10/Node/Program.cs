public class Node<T>
{
    // Значение узла
    public T Value { get; set; }

    // Ссылка на следующий узел
    public Node<T> Next { get; set; }

    // Конструктор для создания узла с указанным значением и ссылкой на следующий узел
    public Node(T value, Node<T> next)
    {
        Value = value;
        Next = next;
    }

    // Метод для вставки нового узла после текущего узла
    public void InsertAfter(T value)
    {
        // Создаем новый узел со значением value и ссылкой на следующий узел текущего узла
        Node<T> newNode = new Node<T>(value, Next);

        // Обновляем ссылку на следующий узел текущего узла, чтобы она указывала на новый узел
        Next = newNode;
    }

    // Метод для удаления следующего узла
    public void DeleteAfter()
    {
        // Проверяем, что следующий узел не равен null (то есть, что он существует)
        if (Next != null)
        {
            // Обновляем ссылку на следующий узел текущего узла, чтобы она указывала на узел, следующий за следующим узлом
            Next = Next.Next;
        }
    }
}

class Program
{
    static void Main()
    {
        // Создаем три узла
        Node<string> firstNode = new Node<string>("A", null);
        Node<string> secondNode = new Node<string>("B", null);
        Node<string> thirdNode = new Node<string>("C", null);

        // Связываем узлы в список
        firstNode.Next = secondNode;
        secondNode.Next = thirdNode;

        // Выводим список в файл
        using (StreamWriter writer = new StreamWriter("list.txt"))
        {
            Node<string> currentNode = firstNode;

            while (currentNode != null)
            {
                writer.WriteLine(currentNode.Value);
                currentNode = currentNode.Next;
            }
        }

        // Удаляем список без потери ссылки на первый 
        firstNode.Next = null;
    }
}
