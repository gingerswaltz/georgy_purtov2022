#include "bst.h"
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
