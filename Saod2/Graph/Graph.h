// @author: gingerswaltz
#include <iostream>
#include <map>
#include <list>
#include <utility>
#include <vector>
#include <queue>
#include <unordered_map>
#include <limits>
#include <fstream>
#include <sstream>

// Класс графа
template <typename T>
class Graph
{
private:
    // Вес ребра представлен парой вершин (vertex1, vertex2)
    std::map<std::pair<T, T>, int> edgeWeights;

    // Список смежности, где ключ - вершина, а значение - список смежных вершин
    std::map<T, std::list<T>> adjacencyList;

public:
    // Добавление вершины в граф
    void InsertVertex(const T &vertex)
    {
        if (adjacencyList.find(vertex) == adjacencyList.end())
        {
            adjacencyList[vertex] = std::list<T>();
        }
    }

    // Добавление ребра и его веса
    void InsertEdge(const T &vertex1, const T &vertex2, int weight)
    {
        if (adjacencyList.find(vertex1) != adjacencyList.end() && adjacencyList.find(vertex2) != adjacencyList.end())
        {
            adjacencyList[vertex1].push_back(vertex2);
            adjacencyList[vertex2].push_back(vertex1);
            edgeWeights[std::make_pair(vertex1, vertex2)] = weight;
            edgeWeights[std::make_pair(vertex2, vertex1)] = weight;
        }
    }

    // Удаление вершины и всех инцидентных ей ребер
    void DeleteVertex(const T &vertex)
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
    void DeleteEdge(const T &vertex1, const T &vertex2)
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
    std::list<T> GetNeighbors(const T &vertex)
    {
        return adjacencyList[vertex];
    }

    const int *GetWeight(const T &vertex1, const T &vertex2)
    {
        auto it = edgeWeights.find(std::make_pair(vertex1, vertex2));
        if (it != edgeWeights.end())
        {
            return &(it->second);
        }
        else
        {
            return nullptr; // Возвращаем nullptr, если ребра нет
        }
    }

    // Изменение веса ребра или добавление нового ребра с заданным весом
    void SetEdgeWeight(const T &vertex1, const T &vertex2, int newWeight)
    {
        // Добавляем вершины в граф, если они еще не существуют
        InsertVertex(vertex1);
        InsertVertex(vertex2);

        // Обновляем вес ребра в обоих направлениях
        edgeWeights[std::make_pair(vertex1, vertex2)] = newWeight;
        edgeWeights[std::make_pair(vertex2, vertex1)] = newWeight;
    }

    // Алгоритм Дейкстры для нахождения кратчайшего пути от start до всех других вершин
    std::unordered_map<T, int> Dijkstra(const T &start)
    {
        // Инициализация расстояний до всех вершин бесконечно большими значениями
        std::unordered_map<T, int> distances;
        for (const auto &pair : adjacencyList)
        {
            distances[pair.first] = std::numeric_limits<int>::max();
        }

        // Использование приоритетной очереди для выбора следующей вершины с минимальным расстоянием
        std::priority_queue<std::pair<int, T>, std::vector<std::pair<int, T>>, std::greater<std::pair<int, T>>> pq;
        pq.push(std::make_pair(0, start)); // Начальная вершина с расстоянием 0
        distances[start] = 0;

        while (!pq.empty())
        {
            T vertex = pq.top().second; // Текущая вершина с минимальным расстоянием
            int dist = pq.top().first;
            pq.pop();

            // Пропускаем обработку, если найдено более короткое расстояние
            if (dist > distances[vertex])
                continue;

            // Перебор всех соседних вершин
            for (const auto &neighbor : adjacencyList[vertex])
            {
                int nextDist = dist + *GetWeight(vertex, neighbor);
                // Если найден более короткий путь к соседу, обновляем его расстояние
                if (nextDist < distances[neighbor])
                {
                    distances[neighbor] = nextDist;
                    pq.push(std::make_pair(nextDist, neighbor)); // Добавляем соседа в очередь для дальнейшей обработки
                }
            }
        }

        return distances; // Возвращаем карту расстояний от начальной вершины до всех остальных
    }

    // Функция для загрузки графа из файла
    void LoadGraphFromFile(const std::string &filename)
    {
        std::ifstream file(filename);
        // Проверяем, открылся ли файл
        if (!file.is_open())
        {
            std::cerr << "Не удалось открыть файл: " << filename << std::endl;
            return;
        }

        T vertex1, vertex2; // Переменные для хранения вершин
        int weight;         // Переменная для хранения веса ребра
        std::string line;

        // Чтение файла построчно
        while (std::getline(file, line))
        {
            std::istringstream iss(line);
            // Извлекаем из строки две вершины и вес ребра
            if (!(iss >> vertex1 >> vertex2 >> weight))
            {
                // В случае ошибки чтения строки, выводим сообщение и продолжаем с следующей строки
                std::cerr << "Ошибка чтения строки: " << line << std::endl;
                continue;
            }

            // Добавляем вершины и ребро в граф
            InsertVertex(vertex1);
            InsertVertex(vertex2);
            InsertEdge(vertex1, vertex2, weight);
        }

        // Закрываем файл после чтения
        file.close();
    }
};
