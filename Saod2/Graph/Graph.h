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
#include <set>

// Класс графа
template <typename T>
class Graph
{
private:
    // Вес ребра представлен парой вершин (vertex1, vertex2)
    std::map<std::pair<T, T>, int> edgeWeights;

    // Список смежности, где ключ - вершина, а значение - список смежных вершин
    std::map<T, std::list<T>> adjacencyList;

    // Вспомогательный метод для рекурсивного обхода в глубину
    void DFSUtil(const T &vertex, std::set<T> &visited, std::vector<T> &result) const
    {
        // Проверяем, была ли вершина уже посещена
        if (visited.find(vertex) != visited.end())
        {
            return; // Если вершина уже посещена, прекращаем обработку
        }

        // Отмечаем текущую вершину как посещенную
        visited.insert(vertex);
        // Добавляем текущую вершину в список результатов
        result.push_back(vertex);

        // Перебираем всех соседей текущей вершины
        for (const auto &neighbor : adjacencyList.at(vertex))
        {
            // Если соседняя вершина еще не была посещена, рекурсивно вызываем DFSUtil для нее
            if (visited.find(neighbor) == visited.end())
            {
                DFSUtil(neighbor, visited, result);
            }
        }
    }

public:
    // Добавление вершины в граф
    void InsertVertex(const T &vertex)
    {
        if (adjacencyList.find(vertex) == adjacencyList.end())
        {
            adjacencyList[vertex] = std::list<T>();
        }
    }

    // Метод для обхода в глубину, начиная с заданной вершины
    std::vector<T> DFS(const T &startVertex) const
    {
        std::set<T> visited;   // Создаем множество для отслеживания посещенных вершин
        std::vector<T> result; // Вектор для хранения порядка обхода вершин

        // Вызываем вспомогательный рекурсивный метод DFSUtil
        // Передаем ему начальную вершину, множество посещенных вершин и вектор результата
        DFSUtil(startVertex, visited, result);

        // Возвращаем вектор с порядком обхода вершин после завершения обхода
        return result;
    }

    // Метод для обхода графа в ширину (Breadth-First Search, BFS).
    std::vector<T> BFS(const T &startVertex) const
    {
        std::set<T> visited;   // Множество для отслеживания посещенных вершин
        std::queue<T> queue;   // Очередь для управления порядком обхода вершин
        std::vector<T> result; // Вектор для хранения порядка обхода вершин

        // Добавляем начальную вершину в очередь и отмечаем её как посещенную
        queue.push(startVertex);

        // Продолжаем пока в очереди есть элементы
        while (!queue.empty())
        {
            T vertex = queue.front(); // Получаем вершину из начала очереди
            queue.pop();              // Удаляем эту вершину из очереди

            // Проверяем, была ли вершина уже посещена
            if (visited.find(vertex) != visited.end())
            {
                continue; // Если посещена, пропускаем остальные действия и переходим к следующей итерации
            }

            // Отмечаем вершину как посещенную и добавляем ее в результат
            visited.insert(vertex);
            result.push_back(vertex);

            // Добавляем все не посещенные соседние вершины в очередь
            for (const auto &neighbor : adjacencyList.at(vertex))
            {
                if (visited.find(neighbor) == visited.end())
                {
                    queue.push(neighbor);
                }
            }
        }

        // Возвращаем вектор с порядком обхода вершин
        return result;
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


    void saveToFile(const std::string &filename) const
    {
        std::ofstream outFile(filename);
        if (!outFile.is_open())
        {
            std::cerr << "Не удалось открыть файл для записи: " << filename << std::endl;
            return;
        }

        std::set<std::pair<T, T>> recordedEdges; // Для отслеживания уже записанных рёбер

        for (const auto &edgeWeightPair : edgeWeights)
        {
            const auto &edge = edgeWeightPair.first;
            const int weight = edgeWeightPair.second;

            // Проверяем, было ли ребро уже записано
            if (recordedEdges.find(std::make_pair(edge.second, edge.first)) != recordedEdges.end())
            {
                continue; // Если ребро уже записано, пропускаем его
            }

            outFile << edge.first << " " << edge.second << " " << weight << std::endl;
            recordedEdges.insert(edge); // Добавляем ребро в записанные
        }

        outFile.close();
    }
};
