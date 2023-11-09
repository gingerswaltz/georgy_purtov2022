#include <cassert>
#include <algorithm>
#include "TournamentSort.h"

// Проверка сортировки пустого массива
void testSortEmptyArray() {
    vector<int> array;
    vector<int> copy = array;

    tournamentSort(array);

    assert(array == copy);
}

// Проверка сортировки массива из одного элемента  
void testSortSingleElement() {
    int value = 42;
    vector<int> array = { value };
    vector<int> copy = array;

    tournamentSort(array);

    assert(array == copy);
    assert(array[0] == value);
}

// Проверка сортировки обратным порядком
void testReverseSort() {
    vector<int> array = { 5, 3, 1 };
    vector<int> expected = { 1, 3, 5 };

    tournamentSort(array);


    assert(array == expected);
}

// Проверка корректности сортировки
void testCorrectSort() {
    vector<int> array = { 5, 1, 4, 3, 2 };
    vector<int> expected = { 1, 2, 3, 4, 5 };

    tournamentSort(array);

    assert(array == expected);
}

// Вывод результата тестирования
void printTestResult(bool passed) {
    if (passed) {
        cout << "All tests passed!" << endl;
    }
    else {
        cout << "Test failed!" << endl;
    }
}

int main() {
    bool testsPassed = true;

    testSortEmptyArray();
    testSortSingleElement();
    testReverseSort();
    testCorrectSort();

    printTestResult(testsPassed);

    return 0;
}