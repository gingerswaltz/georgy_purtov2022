//@author: gingerswaltz
#pragma once

// todo: l��������� ������ ��� ������� ���� �� �������. ����������� � ��������� ������� �����(����������� �� �������� ����)
template <typename T>
class Heap
{
private:
	T* heapArray;       // ��������� �� ������
	int arraySize;      // ������������ ������� ����
	int heapSize;       // ������� ������ ����

    void HeapifyUp(int index) {
        int current = index; // ������������� ��������� ������, � �������� ���������� �������������� ������� ����.

        // ���������� ���� ��� ������������ �������������� ������� ����.
        while (current > 0) {
            int parent = (current - 1) / 2; // ��������� ������ �������� �������� ��������.

            // ���������� ������� ������� � ��� ���������.
            if (heapArray[parent] < heapArray[current]) {
                // ���� ������� ������� ������ ��������, ������ �� �������.�
                std::swap(heapArray[parent], heapArray[current]); 
                current = parent; // ��������� ������� ������ �� ������ ��������.
            }
            else {
                // ���� ������� ������� ������ ��� ����� ��������, �������� ���� �������������, � ������� �� �����.
                break;
            }
        }
    }


    // �������������� ������� max-���� ����� �������� ������������� ��������
    void HeapifyDown(int index) {
        int current = index;
        int leftChild, rightChild, largest;

        while (true) {
            leftChild = 2 * current + 1; // ����� �������� �������
            rightChild = 2 * current + 2; // ������ �������� �������
            largest = current; // ������ ����������� ��������

            // ���������� ������� ������� � ����� �������� ���������, ���� �� ����������.
            if (leftChild < heapSize && heapArray[leftChild] > heapArray[largest]) {
                largest = leftChild;
            }

            // ���������� ���������� ������� � ������ �������� ���������, ���� �� ����������.
            if (rightChild < heapSize && heapArray[rightChild] > heapArray[largest]) {
                largest = rightChild;
            }

            // ���� ���������� ������� �� �������� ������� ���������, ������ �� ������� � ���������� ��������.
            if (largest != current) {
                std::swap(heapArray[current], heapArray[largest]);
                current = largest;
            }
            else {
                // ���� �������� ���� �������������, ������� �� �����.
                break;
            }
        }
    }


public:
    // ����������� ������ ����
    Heap(int capacity) : heapSize(0), arraySize(capacity) {
        heapArray = new T[arraySize];
    }

    // ���������� ������ ����
    ~Heap() {
        delete[] heapArray;
    }

   // ����� ��� ���������� �������� � ����
    template <typename T>
    void Insert(const T& item) {
        // ��������, ����� ���������, ��� ���� �� �������� ����� ������������ �������.
        if (heapSize == arraySize)
            throw std::out_of_range("Heap is full");

        // �������� ����� ������� � ����� ����
        heapArray[heapSize] = item;

        // �������� HeapifyUp ��� �������������� ������� ���� ����� ������� ��������.
        HeapifyUp(heapSize);

        // ����������� ������ ����
        heapSize++;
    }


    // ����� ��� �������� � ����������� ������������� �������� �� ����
    T ExtractMax() {
        // ��������, ����� ���������, ��� ���� �� �������� ����� ������������ �������.
        if (heapSize == 0)
            throw std::out_of_range("Heap is empty");

        // ��������� ������� ������������ �������
        T maxElement = heapArray[0];

        // �������� ������ ���� ��������� ���������
        heapArray[0] = heapArray[heapSize - 1];

        // ��������� ������ ����
        heapSize--;

        // �������� HeapifyDown ��� �������������� ������� ���� ����� �������� ������������� ��������
        HeapifyDown(0);

        // ���������� ����������� ������������ �������
        return maxElement;
    }


    // ����� ��� ��������� �������� ������� ����
    int Size() const {
        return heapSize;
    }

    // ����� ��� ��������, ������ �� ����
    bool IsEmpty() const {
        return heapSize == 0;
    }

    // ����� ��� ������ �������� � ����
    bool Find(const T& item) const {
        for (int i = 0; i < heapSize; i++) {
            if (heapArray[i] == item) {
                return true; // ������� ������ � ����
            }
        }
        return false; // ������� �� ������ � ����
    }
    
    // ����� ��� �������� �������� �� ���� �� ��������
    bool Remove(const T& item) {
        // ����� �������� � �������� ���������
        for (int i = 0; i < heapSize; i++) {
            if (heapArray[i] == item) {
                // ������ �������, ������� ��� �� ����.
                // � ������ ������, �� ������ �������� ������� ��������� � ��������� ������ ����.
                heapArray[i] = heapArray[heapSize - 1];
                heapSize--;
                return true;
            }
        }
        // ������� �� ������, ���������� false.
        return false;
    }

    // ����� ��� ������� ����
    void Clear() {
     // delete[] heapArray; // ������� ������������ ������ ���������
      //   heapArray = new T[arraySize]; // ������� ����� ������ ������
        heapSize = 0; // ���������� ������ ����
    }

   

};
// todo: to func
template <typename T>
class HeapSort {
public:
    // ����������� ����� ��� ���������� ������� � �������������� ���������� �����
    static void Sort(T* array, int size) {
        // ������� ��������� ���� � ��������� �������� ������� � ���
        Heap<T> heap(size);
        for (int i = 0; i < size; i++) {
            heap.Insert(array[i]);
        }

        // ��������� ������������ �������� � ��������� �� � ��������������� �������
        for (int i = size - 1; i >= 0; i--) {
            array[i] = heap.ExtractMax();
        }
    }
};