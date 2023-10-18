#pragma once
#include <iostream>
#include <stack>
#include <functional>
#include <vector>
#include <queue>
#include "Iterator.h"
// шаблонный класс структуры бинарного Дерева
template<typename T>
struct Node {
    T data;
     Node* left;
     Node* right;

    Node() {
        left = nullptr;
        right = nullptr;
    }

};

// шаблонный конструктор узла дерева
template<typename T>
 Node<T>* newNode(T data) {
    Node<T>* node = new Node<T>;
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
        delete temp;
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


// вывод дерева в виде дерева, обход по LNR
template<typename T>
void printTree(Node<T>* root, int level = 0) {
    if (root == nullptr) {
        return;
    }

    // Рекурсивно обходим левое поддерево
    printTree(root->left, level + 1);

    // Выводим отступ в зависимости от уровня узла
    for (int i = 0; i < level; ++i) {
        std::cout << "    ";
    }

    // Выводим значение узла
    std::cout << root->data << std::endl;

    // Рекурсивно обходим правое поддерево
    printTree(root->right, level + 1);
}



// итеративный алгоритм поиска глубины при помощи стека
template<typename T>
int findTreeDepth(Node<T>* root) {
    if (root == nullptr) {
        return 0; // Для пустого дерева глубина равна 0
    }

    // стек для хранения пар узлов дерева и их уровней в дереве
    std::stack<std::pair<Node<T>*, int> > nodeStack;

    nodeStack.push(std::make_pair(root, 1)); // Корневой узел с уровнем 1

    int maxDepth = 0;
    
    // пока стэк не пуст
    while (!nodeStack.empty()) {
        // текущий узел - первый в стэке
        Node<T>* currentNode = nodeStack.top().first;
        // второй элемент стека (второй узел) - текущая глубина
        int currentDepth = nodeStack.top().second;
        // после обработки удалим этот элемент из стэка
        nodeStack.pop();

        // Обновляем максимальную глубину, если текущая глубина больше
        if (currentDepth > maxDepth) {
            maxDepth = currentDepth;
        }
        // Проверяем поддеревья и обновляем глубину
        if (currentNode->left) {
            nodeStack.push(std::make_pair(currentNode->left, currentDepth + 1));
        }

        if (currentNode->right) {
            nodeStack.push(std::make_pair(currentNode->right, currentDepth + 1));
        }
    }

    return maxDepth;
}

template<typename T>
Node<T>* insert(Node<T>* root, T value) {
    // Если дерево пусто, создаем новый узел и делаем его корневым
    if (root == nullptr) {
        return newNode(value);
    }

    // Рекурсивно вставляем значение в правое поддерево, если оно больше текущего узла
    if (value > root->data) {
        root->right = insert(root->right, value);
    }
    // Или в левое поддерево, если оно меньше или равно текущему узлу
    else {
        root->left = insert(root->left, value);
    }

    return root;
}

template<typename T>
Node<T>* search(Node<T>* root, T value) {
    // Если дерево пусто или текущий узел содержит искомое значение, вернуть текущий узел
    if (root == nullptr || root->data == value) {
        return root;
    }

    // Если искомое значение больше значения текущего узла,
    // рекурсивно искать в правом поддереве
    if (value > root->data) {
        return search(root->right, value);
    }

    // Иначе искать в левом поддереве
    Node<T>* result = search(root->left, value);

    // Если результат поиска в левом поддереве не равен nullptr, значит, значение найдено
    // и мы его возвращаем, иначе возвращаем nullptr
    return (result != nullptr) ? result : nullptr;
}


// Функция для обхода дерева в порядке LNR и добавления элементов в вектор
template<typename T>
void treeToVector(Node<T>* root, std::vector<T>& result) {
    if (root != nullptr) {
        // Рекурсивно обходим левое поддерево
        treeToVector(root->left, result);

        // Добавляем значение текущего узла в вектор
        result.push_back(root->data);

        // Рекурсивно обходим правое поддерево
        treeToVector(root->right, result);
    }
}


// Функция для нахождения преемника узла
template<typename T>
Node<T>* findSuccessor(Node<T>* node) {
    while (node->left != nullptr) {
        node = node->left;
    }
    return node;
}

template<typename T>
Node<T>* deleteNodeWithSuccessor(Node<T>* root, T key) {
    if (root == nullptr) {
        return root; // Если дерево пустое, возвращаем nullptr
    }

    // Рекурсивно ищем узел, который нужно удалить
    if (key < root->data) {
        root->left = deleteNodeWithSuccessor(root->left, key);
    }
    else if (key > root->data) {
        root->right = deleteNodeWithSuccessor(root->right, key);
    }
    else {
        // Узел найден, выполним удаление

        // У случая 1 и 2 (узел без одного или обоих детей), просто удаляем узел
        if (root->left == nullptr) {
            Node<T>* temp = root->right;
            delete root;
            return temp;
        }
        else if (root->right == nullptr) {
            Node<T>* temp = root->left;
            delete root;
            return temp;
        }

        // У случая 3 (узел с двумя детьми) найдем преемника
        Node<T>* successor = findSuccessor(root->right);

        // Заменяем данные текущего узла данными преемника
        root->data = successor->data;

        // Рекурсивно удаляем преемника из правого поддерева
        root->right = deleteNodeWithSuccessor(root->right, successor->data);
    }

    return root;
}

// Функция для обхода дерева и применения функции к каждому элементу
template<typename T>
void applyFunction(Node<T>* root, T(*func)(T)) {
    if (root != nullptr) {
        // Применяем функцию к текущему элементу
        root->data = func(root->data);
        // Рекурсивно обходим левое и правое поддеревья
        applyFunction(root->left, func);
        applyFunction(root->right, func);
    }
}

// Breadth-First Search, алгоритм обхода дерева в ширину
template<typename T>
std::vector<Node<T>*> breadthFirstSearch(Node<T>* root) {
    std::vector<Node<T>*> result;

    if (root == nullptr) {
        return result;
    }

    std::queue<Node<T>*> q;
    q.push(root);

    while (!q.empty()) {
        Node<T>* current = q.front();
        q.pop();

        // Добавляем текущий узел в вектор 
        result.push_back(current);

        // Добавляем дочерние узлы в очередь
        if (current->left != nullptr) {
            q.push(current->left);
        }
        if (current->right != nullptr) {
            q.push(current->right);
        }
    }

    return result;
}

// Алгоритм копирования бинарного дерева
template<typename T>
Node<T>* copyTree(Node<T>* source) {
    if (source == nullptr) {
        return nullptr; // Если исходное дерево пусто, возвращаем nullptr
    }

    // Создаем новый узел с тем же значением
    Node<T>* new_node= newNode(source->data);

    // Рекурсивно копируем левое и правое поддеревья
    new_node->left = copyTree(source->left);
    new_node->right = copyTree(source->right);

    return new_node;
}


template<typename T>
void deleteTree(Node<T>* node) {
    if (node == nullptr) {
        return;
    }

    // Рекурсивно удаляем левое и правое поддерево
    deleteTree(node->left);
    deleteTree(node->right);

    // Удаляем текущий узел
    delete node;
}

// Функция для возведения числа в квадрат
template<typename T>
T square(T x) {
    return x * x;
}

template <typename T>
class BinaryTreeIterator : public Iterator<T> {
public:
    BinaryTreeIterator(Node<T>* start) : current(start) {
        if (current) {
            initializeStack(current);
        }
    }

    T operator*() const override {
        if (current) {
            return current->data;
        }
        else {
            throw std::runtime_error("Dereferencing a nullptr iterator");
        }
    }

    BinaryTreeIterator<T>& operator++() override {
        if (nodeStack.empty()) {
            current = nullptr;
        }
        else {
            current = nodeStack.top();
            nodeStack.pop();
            if (current->right) {
                initializeStack(current->right);
            }
        }
        return *this;
    }

    bool operator==(const Iterator<T>& other) const override {
        const BinaryTreeIterator<T>* otherIterator = dynamic_cast<const BinaryTreeIterator<T>*>(&other);
        if (otherIterator) {
            return current == otherIterator->current;
        }
        return false;
    }

    bool operator!=(const Iterator<T>& other) const override {
        return !(*this == other);
    }

    explicit operator bool() const {
        return current != nullptr;
    }

private:
    Node<T>* current;
    std::stack<Node<T>*> nodeStack;

    void initializeStack(Node<T>* node) {
        while (node) {
            nodeStack.push(node);
            node = node->left;
        }
    }
};
