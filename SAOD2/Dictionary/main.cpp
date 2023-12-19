#include <iostream>
#include <string>
#include "Dictionary.h"

int main() {
    // Создание экземпляра словаря с ключами типа std::string и значениями типа int
    Dictionary<std::string, int> myDictionary;

    // Вставка элементов
    myDictionary.insert("apple", 5);
    myDictionary.insert("banana", 8);
    myDictionary.insert("cherry", 3);

    // Поиск элемента
    int value;
    if (myDictionary.search("banana", value)) {
        std::cout << "Значение 'banana': " << value << std::endl;
    } else {
        std::cout << "'banana' не найден" << std::endl;
    }

    // Удаление элемента
    myDictionary.remove("apple");

    // Поиск удаленного элемента
    if (myDictionary.search("apple", value)) {
        std::cout << "Значение 'apple': " << value << std::endl;
    } else {
        std::cout << "'apple' не найден" << std::endl;
    }


    // Создаем экземпляр словаря
    Dictionary<std::string, int> myDictionary1;

    // Добавляем несколько элементов
    myDictionary1.insert("apple", 1);
    myDictionary1.insert("banana", 2);
    myDictionary1.insert("cherry", 3);
   // assert(myDictionary1.getSize()==3);
    // Печатаем содержимое словаря
    std::cout << "Содержимое словаря:" << std::endl;
    myDictionary1.print();
   
    return 0;




}
