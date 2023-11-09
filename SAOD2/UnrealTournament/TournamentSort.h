#include <iostream>
#include <vector>

using namespace std;

template<typename T>
void print(vector<T> vec)
{
    int n = vec.size();
    for (int i = 0; i < n; i++) {
        cout << vec[i] << " ";
    }
}
template<typename T>
void tournamentSort(vector<T> &vec)
{
    int vecSize = vec.size();
    /// Определяем размер турнирного дерева
    int treeSize = 1;
    while (treeSize <= vecSize) {
        treeSize *= 2;
    }

    // Создаем массив размером с общее количество узлов (элементов) в дереве турнира.
    int size = (2 * treeSize);
    vector<T> tree(size);

    // Assigns each node in the tree with an "infinite" (max) value of datatype used
    // Назначает каждому узлу в дереве «бесконечное» (максимальное) значение используемого типа данных.
    for (int i = 0; i < size; i++) {
        tree[i] = numeric_limits<T>::max();
    }

    // Assigns elements from the unsorted array into the array with the total 
    // Присваивает элементы из несортированного массива в листья
    for (int i = 0; i < vecSize; i++) {
        tree[treeSize + i] = vec[i];
    }

    // Build the tournament tree by selecting the minimum of each pair of number of nodes
    // Постройте дерево турнира, выбрав минимальное количество узлов в каждой паре.
    for (int i = treeSize - 1; i >= 1; i--) {
        tree[i] = min(tree[2 * i], tree[2 * i + 1]);
    } 

    // Extract elements from the tournament tree in ascending order
    // Извлекайте элементы из дерева турнира в порядке возрастания.
    int sortIndex = 0;
    while (sortIndex < vecSize) {

        // Assigns root to original array and assigns "infinite" to root
        // Присваивает корень исходному массиву и присваивает корню значение «бесконечно».
        vec[sortIndex++] = tree[1];
        tree[1] = numeric_limits<T>::max();


        // Replaces minimum value with "infinite"
        // Заменяет минимальное значение на «бесконечное».
        int node = 1;
        while (node < treeSize) {
            int leftChild = 2 * node;
            int rightChild = 2 * node + 1;

            // Node is assigned the index number of the lowest value
            // Узлу присваивается порядковый номер наименьшего значения
            node = (tree[leftChild] < tree[rightChild]) ? leftChild : rightChild;

            // Sets smallest number to "infinite"
            // Устанавливает наименьшее число на «бесконечное»
            if (tree[leftChild] < tree[rightChild]) {
                tree[leftChild] = numeric_limits<T>::max();
            }
            else {
                tree[rightChild] = numeric_limits<T>::max();
            }
        }

        // Propagates the minimum of each pair of nodes
        // Распространяет минимум каждой пары узлов
        for (int i = treeSize - 1; i >= 1; i--) {
            tree[i] = min(tree[2 * i], tree[2 * i + 1]);
        }
    }
}