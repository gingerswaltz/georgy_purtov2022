// author: gingerswaltz

#pragma once
#include <cassert>
#include <stack>
#include <stdexcept>
#include <functional>
#include <iostream>
#include <queue>

// Класс узла бинарного дерева
class TreeNode {
public:
    int data;          // Значение узла
    TreeNode* left;    // Указатель на левого потомка
    TreeNode* right;   // Указатель на правого потомка

    // Конструктор для создания узла с заданным значением
    TreeNode(int val) : data(val), left(nullptr), right(nullptr) {}
};

// Класс бинарного дерева
class BinaryTree {
public:
    TreeNode* root;  // Указатель на корневой узел
    // Вспомогательный метод для создания глубокой копии дерева
    TreeNode* copyTree(TreeNode* node) {
        if (node == nullptr) {
            return nullptr;
        }

        TreeNode* newNode = new TreeNode(node->data);
        newNode->left = copyTree(node->left);
        newNode->right = copyTree(node->right);
        return newNode;
    }

    // Вспомогательный метод для вычисления глубины дерева
    int calculateDepth(TreeNode* node) {
        if (node == nullptr) {
            return 0;
        }

        int leftDepth = calculateDepth(node->left);
        int rightDepth = calculateDepth(node->right);

        return std::max(leftDepth, rightDepth) + 1;
    }
public:
    // Конструктор по умолчанию инициализирует корневой узел как nullptr
    BinaryTree() : root(nullptr) {}

    // Функция для вставки значения в дерево
    void insert(int value) {
        root = insertRec(root, value);
    }

    // Рекурсивная функция для вставки значения
    TreeNode* insertRec(TreeNode* node, int value) {
        // Если дерево пустое, создаем новый узел и возвращаем его
        if (node == nullptr) {
            return new TreeNode(value);
        }

        // Иначе рекурсивно идем влево или вправо, в зависимости от значения
        if (value < node->data) {
            node->left = insertRec(node->left, value);
        }
        else if (value > node->data) {
            node->right = insertRec(node->right, value);
        }

        return node;
    }
     // Метод для создания глубокой копии дерева
    BinaryTree CopyTree() {
        BinaryTree newTree;
        newTree.root = copyTree(root);
        return newTree;
    }

    // Метод для вычисления глубины дерева (максимальной глубины)
    int depth() {
        return calculateDepth(root);
    }

    // Метод для обхода дерева в ширину
    void BreadthFirstSearch(std::function<void(int)> callback) {
        if (root == nullptr) {
            return;
        }

        std::queue<TreeNode*> q;
        q.push(root);

        while (!q.empty()) {
            TreeNode* current = q.front();
            q.pop();

            callback(current->data);

            if (current->left != nullptr) {
                q.push(current->left);
            }

            if (current->right != nullptr) {
                q.push(current->right);
            }
        }
    }

    // Функция для поиска значения в дереве
    bool search(int value) {
        return searchRec(root, value);
    }

    // Рекурсивная функция для поиска значения
    bool searchRec(TreeNode* node, int value) {
        // Если дерево пустое или мы нашли значение, возвращаем true
        if (node == nullptr || node->data == value) {
            return node != nullptr;
        }

        // Рекурсивно идем влево или вправо, в зависимости от значения
        if (value < node->data) {
            return searchRec(node->left, value);
        }
        else {
            return searchRec(node->right, value);
        }
    }

    TreeNode* findMin(TreeNode* p) {
        return (p->left == nullptr) ? p : findMin(p->left);
    }

    TreeNode* removeMin(TreeNode* p) {
        if (p->left == nullptr) {
            return p->right;
        }
        p->left = removeMin(p->left);
        return p;
    }

    TreeNode* remove(TreeNode* p, int value) {
        if (p == nullptr) {
            return nullptr;
        }

        if (value < p->data) {
            p->left = remove(p->left, value);
        } else if (value > p->data) {
            p->right = remove(p->right, value);
        } else {
            TreeNode* left = p->left;
            TreeNode* right = p->right;
            delete p;

            if (right == nullptr) {
                return left;
            }

            TreeNode* min = findMin(right);
            min->right = removeMin(right);
            min->left = left;
            return min;
        }

        return p;
    }

    void destroy(TreeNode* p) {
        if (p != nullptr) {
            destroy(p->left);
            destroy(p->right);
            delete p;
        }
    }

//     // Класс итератора LNR
//     class Iterator {
//     private:
//         std::stack<TreeNode*> stack;

//     public:
//         Iterator(TreeNode* root) {
//             // Инициализируем итератор, помещая все узлы до самого левого в стек
//             while (root != nullptr) {
//                 stack.push(root);
//                 root = root->left;
//             }
//         }

//         // traverse LNR
//         int next() {
//             // Если стек пуст, значит все элементы уже обойдены
//             if (stack.empty()) {
//                 throw std::runtime_error("Итератор завершил обход");
//             }

//             // Получаем значение текущего узла
//             TreeNode* current = stack.top();
//             int value = current->data;

//             // Переходим к правому потомку
//             stack.pop();
//             if (current->right != nullptr) {
//                 current = current->right;
//                 while (current != nullptr) {
//                     stack.push(current);
//                     current = current->left;
//                 }
//             }

//             return value;
//         }
//         // проверка следующего элемента в стеке
//         bool hasNext() const {
//             return !stack.empty();
//         }
//     };

//     // Метод, возвращающий итератор
//     Iterator iterator() {
//         return Iterator(root);
//     }


//     // Обход LNR (in-order) с использованием итератора
//     void traverseLNR(std::function<void(int)> callback) {
//         Iterator it = iterator();
//         while (it.hasNext()) {
//             callback(it.next());
//         }
//     }

//     // Обход RNL (reverse in-order) с использованием итератора
//     void traverseRNL(std::function<void(int)> callback) {
//         std::stack<int> values;
//         Iterator it = iterator();
//         while (it.hasNext()) {
//             values.push(it.next());
//         }
//         while (!values.empty()) {
//             callback(values.top());
//             values.pop();
//         }
//     }
    
//     void traverseNLR(TreeNode* node) {
//         if (node == nullptr) {
//             return;
//         }
//         // Действие (например, вывод значения на экран)
//         std::cout << node->data << " ";
//         traverseNLR(node->left);
//         traverseNLR(node->right);
//     }

// };
};
