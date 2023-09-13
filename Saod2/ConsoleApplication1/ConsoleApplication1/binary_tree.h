#pragma once
#include <iostream>

// шаблонный класс структуры Дерева
template<typename T>
struct Node {
    T data;
    struct Node* left;
    struct Node* right;

    Node() {
        left = nullptr;
        right = nullptr;
    }

    //todo: Node(...)

};

// шаблонный конструктор узла дерева
template<typename T>
struct Node<T>* newNode(T data) {
    struct Node<T>* node = new Node<T>;

    node->data = data;

    node->left = nullptr;
    node->right = nullptr;
    return node;
}

// вывод дерева в порядке главный узел, левая ветка, правая ветка
template<typename T>
void traversePreOrder(Node<T>* temp) {
    if (temp != nullptr) {
        std::cout << " " << temp->data;
        traversePreOrder(temp->left);
        traversePreOrder(temp->right);
    }
}

// вывод дерева в порядке левая ветка, главный узел, правая ветка
template<typename T>
void traverseInOrder(Node<T>* temp) {
    if (temp != nullptr) {
        traverseInOrder(temp->left);
        std::cout << " " << temp->data;
        traverseInOrder(temp->right);
    }
}

// вывод дерева в порядке левая ветка, правая ветка, главный узел
template<typename T>
void traversePostOrder(Node<T>* temp) {
    if (temp != nullptr) {
        traversePostOrder(temp->left);
        traversePostOrder(temp->right);
        std::cout << " " << temp->data;
    }
}

// удаление узла дерева
template<typename T>
void deleteNode(Node<T>* temp) {
    if (temp != nullptr) {
        deleteNode(temp->left);
        deleteNode(temp->right);
        free(temp);
    }
}


template<typename T>
int countNodes(Node<T>* root) {
    if (root == nullptr) {
        // Если дерево пусто (корень равен nullptr), возвращаем 0.
        return 0;
    }
    else {
        // Иначе, рекурсивно считаем количество узлов в левом и правом поддеревьях,
        // а затем добавляем 1 для текущего узла (корня).
        return 1 + countNodes(root->left) + countNodes(root->right);
    }
}

///         1
///        / \       
///       2   3
///      /   / \
///     4   9  15



