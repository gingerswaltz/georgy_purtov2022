// @author: gingerswaltz

#include "Graph.h"
#include <cassert>

void testSingleVertexOperations()
{
    Graph<int> g;

    // Тест на добавление и удаление вершины
    g.InsertVertex(1);
    assert(g.GetNeighbors(1).empty()); // Проверяем, что у новой вершины нет соседей
    g.DeleteVertex(1);
    assert(g.GetNeighbors(1).empty()); // Проверяем, что вершина удалена и список смежности пуст

    // Тест на добавление и удаление ребра
    g.InsertVertex(1);
    g.InsertEdge(1, 1, 10);           // Добавляем ребро из вершины в саму себя
    assert(*g.GetWeight(1, 1) == 10); // Проверяем, что вес ребра корректный
    g.DeleteEdge(1, 1);
    assert(g.GetWeight(1, 1) == nullptr); // Проверяем, что ребро удалено

    // Тест на получение соседей и веса ребра
    g.DeleteVertex(1);                    // Удаляем вершину, чтобы убедиться в пустоте графа
    assert(g.GetNeighbors(1).empty());    // Проверяем, что у вершины нет соседей
    assert(g.GetWeight(1, 1) == nullptr); // Проверяем, что вес ребра равен -1, что означает отсутствие ребра

    std::cout << "[OK] Single vertex test passed" << std::endl;
}

void testThreeVertexOperations()
{
    Graph<int> g;

    // Тест на добавление вершин и ребер
    g.InsertVertex(1);
    g.InsertVertex(2);
    g.InsertVertex(3);
    g.InsertEdge(1, 2, 10);
    g.InsertEdge(2, 3, 20);
    g.InsertEdge(1, 3, 30);
    assert(*g.GetWeight(1, 2) == 10);
    assert(*g.GetWeight(2, 3) == 20);
    assert(*g.GetWeight(1, 3) == 30);

    // Тест на удаление вершины
    g.DeleteVertex(3);
    assert(g.GetWeight(1, 3) == nullptr && g.GetWeight(2, 3) == nullptr); // Проверяем удаление ребер
    assert(g.GetNeighbors(3).empty());                                    // Проверяем, что вершина 3 удалена

    // Тест на получение соседей и веса ребра
    std::list<int> neighbors1 = g.GetNeighbors(1);
    assert(neighbors1.size() == 1 && neighbors1.front() == 2); // У вершины 1 должен быть один сосед - вершина 2
    std::list<int> neighbors2 = g.GetNeighbors(2);
    assert(neighbors2.size() == 1 && neighbors2.front() == 1); // У вершины 2 должен быть один сосед - вершина 1

    std::cout << "[OK] 3 vertex test passed" << std::endl;
}

void testEmptyGraphOperations()
{
    Graph<int> g;

    // Тест на проверку пустоты графа
    assert(g.GetNeighbors(1).empty());    // Проверяем, что у несуществующей вершины нет соседей
    assert(g.GetWeight(1, 2) == nullptr); // Проверяем, что вес ребра равен -1, что означает отсутствие ребра

    // Тест на удаление вершины из пустого графа
    g.DeleteVertex(1);                 // Попытка удалить несуществующую вершину
    assert(g.GetNeighbors(1).empty()); // Убеждаемся, что состояние графа не изменилось

    // Тест на добавление ребра в пустой граф
    g.InsertEdge(1, 2, 10);               // Попытка добавить ребро в пустой граф
    assert(g.GetWeight(1, 2) == nullptr); // Убеждаемся, что ребро не добавлено.
    std::cout << "[OK] 0 vertex test passed" << std::endl;
}

void testSetEdgeWeight()
{
    Graph<int> g;

    // Проверка добавления нового ребра
    g.SetEdgeWeight(1, 2, 50);
    assert(*g.GetWeight(1, 2) == 50);
    assert(*g.GetWeight(2, 1) == 50); // Проверяем в обоих направлениях, так как граф неориентированный

    // Проверка изменения веса существующего ребра
    g.SetEdgeWeight(1, 2, 100);
    assert(*g.GetWeight(1, 2) == 100);
    assert(*g.GetWeight(2, 1) == 100);

    // Проверка добавления ребра с новыми вершинами
    g.SetEdgeWeight(3, 4, 30);
    assert(*g.GetWeight(3, 4) == 30);
    assert(*g.GetWeight(4, 3) == 30);

    std::cout << "[OK] Set edge weight test passed" << std::endl;
}

void testDijkstra()
{
    Graph<int> g;

    // Создаем граф
    g.InsertVertex(1);
    g.InsertVertex(2);
    g.InsertVertex(3);
    g.InsertVertex(4);

    // Создаем ребра с весами
    g.InsertEdge(1, 2, 1);
    g.InsertEdge(1, 3, 4);
    g.InsertEdge(2, 3, 2);
    g.InsertEdge(3, 4, 1);

    // Вызываем алгоритм Дейкстры из вершины 1
    std::unordered_map<int, int> distances = g.Dijkstra(1);

    // Проверяем расстояния
    assert(distances[1] == 0); // Расстояние от 1 до 1 равно 0
    assert(distances[2] == 1); // Расстояние от 1 до 2 равно 1
    assert(distances[3] == 3); // Расстояние от 1 до 3 равно 3 (через вершину 2)
    assert(distances[4] == 4); // Расстояние от 1 до 4 равно 4 (через вершины 2 и 3)

    std::cout << "[OK] Dijkstra test passed" << std::endl;
}

void testLoadGraphFromFile()
{
    Graph<int> g;
    g.LoadGraphFromFile("graph.txt"); // Укажите правильный путь к файлу

    // Проверяем наличие вершин и рёбер
    assert(!g.GetNeighbors(1).empty()); // Проверяем, что у вершины 1 есть соседи
    assert(*g.GetWeight(1, 2) == 3);    // Проверяем вес ребра 1-2
    assert(*g.GetWeight(2, 3) == 4);    // Проверяем вес ребра 2-3
    assert(*g.GetWeight(1, 3) == 7);    // Проверяем вес ребра 1-3

    std::cout << "[OK] Load graph from file test passed" << std::endl;
}

void testDFS()
{
    Graph<int> g;
    g.InsertVertex(1);
    g.InsertVertex(2);
    g.InsertVertex(3);
    g.InsertVertex(4);

    g.InsertEdge(1, 2, 1);
    g.InsertEdge(2, 3, 1);
    g.InsertEdge(3, 4, 1);
    g.InsertEdge(4, 1, 1);

    auto dfsResult = g.DFS(1);

    // Предположим, что ожидаемый порядок DFS обхода: 1, 2, 3, 4
    std::vector<int> expectedDFSOrder = {1, 2, 3, 4};
    assert(dfsResult == expectedDFSOrder);

    std::cout << "[OK] DFS test passed" << std::endl;
}

// todo : граф с циклом
void testBFS()
{
    Graph<int> g;
    g.InsertVertex(1);
    g.InsertVertex(2);
    g.InsertVertex(3);
    g.InsertVertex(4);

    g.InsertEdge(1, 2, 1);
    g.InsertEdge(1, 3, 1);
    g.InsertEdge(2, 4, 1);
    g.InsertEdge(3, 4, 1);

    auto bfsResult = g.BFS(1);

    // Предположим, что ожидаемый порядок BFS обхода: 1, 2, 3, 4
    std::vector<int> expectedBFSOrder = {1, 2, 3, 4};
    assert(bfsResult == expectedBFSOrder);

    std::cout << "[OK] BFS test passed" << std::endl;
}

void testSaveToFile()
{
    Graph<int> g;
    // Заполнение графа вершинами и рёбрами
    g.InsertVertex(1);
    g.InsertVertex(2);
    g.InsertVertex(3);
    g.InsertEdge(1, 2, 10);
    g.InsertEdge(2, 3, 20);
    g.InsertEdge(1, 3, 30);

    const std::string filename = "graph_out.txt";
    g.saveToFile(filename);

    // Открытие файла и проверка его содержимого
    std::ifstream inFile(filename);
    assert(inFile.is_open()); // Убедитесь, что файл успешно открылся

    std::string line;
    std::stringstream fileContent;

    while (std::getline(inFile, line))
    {
        fileContent << line << "\n";
    }

    inFile.close();

    // Проверка содержимого файла на соответствие ожидаемому
    const std::string expectedContent = "1 2 10\n1 3 30\n2 3 20\n";
    assert(fileContent.str() == expectedContent);

    std::cout << "[OK] Save to file test passed" << std::endl;
}


void testDFSCycle()
{
    Graph<int> g;
    g.InsertVertex(1);
    g.InsertVertex(2);
    g.InsertVertex(3);
    g.InsertVertex(4);

    g.InsertEdge(1, 2, 1);
    g.InsertEdge(2, 3, 1);
    g.InsertEdge(3, 4, 1);
    g.InsertEdge(4, 2, 1); // Добавление ребра, создающего цикл
    // 1 -> 2 -> 3 -> 4
//      ^         |
//      |_________|
//
    auto dfsResult = g.DFS(1);

    // В данном случае, порядок: 1, 2, 3, 4
    std::vector<int> expectedDFSOrder = {1, 2, 3, 4};
    assert(dfsResult == expectedDFSOrder);

    std::cout << "[OK] DFS with cycle test passed" << std::endl;
}

void testBFSCycle()
{
    Graph<int> g;
    g.InsertVertex(1);
    g.InsertVertex(2);
    g.InsertVertex(3);
    g.InsertVertex(4);

    g.InsertEdge(1, 2, 1);
    g.InsertEdge(2, 3, 1);
    g.InsertEdge(3, 4, 1);
    g.InsertEdge(4, 2, 1); // Добавление ребра, создающего цикл

    auto bfsResult = g.BFS(1);

    // В данном случае, порядок: 1, 2, 3, 4
    std::vector<int> expectedBFSOrder = {1, 2, 3, 4};
    assert(bfsResult == expectedBFSOrder);

    std::cout << "[OK] BFS with cycle test passed" << std::endl;
}

int main()
{
    testSingleVertexOperations();
    testThreeVertexOperations();
    testEmptyGraphOperations();
    testSetEdgeWeight();
    testDijkstra();
    testLoadGraphFromFile();
    testSaveToFile();
    testBFS();
    testDFS();
    testBFSCycle();
    testDFSCycle();
    return 0;
}
