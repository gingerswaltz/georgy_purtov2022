//@author: gingerswaltz
#include <iostream>
#include <string>
#include "Dictionary.h"
#include <cassert>

int TestInsert()
{
    Dictionary<int, std::string> dict;

    // Тест 1: Вставка элементов
    dict.insert(1, "One");
    dict.insert(2, "Two");
    dict.insert(3, "Three");
    dict.insert(4, "Four");

    // Проверяем размер словаря
    assert(dict.getSize() == 4);

    // Тест 2: Попытка вставки существующего ключа (должна проигнорироваться)
    dict.insert(2, "NewTwo");

    // Проверяем, что значение не изменилось
    std::string value;
    assert(dict.search(2, value));
    assert(value == "Two");

    // Тест 3: Проверка вставки и удаления
    dict.insert(5, "Five");
    dict.remove(4);

    // Проверяем размер и отсутствие удаленного ключа
    assert(dict.getSize() == 4);
    assert(!dict.search(4, value));

    // Тест 4: Поиск элемента
    assert(dict.search(3, value));
    assert(value == "Three");

    std::cout << "[OK] Insert tests passed" << std::endl;

    return 0;
}

// поиск всех элементов
int TestFind()
{
    Dictionary<int, std::string> dict;

    // Вставляем элементы для тестирования
    dict.insert(1, "One");
    dict.insert(2, "Two");
    dict.insert(3, "Three");
    dict.insert(4, "Four");

    // Тест 1: Поиск существующего ключа
    std::string value;
    assert(dict.search(2, value));
    assert(value == "Two");

    // Тест 2: Поиск несуществующего ключа
    assert(!dict.search(5, value));

    // Тест 3: Поиск существующего ключа с пустым значением
    assert(dict.search(4, value));
    assert(value == "Four");

    std::cout << "[OK] Find tests passed" << std::endl;

    return 0;
}


//todo удаление из пустого словаря, удалить все элементы
int DeleteTest()
{
    Dictionary<int, std::string> dict;

    // Вставляем элементы для тестирования
    dict.insert(1, "One");
    dict.insert(2, "Two");
    dict.insert(3, "Three");
    dict.insert(4, "Four");

    // Тест 1: Успешное удаление существующего ключа
    dict.remove(2);

    // Проверяем, что ключ больше не существует
    std::string value;
    assert(!dict.search(2, value));

    // Проверяем размер словаря после удаления
    assert(dict.getSize() == 3);

    // Тест 2: Попытка удаления несуществующего ключа
    dict.remove(5);

    // Проверяем, что размер словаря остался неизменным
    assert(dict.getSize() == 3);

    std::cout << "[OK] Find tests passed" << std::endl;

    return 0;
}
 // todo  в целом пустой словарь
int main()
{
    TestInsert();
    DeleteTest();
    TestFind();

    return 0;
}
