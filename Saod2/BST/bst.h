// @author: gingerswaltz
#pragma once
#include "..//ConsoleApplication1/ConsoleApplication1/binary_tree.h"
// класс Бинарного Дерева Поиска
template<typename T>
class BinarySearchTree {
private:
    Node<T>* root;



public:
    BinarySearchTree() {
        root = nullptr;
    }

    // Конструктор с параметром
    BinarySearchTree(T initialValue) {
        root = newNode(initialValue); // Создаем корневой узел с начальным значением
    }

    // Конструктор копирования
    BinarySearchTree(const BinarySearchTree& other) {
        // Вызываем функцию копирования дерева и присваиваем корневой узел
        root = copyTree(other.root);
    }

    // Конструктор перемещения
    BinarySearchTree(BinarySearchTree&& other) noexcept {
        // Перемещаем указатель на корневой узел из другого объекта
        root = other.root;

        // Устанавливаем указатель в другом объекте на nullptr,
        // чтобы избежать освобождения памяти при разрушении другого объекта
        other.root = nullptr;
    }

    // Конструктор с параметром, принимающий указатель на корневой узел
    BinarySearchTree(Node<T>* rootNode) {
        root = rootNode;
    }

    // Оператор присваивания перемещением
    BinarySearchTree& operator=(BinarySearchTree&& other) noexcept {
        if (this == &other) {
            return *this; // Проверка на самоприсваивание
        }

        // Освобождаем ресурсы текущего объекта
        deleteTree(root);

        // Перемещаем указатель на корневой узел из другого объекта
        root = other.root;

        // Устанавливаем указатель в другом объекте на nullptr,
        // чтобы избежать освобождения памяти при разрушении другого объекта
        other.root = nullptr;

        return *this;
    }

    // Оператор присваивания копированием
    BinarySearchTree& operator=(const BinarySearchTree& other) {
        if (this == &other) {
            return *this; // Проверка на самоприсваивание
        }

        // Освобождаем ресурсы текущего объекта
        deleteTree(root);

        // Копируем дерево из другого объекта
        root = copyTree(other.root);

        return *this;
    }


    ~BinarySearchTree() {
        // Вызываем функцию удаления дерева для освобождения памяти
        deleteTree(root);
    }

    // Метод для вставки значения в BST
    void insert(T value) {
        root = ::insert(root, value);
    }

    // Метод для поиска значения в BST
    bool search(T value) {
        Node<T>* result = ::search(root, value);
        return (result != nullptr);
    }


    // Метод для вывода дерева
    void print() {
        printTree(root);
    }

    // Метод для вычисления глубины дерева
    int depth() {
        return findTreeDepth(root);
    }

    // Метод для удаления значения
    void remove(T value) {
        root = deleteNodeWithSuccessor(root, value);
    }


    // Метод для обхода дерева в ширину и возврата узлов
    std::vector<Node<T>*> breadthFirstSearch() {
        return ::breadthFirstSearch(root);
    }


};
