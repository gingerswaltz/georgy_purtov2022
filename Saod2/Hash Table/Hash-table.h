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

    vector<LinkedList<T>> buckets; // Хэш-таблица - вектор связанных списков

    unsigned long (*hashFunction)(T key); // Указатель на хэш-функцию

    int elementCount; // Текущее количество элементов в хэш-таблице

public:
    /**
     * Конструктор для создания хэш-таблицы.
     *
     * @param nbuckets Количество блоков (buckets) в хэш-таблице. Это число определяет
     *                 размер хэш-таблицы и влияет на эффективность хеширования
     *                 и разрешения коллизий.
     * @param hashf Указатель на функцию, которая будет использоваться для генерации
     *              хэш-значений из ключей. Эта функция должна быть эффективной и
     *              обеспечивать равномерное распределение хэш-значений.
     *
     * Инициализирует хэш-таблицу с заданным числом блоков и функцией хеширования.
     * Таблица изначально не содержит элементов (elementCount инициализируется как 0).
     * Размер вектора buckets устанавливается равным nbuckets, что определяет
     * количество слотов в хэш-таблице.
     */
    HashTable<T>(int nbuckets, unsigned long (*hashf)(T key))
        : numBuckets(nbuckets), hashFunction(hashf), elementCount(0)
    {
        buckets.resize(numBuckets);
    }

    // Вставка элемента в хэш-таблицу
    void Insert(const T &key)
    {
        unsigned long hashValue = hashFunction(key);
        int bucketIndex = hashValue % numBuckets; // Вычисление индекса блоков
        buckets[bucketIndex].insert(key);         // Вставка элемента в блок
        elementCount++;                           // Увеличиваем счетчик элементов
    }

    // Поиск элемента в хэш-таблице
    bool Find(const T &key)
    {
        unsigned long hashValue = hashFunction(key);
        int bucketIndex = hashValue % numBuckets; // Вычисление индекса блоков
        return buckets[bucketIndex].search(key);  // Поиск элемента в блоке
    }

    // Удаление элемента из хэш-таблицы
    void Delete(const T &key)
    {
        unsigned long hashValue = hashFunction(key);
        int bucketIndex = hashValue % numBuckets; // Вычисление индекса блоков
        buckets[bucketIndex].remove(key);         // Удаление элемента из блока
        size--;
        elementCount--;
    }

    // Очистка всех блоков хэш-таблицы
    void ClearList()
    {
        for (int i = 0; i < numBuckets; ++i)
        {
            buckets[i].clear();
        }
        elementCount = 0;
    }

    // Обновление значения ключа в хэш-таблице
    void Update(const T &oldKey, const T &newKey)
    {
        unsigned long oldHashValue = hashFunction(oldKey);
        int oldBucketIndex = oldHashValue % numBuckets; // Вычисление индекса старого блока

        unsigned long newHashValue = hashFunction(newKey);
        int newBucketIndex = newHashValue % numBuckets; // Вычисление индекса нового блока

        if (oldBucketIndex == newBucketIndex)
        {
            buckets[oldBucketIndex].update(oldKey, newKey); // Обновление значения ключа в одном блоке
        }
        else
        {
            buckets[oldBucketIndex].remove(oldKey); // Удаление старого ключа из старого блока
            buckets[newBucketIndex].insert(newKey); // Вставка нового ключа в новый блок
        }
    }

    // Вывод хэш-таблицы
    void PrintTable()
    {
        for (int i = 0; i < numBuckets; ++i)
        {
            cout << "Блок " << i << ": ";
            buckets[i].print();
            cout << endl;
        }
    }

    // Геттр общего количества слотов (buckets) в хэш-таблице
    int getSize() const
    {
        return numBuckets;
    }

    // Геттер количества элементов
    void getSize()
    {
        return elementCount;
    }
};

unsigned long SimpleHashFunction(int key)
{
    key *= key;

    // Сдвиг вправо используется для получения "средней" части бинарного представления квадрата ключа.
    key >>= 11;
    return static_cast<unsigned int>(key) % 1024;
}
