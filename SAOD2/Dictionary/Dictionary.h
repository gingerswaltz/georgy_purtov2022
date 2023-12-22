//@author: gingerswaltz
#include <iostream>
#include "../AVL/AVL_tree.h"

// Шаблонный класс словаря на основе AVL дерева
template <class Key, class Value>
class Dictionary
{
private:
    // Структура для хранения пары ключ-значение
    struct KeyValuePair
    {
        Key key;
        Value value;

        // Конструктор класса KeyValuePair, создающий объект пары ключ-значение.
        // Принимает ключ и значение в качестве аргументов и инициализирует члены данных key и value.
        // Аргументы:
        //   key: Ключ элемента пары.
        //   value: Значение элемента пары.
        KeyValuePair(const Key &key, const Value &value) : key(key), value(value) {}

        // Добавляем конструктор по умолчанию
        KeyValuePair() = default;

        // Перегруженный оператор сравнения "<" для сравнения двух объектов KeyValuePair по ключу.
        // Возвращает true, если ключ текущего объекта меньше ключа другого объекта, иначе false.
        bool operator<(const KeyValuePair &other) const
        {
            return key < other.key;
        }

        // Перегруженный оператор сравнения ">" для сравнения двух объектов KeyValuePair по ключу.
        // Возвращает true, если ключ текущего объекта больше ключа другого объекта, иначе false.
        bool operator>(const KeyValuePair &other) const
        {
            return key > other.key;
        }

        // Перегруженный оператор сравнения "==" для сравнения двух объектов KeyValuePair по ключу.
        // Возвращает true, если ключи текущего и другого объектов равны, иначе false.
        bool operator==(const KeyValuePair &other) const
        {
            return key == other.key;
        }

        // Перегруженный оператор вывода в поток для объекта KeyValuePair.
        // Позволяет вывести объект KeyValuePair в поток, используя формат "ключ: значение".
        friend std::ostream &operator<<(std::ostream &os, const KeyValuePair &kvp)
        {
            os << kvp.key << ": " << kvp.value;
            return os;
        }
    };

    // Используем AVL дерево для хранения пар ключ-значение
    AVLTree<KeyValuePair> tree;

    size_t size; // Член класса для отслеживания размера словаря

    // Вспомогательная функция для получения значения по ключу
    Value getValue(const Key &key)
    {
        return getValueRecursive(tree.getRoot(), key); // начинаем поиск с корня
    }


    // todo: документация к исключениям 
    // Рекурсивная функция для обхода дерева и поиска значения
    Value getValueRecursive(TreeNode<KeyValuePair> *node, const Key &key)
    {
        if (node == nullptr)
        {
            throw std::runtime_error("Key not found");
        }
        if (key < node->data.key)
        {
            return getValueRecursive(node->left, key);
        }
        else if (key > node->data.key)
        {
            return getValueRecursive(node->right, key);
        }
        else
        {
            return node->data.value; // Найденный ключ, возвращаем значение
        }
    }

    void printInOrder(TreeNode<KeyValuePair> *node) const
    {
        if (node != nullptr)
        {
            printInOrder(node->Left());     // Первым делом обходим левое поддерево
            std::cout << node->data << " "; // Затем печатаем данные текущего узла
            printInOrder(node->Right());    // Наконец, обходим правое поддерево
        }
    }

public:
    Dictionary() : size(0) {} // Инициализация размера в конструкторе

    // Вставка пары ключ-значение
    void insert(const Key &key, const Value &value)
    {
        KeyValuePair kvp(key, value);
        if (!tree.search(kvp))
        { // Добавляем элемент только если его нет
            tree.insert(kvp);
            ++size; // Увеличиваем размер
        }
    }

    // Удаление по ключу
    void remove(const Key &key)
    {
        KeyValuePair kvp(key, Value());
        if (tree.search(kvp))
        { // Удаляем элемент только если он существует
            tree.remove(kvp);
            --size; // Уменьшаем размер
        }
    }


    // поиск по ключу, не зная значения
    // Поиск значения по ключу
    bool search(const Key &key, Value &value)
    {
        KeyValuePair kvp(key, Value()); // Создаем временный объект для поиска

        if (tree.search(kvp))
        {
            value = getValue(key); // Предположим, что у нас есть функция getValue
            return true;
        }
        return false;
    }

    // Метод печати словаря
    void print() const
    {
        printInOrder(tree.getRoot());
        std::cout << std::endl;
    }

    size_t getSize() const
    {
        return size; // Возвращаем текущий размер словаря
    }
};