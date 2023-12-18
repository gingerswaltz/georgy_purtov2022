//@author gingerswaltz

#include <iostream>
#include "Hash-table.h"
#include <cassert>
#include <set>

void testHashTableInsert()
{
    // Создаем экземпляр хэш-таблицы
    HashTable<int> hashTable1(5, SimpleHashFunction);

    // Вставляем элементы в хэш-таблицу
    hashTable1.Insert(10);
    hashTable1.Insert(20);
    hashTable1.Insert(30);

    // Проверяем наличие вставленных элементов
    assert(hashTable1.Find(10) == true);
    assert(hashTable1.Find(20) == true);
    assert(hashTable1.Find(30) == true);

    // Проверяем отсутствие невставленного элемента
    assert(hashTable1.Find(40) == false);

    // Вставляем дубликат элемента
    hashTable1.Insert(10);

    // Проверяем, что дубликат успешно вставлен
    assert(hashTable1.Find(10) == true);

    cout << "[OK] Тест вставки и поиска пройден" << endl;
}

void testHashTableDelete()
{
    // Создаем экземпляр хэш-таблицы
    HashTable<int> hashTable(5, SimpleHashFunction);

    // Вставляем элементы в хэш-таблицу
    hashTable.Insert(10);
    hashTable.Insert(20);
    hashTable.Insert(30);

    // Удаляем элементы из хэш-таблицы
    hashTable.Delete(10);
    hashTable.Delete(20);

    // Проверяем, что удаленные элементы больше не присутствуют
    assert(hashTable.Find(10) == false);
    assert(hashTable.Find(20) == false);
    assert(hashTable.Find(30) == true);

    cout << "[OK] Тест удаления пройден" << endl;
}

void testHashTableClearList()
{
    // Создаем экземпляр хэш-таблицы
    HashTable<int> hashTable(5, SimpleHashFunction);

    // Вставляем элементы в хэш-таблицу
    hashTable.Insert(10);
    hashTable.Insert(20);
    hashTable.Insert(30);

    // Очищаем все блоки хэш-таблицы
    hashTable.ClearList();

    // Проверяем, что все элементы были удалены
    assert(hashTable.Find(10) == false);
    assert(hashTable.Find(20) == false);
    assert(hashTable.Find(30) == false);

    cout << "[OK] Тест очистки пройден" << endl;
}

void testHashTableUpdate()
{
    // Создаем экземпляр хэш-таблицы
    HashTable<int> hashTable(5, SimpleHashFunction);

    // Вставляем элемент в хэш-таблицу
    hashTable.Insert(10);

    // Обновляем значение ключа
    hashTable.Update(10, 20);

    // Проверяем, что старый ключ больше не присутствует, а новый ключ добавлен
    assert(hashTable.Find(10) == false);
    assert(hashTable.Find(20) == true);

    cout << "[OK] Тест обновления пройден" << endl;
}

void TestSearch()
{
    // Создаем экземпляр хэш-таблицы
    HashTable<int> table(10, SimpleHashFunction); // Пример с типом int и хэш-функцией SimpleHashFunction

    // Вставляем элементы в таблицу
    table.Insert(5);
    table.Insert(15);
    table.Insert(25);

    // Проверяем операцию поиска
    assert(table.Find(5) == true);   // Проверяем, есть ли элемент 5 в таблице
    assert(table.Find(15) == true);  // Проверяем, есть ли элемент 15 в таблице
    assert(table.Find(25) == true);  // Проверяем, есть ли элемент 25 в таблице
    assert(table.Find(10) == false); // Проверяем отсутствующий элемент 10 в таблице

    std::cout << "[OK] Тест поиска пройден" << std::endl;
}

void testEmptyHashTable()
{
    // Создаем пустую хэш-таблицу
    HashTable<int> emptyTable(5, SimpleHashFunction);

    // Проверяем, что пустая таблица действительно пуста
    assert(emptyTable.Find(10) == false);
    assert(emptyTable.Find(20) == false);
    assert(emptyTable.Find(30) == false);

    // Попытка удалить элементы из пустой таблицы
    emptyTable.Delete(10);
    emptyTable.Delete(20);
    emptyTable.Delete(30);

    // Проверяем, что удаление из пустой таблицы не вызвало ошибок
    assert(emptyTable.Find(10) == false);
    assert(emptyTable.Find(20) == false);
    assert(emptyTable.Find(30) == false);

    // Попытка обновить ключи в пустой таблице
    emptyTable.Update(10, 20);

    // Проверяем, что обновление в пустой таблице также не вызвало ошибок
    assert(emptyTable.Find(10) == false);
    assert(emptyTable.Find(20) == false);

    cout << "[OK] Тест работы с пустой таблицей пройден" << endl;
}

void testDeleteNonExistingKeys()
{
    // Создаем хэш-таблицу
    HashTable<int> table(5, SimpleHashFunction);

    // Вставляем элементы в таблицу
    table.Insert(10);
    table.Insert(20);
    table.Insert(30);

    // Удаляем ключи, которые не были вставлены
    table.Delete(40);
    table.Delete(50);

    // Проверяем, что удаление несуществующих ключей не влияет на другие элементы таблицы
    assert(table.Find(10) == true);
    assert(table.Find(20) == true);
    assert(table.Find(30) == true);

    cout << "[OK] Тест на удаление несуществующих ключей пройден" << endl;
}

void testEmptyHashTable2()
{
    // Создаем пустую хэш-таблицу с размером 1
    HashTable<int> emptyTable(1, SimpleHashFunction);

    // Проверяем, что таблица пустая
    assert(emptyTable.Find(10) == false);
    assert(emptyTable.Find(20) == false);
    assert(emptyTable.Find(30) == false);

    // Попытка удалить из пустой таблицы
    emptyTable.Delete(10);
    emptyTable.Delete(20);
    emptyTable.Delete(30);

    // Проверяем, что удаление из пустой таблицы не вызывает ошибок
    assert(emptyTable.Find(10) == false);
    assert(emptyTable.Find(20) == false);
    assert(emptyTable.Find(30) == false);

    // Попытка обновить в пустой таблице
    emptyTable.Update(10, 20);

    // Проверяем, что обновление в пустой таблице также не вызывает ошибок
    assert(emptyTable.Find(10) == false);
    assert(emptyTable.Find(20) == false);

    cout << "[OK] Тест на граничный случай (пустая таблица) пройден" << endl;
}

int main()
{
    testHashTableInsert();
    testHashTableDelete();
    testHashTableClearList();
    testHashTableUpdate();
    TestSearch();
    testEmptyHashTable();
    testDeleteNonExistingKeys();
    testEmptyHashTable2();
    return 0;
}