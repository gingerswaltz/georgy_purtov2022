//@author: gingerswaltz
#include <iostream>
#include <vector>

using namespace std;
// функция вывода вектора
template<typename T>
void print(vector<T> vec)
{
    int n = vec.size();
    for (int i = 0; i < n; i++) {
        cout << vec[i] << " ";
    }
}

// шаблонная функция турнирной сортировки asc (по возрастанию)
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

    
    // Назначает каждому узлу в дереве «бесконечное» (максимальное) значение используемого типа данных.
    for (int i = 0; i < size; i++) {
        tree[i] = numeric_limits<T>::max();
    }

    
    // Присваивает элементы из несортированного массива в листья
    for (int i = 0; i < vecSize; i++) {
        tree[treeSize + i] = vec[i];
    }

    
    // Постройте дерево турнира, выбрав минимальное количество узлов в каждой паре.
    // здесь - чем больше индекс i, тем элемент дальше от корня 
    // example : i=1, 2*i = наследник левый, (2*i)+1 = наследник правый 
    for (int i = treeSize - 1; i >= 1; i--) {
        tree[i] = min(tree[2 * i], tree[2 * i + 1]);
    } 


    // Извлечение элементы из дерева турнира в порядке возрастания.
    int sortIndex = 0;
    while (sortIndex < vecSize) {

        
        // Присваивает корень исходному массиву и присваивает корню значение «бесконечно».
        vec[sortIndex++] = tree[1];
        tree[1] = numeric_limits<T>::max();


        // Заменяет минимальное значение на «бесконечное».
        int node = 1;
        while (node < treeSize) {
            int leftChild = 2 * node;
            int rightChild = 2 * node + 1;

     
            // Узлу присваивается порядковый номер наименьшего значения
            node = (tree[leftChild] < tree[rightChild]) ? leftChild : rightChild;

            
            // Устанавливает наименьшее число на «бесконечное»
            if (tree[leftChild] < tree[rightChild]) {
                tree[leftChild] = numeric_limits<T>::max();
            }
            else {
                tree[rightChild] = numeric_limits<T>::max();
            }
        }


        // Распространяет минимум каждой пары узлов
        for (int i = treeSize - 1; i >= 1; i--) {
            tree[i] = min(tree[2 * i], tree[2 * i + 1]);
        }
    }
}