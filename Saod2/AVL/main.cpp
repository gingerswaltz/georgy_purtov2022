#include "AVLTree.h"
#include <cassert>
// Тест на пустое AVL-дерево
void testEmptyAVLTree() {
    AVLTree<int> avl;
    assert(avl.depth() == 0);
    assert(!avl.search(42));
}


int main() {
    AVLTree<int> avl;
    avl.insert(10);
    avl.insert(20);
    avl.insert(5);
    avl.insert(6);
    avl.insert(15);

    std::cout << "AVL Tree after insertions:\n";
    avl.print();

    avl.remove(6);
    avl.remove(20);

    std::cout << "\nAVL Tree after removals:\n";
    avl.print();

    return 0;
}