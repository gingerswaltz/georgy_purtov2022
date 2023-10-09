#include "..//ConsoleApplication1/ConsoleApplication1/binary_tree.h"

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


    // конструктор с указателем на узел todo и оператор присваивания и удаление узла и перемещения

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

int main() {
    BinarySearchTree<int> bst;
    bst.insert(10);
    bst.insert(5);
    bst.insert(15);

    bst.print(); // Вывод дерева

    // Создаем копию дерева
    BinarySearchTree<int> copiedBST(bst);

    // Вывод копии дерева
    std::cout << "\nCopied Tree:" << std::endl;
    copiedBST.print();

    // Вызов метода поиска значения
    bool found = bst.search(5);
    if (found) {
        std::cout << "Found 5 in BST." << std::endl;
    }
    else {
        std::cout << "5 not found in BST." << std::endl;
    }

    found = bst.search(7);
    if (found) {
        std::cout << "Found 7 in BST." << std::endl;
    }
    else {
        std::cout << "7 not found in BST." << std::endl;
    }

    // Вызываем метод breadthFirstSearch и сохраняем результат в векторе nodes
    std::vector<Node<int>*> nodes = bst.breadthFirstSearch();

    // Выводим значения узлов, обойденных в ширину
    for (Node<int>* node : nodes) {
        std::cout << node->data << " ";
    }
    std::cout << std::endl;


    return 0;
}
