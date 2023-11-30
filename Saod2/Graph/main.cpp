#include "Graph.h"
#include <cassert>

void testSingleVertexOperations()
{
    Graph g;

    // Тест на добавление и удаление вершины
    g.InsertVertex(1);
    assert(g.GetNeighbors(1).empty()); // Проверяем, что у новой вершины нет соседей
    g.DeleteVertex(1);
    assert(g.GetNeighbors(1).empty()); // Проверяем, что вершина удалена и список смежности пуст

    // Тест на добавление и удаление ребра
    g.InsertVertex(1);
    g.InsertEdge(1, 1, 10);          // Добавляем ребро из вершины в саму себя
    assert(g.GetWeight(1, 1) == 10); // Проверяем, что вес ребра корректный
    g.DeleteEdge(1, 1);
    assert(g.GetWeight(1, 1) == -1); // Проверяем, что ребро удалено

    // Тест на получение соседей и веса ребра
    g.DeleteVertex(1);                 // Удаляем вершину, чтобы убедиться в пустоте графа
    assert(g.GetNeighbors(1).empty()); // Проверяем, что у вершины нет соседей
    assert(g.GetWeight(1, 1) == -1);   // Проверяем, что вес ребра равен -1, что означает отсутствие ребра

    std::cout << "[OK] Single vertex test passed" << std::endl;
}

void testThreeVertexOperations()
{
    Graph g;

    // Тест на добавление вершин и ребер
    g.InsertVertex(1);
    g.InsertVertex(2);
    g.InsertVertex(3);
    g.InsertEdge(1, 2, 10);
    g.InsertEdge(2, 3, 20);
    g.InsertEdge(1, 3, 30);
    assert(g.GetWeight(1, 2) == 10);
    assert(g.GetWeight(2, 3) == 20);
    assert(g.GetWeight(1, 3) == 30);

    // Тест на удаление вершины
    g.DeleteVertex(3);
    assert(g.GetWeight(1, 3) == -1 && g.GetWeight(2, 3) == -1); // Проверяем удаление ребер
    assert(g.GetNeighbors(3).empty());                          // Проверяем, что вершина 3 удалена

    // Тест на получение соседей и веса ребра
    std::list<int> neighbors1 = g.GetNeighbors(1);
    assert(neighbors1.size() == 1 && neighbors1.front() == 2); // У вершины 1 должен быть один сосед - вершина 2
    std::list<int> neighbors2 = g.GetNeighbors(2);
    assert(neighbors2.size() == 1 && neighbors2.front() == 1); // У вершины 2 должен быть один сосед - вершина 1

    std::cout << "[OK] 3 vertex test passed" << std::endl;
}

void testEmptyGraphOperations()
{
    Graph g;

    // Тест на проверку пустоты графа
    assert(g.GetNeighbors(1).empty()); // Проверяем, что у несуществующей вершины нет соседей
    assert(g.GetWeight(1, 2) == -1);   // Проверяем, что вес ребра равен -1, что означает отсутствие ребра

    // Тест на удаление вершины из пустого графа
    g.DeleteVertex(1);                 // Попытка удалить несуществующую вершину
    assert(g.GetNeighbors(1).empty()); // Убеждаемся, что состояние графа не изменилось

    // Тест на добавление ребра в пустой граф
    g.InsertEdge(1, 2, 10);          // Попытка добавить ребро в пустой граф
    assert(g.GetWeight(1, 2) == -1); // Убеждаемся, что ребро не добавлено. Функция возвращает -1 как знак 
    std::cout << "[OK] 0 vertex test passed" << std::endl;
}

int main()
{
    testSingleVertexOperations();
    testThreeVertexOperations();
    testEmptyGraphOperations();

    return 0;
}
