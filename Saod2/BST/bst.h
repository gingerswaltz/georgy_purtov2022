// @author: gingerswaltz
#pragma once
#include "../ConsoleApplication1/ConsoleApplication1/binary_tree.h"
// класс Бинарного Дерева Поиска
class BinarySearchTree {
private:
    BinaryTree binaryTree;  // Используем класс BinaryTree внутри BinarySearchTree

public:
    // Конструктор по умолчанию
    BinarySearchTree() : binaryTree() {}

    // Конструктор копирования
    BinarySearchTree(const BinarySearchTree& other) : binaryTree(other.binaryTree) {}

    // Оператор присваивания
    BinarySearchTree& operator=(const BinarySearchTree& other) {
        if (this == &other) {
            return *this;
        }

        binaryTree = other.binaryTree;
        return *this;
    }

    // Конструктор перемещения
    BinarySearchTree(BinarySearchTree&& other) noexcept : binaryTree(std::move(other.binaryTree)) {}

    // Оператор перемещения
    BinarySearchTree& operator=(BinarySearchTree&& other) noexcept {
        if (this == &other) {
            return *this;
        }

        binaryTree = std::move(other.binaryTree);
        return *this;
    }



    // Метод для вставки значения в дерево
    void insert(int value) {
        binaryTree.insert(value);
    }

    // Метод для поиска значения в дереве
    bool search(int value) {
        return binaryTree.search(value);
    }

    // Метод для создания глубокой копии дерева
    BinarySearchTree CopyTree() {
        BinarySearchTree newTree;
        newTree.binaryTree = binaryTree.CopyTree();
        return newTree;
    }

    // Метод для вычисления глубины дерева
    int depth() {
        return binaryTree.depth();
    }

    // Метод для обхода дерева в ширину
    void BreadthFirstSearch(std::function<void(int)> callback) {
        binaryTree.BreadthFirstSearch(callback);
    }
};
