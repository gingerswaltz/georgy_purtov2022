#include <iostream>
#include <utility> // для std::pair
#include "../AVL/AVL_tree.h"

template <class Key, class Value>
class Dictionary {
private:
    // Структура для хранения пары ключ-значение
    struct KeyValuePair {
        Key key;
        Value value;

        KeyValuePair(const Key &key, const Value &value) : key(key), value(value) {}
        
        // Добавляем конструктор по умолчанию
        KeyValuePair() = default;

        bool operator<(const KeyValuePair &other) const {
            return key < other.key;
        }

        bool operator>(const KeyValuePair &other) const {
            return key > other.key;
        }

        bool operator==(const KeyValuePair &other) const {
            return key == other.key;
        }

        friend std::ostream& operator<<(std::ostream& os, const KeyValuePair& kvp) {
            os << kvp.key << ": " << kvp.value;
            return os;
        }
    };

    // Используем AVL дерево для хранения пар ключ-значение
    AVLTree<KeyValuePair> tree;
    
    // Вспомогательная функция для получения значения по ключу
    Value getValue(const Key &key) {
        return getValueRecursive(tree.getRoot(), key); // начинаем поиск с корня
    }

    // Рекурсивная функция для обхода дерева и поиска значения
    Value getValueRecursive(TreeNode<KeyValuePair> *node, const Key &key) {
        if (node == nullptr) {
            throw std::runtime_error("Key not found");
        }
        if (key < node->data.key) {
            return getValueRecursive(node->left, key);
        } else if (key > node->data.key) {
            return getValueRecursive(node->right, key);
        } else {
            return node->data.value; // Найденный ключ, возвращаем значение
        }
    }

    void printInOrder(TreeNode<KeyValuePair>* node) const {
        if (node != nullptr) {
            printInOrder(node->Left());   // Первым делом обходим левое поддерево
            std::cout << node->data << " ";  // Затем печатаем данные текущего узла
            printInOrder(node->Right());  // Наконец, обходим правое поддерево
        }
    }
public:
    // Вставка пары ключ-значение
    void insert(const Key &key, const Value &value) {
        KeyValuePair kvp(key, value);
        tree.insert(kvp);
    }

    // Удаление по ключу
    void remove(const Key &key) {
        KeyValuePair kvp(key, Value()); // Создаем временный объект для поиска
        tree.remove(kvp);
    }

    // Поиск значения по ключу
    bool search(const Key &key, Value &value) {
        KeyValuePair kvp(key, Value()); // Создаем временный объект для поиска

        if (tree.search(kvp)) {
            value = getValue(key); // Предположим, что у нас есть функция getValue
            return true;
        }
        return false;
    }

    // Метод печати словаря
    void print() const {
        printInOrder(tree.getRoot());
        std::cout << std::endl;
    }

    // Дополнительные функции могут включать обход дерева, размер словаря и т.д.
};