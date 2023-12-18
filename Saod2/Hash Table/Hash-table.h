//@author gingerswaltz
#include <iostream>
#include <vector>
#include "LinkedList.h"
using namespace std;

// Шаблонный класс хэщ-таблицы
template <class T>
class HashTable
{
private:
    int numBuckets; // Число блоков

    vector <LinkedList<T>> buckets; // Хэш-таблица - вектор связанных списков

    unsigned long (*hashFunction)(T key); // Указатель на хэш-функцию

public:

    // Конструктор класса HashTable
    HashTable<T>(int nbuckets, unsigned long (*hashf)(T key))
        : numBuckets(nbuckets), hashFunction(hashf) {
        buckets.resize(numBuckets); // Инициализация вектора блока
    }

    // Вставка элемента в хэш-таблицу
    void Insert(const T& key) {
        unsigned long hashValue = hashFunction(key);
        int bucketIndex = hashValue % numBuckets; // Вычисление индекса блоков
        buckets[bucketIndex].insert(key); // Вставка элемента в блок
    }

    // Поиск элемента в хэш-таблице
    bool Find(const T& key) {
        unsigned long hashValue = hashFunction(key);
        int bucketIndex = hashValue % numBuckets; // Вычисление индекса блоков
        return buckets[bucketIndex].search(key); // Поиск элемента в блоке
    }

    // Удаление элемента из хэш-таблицы
    void Delete(const T& key) {
        unsigned long hashValue = hashFunction(key);
        int bucketIndex = hashValue % numBuckets; // Вычисление индекса блоков
        buckets[bucketIndex].remove(key); // Удаление элемента из блока
    }

    // Очистка всех блоков хэш-таблицы
    void ClearList() {
        for (int i = 0; i < numBuckets; ++i) {
            buckets[i].clear();
        }
    }

    // Обновление значения ключа в хэш-таблице
    void Update(const T& oldKey, const T& newKey) {
        unsigned long oldHashValue = hashFunction(oldKey);
        int oldBucketIndex = oldHashValue % numBuckets; // Вычисление индекса старого блока

        unsigned long newHashValue = hashFunction(newKey);
        int newBucketIndex = newHashValue % numBuckets; // Вычисление индекса нового блока

        if (oldBucketIndex == newBucketIndex) {
            buckets[oldBucketIndex].update(oldKey, newKey); // Обновление значения ключа в одном блоке
        }
        else {
            buckets[oldBucketIndex].remove(oldKey); // Удаление старого ключа из старого блока
            buckets[newBucketIndex].insert(newKey); // Вставка нового ключа в новый блок
        }
    }

    // Вывод хэш-таблицы
    void PrintTable() {
        for (int i = 0; i < numBuckets; ++i) {
            cout << "Блок " << i << ": ";
            buckets[i].print();
            cout << endl;
        }
    }




};

// Хэш - функция IntHashFunction использует простое число(например, 31) 
// в качестве коэффициента для преобразования целочисленного ключа в уникальное значение.
// Она основана на операции взятия остатка от деления целого числа на это простое число.

unsigned long SimpleHashFunction(int key) {
    // Простое число, рекомендуемое для хэширования
    const unsigned int prime = 31;

    // Хэширование с помощью деления на простое число и взятия остатка
    // static_cast используется для преобразования 
    // типа int в unsigned long для корректной работы с хэшированием
    return static_cast<unsigned long>(key) % prime;
}
