#include "..//ConsoleApplication1/ConsoleApplication1/binary_tree.h"

template<typename T>
class BinarySearchTree {
private:
    Node<T>* root;

    // Приватный метод для вставки узла в BST
    Node<T>* insertNode(Node<T>* current, T value) {
        if (current == nullptr) {
            return newNode(value); // Создаем новый узел, если текущий узел равен nullptr
        }

        // Рекурсивно вставляем узел в правое или левое поддерево
        if (value > current->data) {
            current->right = insertNode(current->right, value);
        }
        else {
            current->left = insertNode(current->left, value);
        }

        return current;
    }

    // Приватный метод для поиска узла в BST
    Node<T>* searchNode(Node<T>* current, T value) {
        if (current == nullptr || current->data == value) {
            return current;
        }

        if (value > current->data) {
            return searchNode(current->right, value);
        }

        return searchNode(current->left, value);
    }

public:
    BinarySearchTree() {
        root = nullptr;
    }

    // Метод для вставки значения в BST
    void insert(T value) {
        root = insertNode(root, value);
    }

    // Метод для поиска значения в BST
    bool search(T value) {
        Node<T>* result = searchNode(root, value);
        return (result != nullptr);
    }

    // Другие методы, такие как удаление узла и другие операции, могут быть добавлены здесь

    // Метод для вывода дерева
    void print() {
        printTree(root);
    }

    // Метод для вычисления глубины дерева
    int depth() {
        return findTreeDepth(root);
    }
};

int main() {
    BinarySearchTree<int> bst;
    bst.insert(10);
    bst.insert(5);
    bst.insert(15);

    bst.print(); // Вывод дерева

    bool found = bst.search(5);
    if (found) {
        std::cout << "Found 5 in BST." << std::endl;
    }
    else {
        std::cout << "5 not found in BST." << std::endl;
    }

    return 0;
}
