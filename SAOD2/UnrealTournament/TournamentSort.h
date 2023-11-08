#include <iostream>
#include <vector>

using namespace std;

// Класс для турнирной сортировки
class TournamentSort {
private:
    vector<int> tree; // Древовидная структура для турнирной сортировки
    vector<int> leaves; // Листья древа, содержащие элементы для сравнения
    int size; // Размер массива

    // Функция для построения древа
    void buildTree() {
        // Заполняем листья элементами массива
        for (int i = 0; i < size; ++i) {
            tree[size + i] = leaves[i];
        }

        // Строим древо, начиная с конца массива
        for (int i = size - 1; i > 0; --i) {
            tree[i] = min(tree[2 * i], tree[2 * i + 1]);
        }
    }

    // Рекурсивная реализация обновления дерева
    void updateTree(int index) {

     // Преобразуем индекс элемента в индекс узла дерева
    index += size;

    // Базовый случай рекурсии
    if (index <= 1) 
    return;

    // Рекурсивный вызов для обновления родительского узла  
    updateTree(index/2);

    // Обновляем значение в узле на основе дочерних узлов
    tree[index/2] = min(tree[index], tree[index+1]);
    }

public:
    // Конструктор класса
    TournamentSort(const vector<int>& arr) {
        size = arr.size();
        tree.resize(2 * size);
        leaves.resize(size);

        // Копируем элементы массива в листья древа
        for (int i = 0; i < size; ++i) {
            leaves[i] = arr[i];
        }

        // Строим древо
        buildTree();
    }

    // Сортировка исходного массива 
void sort() {
  
  // Массив для хранения отсортированных данных
  vector<int> sortedArray(size);

  // Выполняем size итераций
  for (int i = 0; i < size; i++) {

    // Извлекаем минимальное значение из корня дерева
    int min = tree[1];

    // Заменяем его на максимальное значение в листьях 
    leaves[min-1] = INT_MAX;  

    // Обновляем дерево
    updateTree(min-1);

    // Добавляем минимальное значение в отсортированный массив
    sortedArray[i] = min;
  }
}
};