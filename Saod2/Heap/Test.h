//@author: gingerswaltz
#pragma once
#include <iostream>
#include <cassert>
#include "Heap.h"
// todo: is_heap для массивчика вернувшегося из метода с класса
void TestConstructor() {
    Heap<int> heap(10);

    assert(heap.IsEmpty());
    assert(heap.Size() == 0);

    std::cout << "Constructor test passed." << std::endl;
}

void TestConstructor2() {
    Heap<int> heap(1);

    assert(heap.Size() == 0); // Начальный размер кучи равен 0
    assert(heap.IsEmpty());   // Куча пуста, так как нет добавленных элементов

    // Вставим элемент в кучу
    heap.Insert(42);

    // Теперь размер кучи должен быть 1 и она не пуста
    assert(heap.Size() == 1);
    assert(!heap.IsEmpty());

    std::cout << "Constructor (single element) test passed." << std::endl;
}


void TestConstructor3() {
    int arr[] = {4, 7, 2, 1, 9};
    int size = sizeof(arr) / sizeof(arr[0]);

    Heap<int> heap(arr, size);

    assert(!heap.IsEmpty());
    assert(heap.Size() == size);

    std::cout << "Constructor (multiple elements) test passed." << std::endl;
}

void TestInsert() {
    Heap<int> heap(5);

    heap.Insert(5);
    heap.Insert(3);
    heap.Insert(7);
    heap.Insert(2);
    heap.Insert(4);

    assert(heap.Size() == 5);
    assert(!heap.IsEmpty());

    std::cout << "Insert test passed." << std::endl;
}

void TestInsert2() {
    Heap<int> heap(1);

    heap.Insert(5);

    assert(heap.Size() == 1);
    assert(!heap.IsEmpty());

    std::cout << "Insert (single element) test passed." << std::endl;
}


void TestExtractMax() {
    Heap<int> heap(5);

    heap.Insert(5);
    heap.Insert(3);
    heap.Insert(7);
    heap.Insert(2);
    heap.Insert(4);

    int maxElement = heap.ExtractMax();

    assert(maxElement == 7);
    assert(heap.Size() == 4);

    std::cout << "ExtractMax test passed." << std::endl;
}

void TestExtractMax2() {
    Heap<int> heap(1);

    heap.Insert(5);
    int maxElement = heap.ExtractMax();

    assert(maxElement == 5);
    assert(heap.IsEmpty());

    std::cout << "ExtractMax (single element) test passed." << std::endl;
}

void TestExtractMax3() {
    Heap<int> heap(5);

    try {
        int maxElement = heap.ExtractMax();
        // Если успешно извлекли элемент из пустой кучи, тест не пройден.
        assert(false);
    } catch (const std::out_of_range& ex) {
        // Ожидаемое исключение для пустой кучи
        std::cout << "ExtractMax (empty heap) test passed." << std::endl;
    }
}


void TestSize() {
    Heap<int> heap(5);

    assert(heap.Size() == 0);

    heap.Insert(5);
    heap.Insert(3);
    heap.Insert(7);

    assert(heap.Size() == 3);

    std::cout << "Size test passed." << std::endl;
}

void TestSize2() {
    Heap<int> heap(5);

    assert(heap.Size() == 0);

    std::cout << "Size (empty heap) test passed." << std::endl;
}

void TestSize3() {
    Heap<int> heap(1);
    heap.Insert(5);

    assert(heap.Size() == 1);

    std::cout << "Size (single element) test passed." << std::endl;
}


void TestIsEmpty() {
    Heap<int> heap(5);

    assert(heap.IsEmpty());

    heap.Insert(5);

    assert(!heap.IsEmpty());

    std::cout << "IsEmpty test passed." << std::endl;
}

void TestIsEmpty2() {
    Heap<int> heap(5);

    assert(heap.IsEmpty());

    std::cout << "IsEmpty (empty heap) test passed." << std::endl;
}

void TestIsEmpty3() {
    Heap<int> heap(1);
    heap.Insert(5);

    assert(!heap.IsEmpty());

    std::cout << "IsEmpty (single element) test passed." << std::endl;
}


void TestFind() {
    Heap<int> heap(5);

    heap.Insert(5);
    heap.Insert(3);
    heap.Insert(7);

    // ����� ���������, ������� ���� � ����
    assert(heap.Find(5) == true);
    assert(heap.Find(3) == true);
    assert(heap.Find(7) == true);

    // ����� ���������, ������� ��� � ����
    assert(heap.Find(2) == false);
    assert(heap.Find(6) == false);

    std::cout << "Find test passed." << std::endl;
}

void TestFind2() {
    Heap<int> emptyHeap(5);

    assert(emptyHeap.Find(5) == false);
    assert(emptyHeap.Find(3) == false);
    assert(emptyHeap.Find(7) == false);

    std::cout << "Find (empty heap) test passed." << std::endl;
}

void TestFind3() {
    Heap<int> singleElementHeap(1);
    singleElementHeap.Insert(5);

    assert(singleElementHeap.Find(5) == true);
    assert(singleElementHeap.Find(3) == false);
    assert(singleElementHeap.Find(7) == false);

    std::cout << "Find (single element) test passed." << std::endl;
}


void TestRemove() {
    Heap<int> heap(5);

    heap.Insert(5);
    heap.Insert(3);
    heap.Insert(7);
    heap.Insert(3);

    // �������� ��������, ������� ���� � ����
    assert(heap.Remove(5) == true);
    assert(heap.Size() == 3);

    // ������� �������� ��������, ������� ���� � ����, �� ����������� ��������� ���
    assert(heap.Remove(3) == true);
    assert(heap.Size() == 2);

    // ������� �������� ��������, �������� ��� � ����
    assert(heap.Remove(2) == false);

    std::cout << "Remove test passed." << std::endl;
}

void TestRemove2() {
    Heap<int> emptyHeap(5);

    // Попытка удаления из пустой кучи, должно вернуть false
    assert(emptyHeap.Remove(5) == false);

    std::cout << "Remove (empty heap) test passed." << std::endl;
}

void TestRemove3() {
    Heap<int> singleElementHeap(1);
    singleElementHeap.Insert(5);

    // Попытка удаления из кучи из одного элемента, должно вернуть true
    assert(singleElementHeap.Remove(5) == true);
    assert(singleElementHeap.Size() == 0);

    // Попытка удаления несуществующего элемента, должно вернуть false
    assert(singleElementHeap.Remove(3) == false);

    std::cout << "Remove (single element) test passed." << std::endl;
}


void TestClear() {
    Heap<int> heap(5);

    heap.Insert(5);
    heap.Insert(3);
    heap.Insert(7);

    assert(heap.Size() == 3);

    heap.Clear();

    assert(heap.IsEmpty());
    assert(heap.Size() == 0);

    std::cout << "Clear test passed." << std::endl;
}
void TestClear2() {
    Heap<int> emptyHeap(5);

    // Очистка пустой кучи, куча должна остаться пустой
    emptyHeap.Clear();
    assert(emptyHeap.IsEmpty());
    assert(emptyHeap.Size() == 0);

    std::cout << "[OK] Clear (empty heap) test passed." << std::endl;
}

void TestClear3() {
    Heap<int> singleElementHeap(1);
    singleElementHeap.Insert(5);

    // Очистка кучи из одного элемента, куча должна стать пустой
    singleElementHeap.Clear();
    assert(singleElementHeap.IsEmpty());
    assert(singleElementHeap.Size() == 0);

    std::cout << "[OK] Clear (single element) test passed." << std::endl;
}

//todo is_sorted // 
void TestHeapSort() {
    int arr[] = {5, 3, 7, 2, 4};
    int size = sizeof(arr) / sizeof(arr[0]);

    HeapSort(arr, size);

    for (int i = 0; i < size - 1; i++) {
        assert(arr[i] <= arr[i + 1]);
    }

    std::cout << "[OK] HeapSort test passed." << std::endl;
}

void TestHeapSort2() {
    int emptyArr[] = {};
    int size = 0;

    HeapSort(emptyArr, size);

    // Для пустого массива ничего не должно сломаться

    std::cout << "[OK] HeapSort (empty array) test passed." << std::endl;
}

void TestHeapSort3() {
    int singleElementArr[] = {5};
    int size = 1;

    HeapSort(singleElementArr, size);

    // Для массива из одного элемента сортировка не требуется

    assert(singleElementArr[0] == 5);

    std::cout << "[OK] HeapSort (single element array) test passed." << std::endl;
}

void TestConstructorFromExternalArray() {
    int arr[] = {4, 7, 2, 1, 9, 5, 8};
    int size = sizeof(arr) / sizeof(arr[0]);

    // Создаем кучу из внешнего массива
    Heap<int> heap(arr, size);

    // Проверяем, что размер кучи равен размеру внешнего массива
    assert(heap.Size() == size);

    // Извлекаем максимальный элемент и проверяем его
    int maxElement = heap.ExtractMax();
    assert(maxElement == 9);

    // Проверяем, что размер уменьшился после извлечения
    assert(heap.Size() == size - 1);

    std::cout << "[OK] TestConstructorFromExternalArray test passed." << std::endl;
}

void TestConstructorFromExternalArray2() {
    // Тест для кучи из одного элемента
    int singleElementArr[] = {5};
    int singleElementSize = 1;
    Heap<int> singleElementHeap(singleElementArr, singleElementSize);

    assert(singleElementHeap.Size() == singleElementSize);
    assert(singleElementHeap.ExtractMax() == 5);
    assert(singleElementHeap.IsEmpty());

    // Тест для пустой кучи
    int emptyArr[] = {};
    int emptySize = 0;
    Heap<int> emptyHeap(emptyArr, emptySize);

    assert(emptyHeap.IsEmpty());
    assert(emptyHeap.Size() == emptySize);
    
    std::cout << "[OK] TestConstructorFromExternalArray test passed." << std::endl;
}
