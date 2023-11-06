//@author: gingerswaltz
#pragma once
#include <cstring>

template <typename T>
class Heap
{
private:
	T* heapArray;       // указатель на массив
	int arraySize;      // максимальная емкость кучи
	int heapSize;       // текущий размер кучи

    void HeapifyUp(int index) {
        int current = index; // Устанавливаем начальный индекс, с которого начинается восстановление свойств кучи.

        // Используем цикл для итеративного восстановления свойств кучи.
        while (current > 0) {
            int parent = (current - 1) / 2; // Вычисляем индекс родителя текущего элемента.

            // Сравниваем текущий элемент с его родителем.
            if (heapArray[parent] < heapArray[current]) {
                // Если текущий элемент больше родителя, меняем их местами.В
                std::swap(heapArray[parent], heapArray[current]); 
                current = parent; // Обновляем текущий индекс на индекс родителя.
            }
            else {
                // Если текущий элемент больше или равен родителю, свойство кучи восстановлено, и выходим из цикла.
                break;
            }
        }
    }


    // восстановления свойств max-кучи после удаления максимального элемента
    void HeapifyDown(int index) {
        int current = index;
        int leftChild, rightChild, largest;

        while (true) {
            leftChild = 2 * current + 1; // Левый дочерний элемент
            rightChild = 2 * current + 2; // Правый дочерний элемент
            largest = current; // Индекс наибольшего элемента

            // Сравниваем текущий элемент с левым дочерним элементом, если он существует.
            if (leftChild < heapSize && heapArray[leftChild] > heapArray[largest]) {
                largest = leftChild;
            }

            // Сравниваем наибольший элемент с правым дочерним элементом, если он существует.
            if (rightChild < heapSize && heapArray[rightChild] > heapArray[largest]) {
                largest = rightChild;
            }

            // Если наибольший элемент не является текущим элементом, меняем их местами и продолжаем проверку.
            if (largest != current) {
                std::swap(heapArray[current], heapArray[largest]);
                current = largest;
            }
            else {
                // Если свойства кучи восстановлены, выходим из цикла.
                break;
            }
        }
    }


public:
    // Конструктор класса куча
    Heap(int capacity) : heapSize(0), arraySize(capacity) {
        heapArray = new T[arraySize];
    }
    
    // 5th rule
    
    // Конструктор, принимающий массив и перестраивающий его по принципу кучи
    Heap(const T* array, int size) : arraySize(size), heapSize(size) {
    heapArray = new T[arraySize]; // Создаем массив для хранения элементов кучи.

    // memcpy todo
    // Копируем элементы из внешнего массива в нашу кучу.
    for (int i = 0; i < size; i++) {
        heapArray[i] = array[i];
    }

    // Начинаем преобразование массива в кучу снизу вверх (HeapifyDown).
    // Начинаем с последнего элемента и перемещаемся к корню.
    for (int i = (size - 1) / 2; i >= 0; i--) {
        HeapifyDown(i);
    }
}
    // Деструктор класса куча
    ~Heap() {
        delete[] heapArray;
    }

   // Метод для добавления элемента в кучу
void Insert(const T& item) {
    // Проверка, чтобы убедиться, что куча не достигла своей максимальной емкости.
    if (heapSize == arraySize) {
        // Если текущий размер кучи достиг предельной емкости, увеличиваем размер массива.
        // Увеличение размера вдвое является эффективной стратегией для динамического расширения массивов
        // и обеспечивает амортизированную сложность O(1) для операции вставки.
        arraySize *= 2;
        T* newHeapArray = new T[arraySize];
        // Создаем новый массив с увеличенным размером и копируем в него существующие элементы.
        // 
        // for (int i = 0; i < heapSize; i++) {
        //     newHeapArray[i] = heapArray[i];
        // }
        auto n=sizeof(heapArray[1]);

        memcpy(newHeapArray, heapArray, n*heapSize);
        // memcpy

        // Удаляем старый массив и обновляем указатель на новый массив.
        delete[] heapArray;
        heapArray = newHeapArray;
    }

    // Помещаем новый элемент в конец кучи
    heapArray[heapSize] = item;

    // Вызываем HeapifyUp для восстановления свойств кучи после вставки элемента.
    HeapifyUp(heapSize);

    // Увеличиваем размер кучи
    heapSize++;
}



    // Метод для удаления и возвращения максимального элемента из кучи
    T ExtractMax() {
        // Проверка, чтобы убедиться, что куча не достигла своей максимальной емкости.
        if (heapSize == 0)
            throw std::out_of_range("Heap is empty");

        // Сохраняем текущий максимальный элемент
        T maxElement = heapArray[0];

        // Заменяем корень кучи последним элементом
        heapArray[0] = heapArray[heapSize - 1];

        // Уменьшаем размер кучи
        heapSize--;

        // Вызываем HeapifyDown для восстановления свойств кучи после удаления максимального элемента
        HeapifyDown(0);

        // Возвращаем сохраненный максимальный элемент
        return maxElement;
    }


    // Метод для получения текущего размера кучи
    int Size() const {
        return heapSize;
    }

    // Метод для проверки, пустая ли куча
    bool IsEmpty() const {
        return heapSize == 0;
    }

    // Метод для поиска элемента в куче
    bool Find(const T& item) const {
        for (int i = 0; i < heapSize; i++) {
            if (heapArray[i] == item) {
                return true; // Элемент найден в куче
            }
        }
        return false; // Элемент не найден в куче
    }
    
    // Метод для удаления элемента из кучи по значению
    bool Remove(const T& item) {
        // Поиск элемента с заданным значением
        for (int i = 0; i < heapSize; i++) {
            if (heapArray[i] == item) {
                // Найден элемент, удаляем его из кучи.
                // Здесь можно применить различные стратегии удаления, например, заменить элемент последним и выполнить HeapifyUp/HeapifyDown.
                // В данном случае, мы просто заменяем элемент последним и уменьшаем размер кучи.
                heapArray[i] = heapArray[heapSize - 1];
                heapSize--;
                return true;
            }
        }
        // Элемент не найден, возвращаем false.
        return false;
    }

    // Метод для очистки кучи
    void Clear() {
        delete[] heapArray; // Удаляем существующий массив элементов
        heapArray = new T[arraySize]; // Создаем новый пустой массив
        heapSize = 0; // Сбрасываем размер кучи
    }

};

template <typename T>
void HeapSort(T* array, int size) {
    // Создаем экземпляр кучи и добавляем элементы массива в нее
    Heap<T> heap(size);
    for (int i = 0; i < size; i++) {
        heap.Insert(array[i]);
    }

    // Извлекаем максимальные элементы и сохраняем их в отсортированном порядке
    for (int i = size - 1; i >= 0; i--) {
        array[i] = heap.ExtractMax();
    }
}