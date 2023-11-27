#include <iostream>
#include <map>
#include <list>
#include <utility>

class Graph
{
private:
    // Вес ребра представлен парой вершин (vertex1, vertex2)
    std::map<std::pair<int, int>, int> edgeWeights;

    // Список смежности, где ключ - вершина, а значение - список смежных вершин
    std::map<int, std::list<int>> adjacencyList;

public:
    // Конструктор по умолчанию
    Graph() = default;

    // Конструктор копирования
    Graph(const Graph &other)
        : adjacencyList(other.adjacencyList), edgeWeights(other.edgeWeights) {}

    // Оператор копирования
    Graph &operator=(const Graph &other)
    {
        if (this != &other)
        {
            adjacencyList = other.adjacencyList;
            edgeWeights = other.edgeWeights;
        }
        return *this;
    }

    // Деструктор
    ~Graph()
    {
        // Так как используются стандартные контейнеры, особой обработки не требуется
    }

    // Конструктор перемещения
    Graph(Graph &&other) noexcept
        : adjacencyList(std::move(other.adjacencyList)), edgeWeights(std::move(other.edgeWeights)) {}

    // Оператор перемещения
    Graph &operator=(Graph &&other) noexcept
    {
        if (this != &other)
        {
            adjacencyList = std::move(other.adjacencyList);
            edgeWeights = std::move(other.edgeWeights);
        }
        return *this;
    }

    // Добавление вершины в граф
    void InsertVertex(int vertex)
    {
        // Если вершина уже есть в графе, не добавляем ее
        if (adjacencyList.find(vertex) == adjacencyList.end())
        {
            adjacencyList[vertex] = std::list<int>();
        }
    }

    void InsertEdge(int vertex1, int vertex2, int weight)
    {
        // Проверяем, существуют ли обе вершины в графе
        if (adjacencyList.find(vertex1) != adjacencyList.end() && adjacencyList.find(vertex2) != adjacencyList.end())
        {
            // Добавляем vertex2 в список смежности vertex1 и наоборот
            adjacencyList[vertex1].push_back(vertex2);
            adjacencyList[vertex2].push_back(vertex1);

            // Устанавливаем вес ребра в обоих направлениях
            edgeWeights[std::make_pair(vertex1, vertex2)] = weight;
            edgeWeights[std::make_pair(vertex2, vertex1)] = weight;
        }
    }

    // Удаление вершины и всех инцидентных ей ребер
    void DeleteVertex(int vertex)
    {
        // Удаляем все ребра, инцидентные вершине
        for (auto adjVertex : adjacencyList[vertex])
        {
            adjacencyList[adjVertex].remove(vertex);
            edgeWeights.erase(std::make_pair(vertex, adjVertex));
            edgeWeights.erase(std::make_pair(adjVertex, vertex));
        }

        // Удаляем вершину из списка смежности
        adjacencyList.erase(vertex);
    }

    // Удаление ребра между двумя вершинами
    void DeleteEdge(int vertex1, int vertex2)
    {
        // Удаляем vertex2 из списка смежных вершин для vertex1.
        // Это означает, что ребро больше не соединяет vertex1 и vertex2.
        adjacencyList[vertex1].remove(vertex2);

        // Аналогично удаляем vertex1 из списка смежных вершин для vertex2.
        adjacencyList[vertex2].remove(vertex1);

        // Удаляем вес ребра из карты edgeWeights.
        // Это делается для направления vertex1 -> vertex2.
        edgeWeights.erase(std::make_pair(vertex1, vertex2));

        // Удаляем вес ребра из карты edgeWeights для обратного направления.
        // Это необходимо, так как граф неориентированный, и веса хранятся для обоих направлений.
        edgeWeights.erase(std::make_pair(vertex2, vertex1));
    }

    // Получение списка смежных вершин
    std::list<int> GetNeighbors(int vertex)
    {
        return adjacencyList[vertex];
    }

    // Получение веса ребра
    int GetWeight(int vertex1, int vertex2)
    {
        if (edgeWeights.find(std::make_pair(vertex1, vertex2)) != edgeWeights.end())
        {
            return edgeWeights[std::make_pair(vertex1, vertex2)];
        }
        else
        {
            return -1; // Возвращаем -1, если ребра нет
        }
    }
};
