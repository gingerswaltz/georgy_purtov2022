//@author: gingerswaltz
#pragma once
#include <iostream>
#include <cassert>
#include "Heap.h"

void TestConstructor() {
    Heap<int> heap(10);

    assert(heap.IsEmpty());
    assert(heap.Size() == 0);

    std::cout << "Constructor test passed." << std::endl;
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


void TestSize() {
    Heap<int> heap(5);

    assert(heap.Size() == 0);

    heap.Insert(5);
    heap.Insert(3);
    heap.Insert(7);

    assert(heap.Size() == 3);

    std::cout << "Size test passed." << std::endl;
}

void TestIsEmpty() {
    Heap<int> heap(5);

    assert(heap.IsEmpty());

    heap.Insert(5);

    assert(!heap.IsEmpty());

    std::cout << "IsEmpty test passed." << std::endl;
}


void TestFind() {
    Heap<int> heap(5);

    heap.Insert(5);
    heap.Insert(3);
    heap.Insert(7);

    // Поиск элементов, которые есть в куче
    assert(heap.Find(5) == true);
    assert(heap.Find(3) == true);
    assert(heap.Find(7) == true);

    // Поиск элементов, которых нет в куче
    assert(heap.Find(2) == false);
    assert(heap.Find(6) == false);

    std::cout << "Find test passed." << std::endl;
}


void TestRemove() {
    Heap<int> heap(5);

    heap.Insert(5);
    heap.Insert(3);
    heap.Insert(7);
    heap.Insert(3);

    // Удаление элемента, который есть в куче
    assert(heap.Remove(5) == true);
    assert(heap.Size() == 3);

    // Попытка удаления элемента, который есть в куче, но встречается несколько раз
    assert(heap.Remove(3) == true);
    assert(heap.Size() == 2);

    // Попытка удаления элемента, которого нет в куче
    assert(heap.Remove(2) == false);

    std::cout << "Remove test passed." << std::endl;
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

void TestHeapSort() {
    int arr[] = { 5, 3, 7, 2, 4 };
    int size = sizeof(arr) / sizeof(arr[0]);

    HeapSort<int>::Sort(arr, size);

    for (int i = 0; i < size - 1; i++) {
        assert(arr[i] <= arr[i + 1]);
    }

    std::cout << "HeapSort test passed." << std::endl;
}