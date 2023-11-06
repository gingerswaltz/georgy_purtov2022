// author: gingerswaltz
#include "../ConsoleApplication1/ConsoleApplication1/binary_tree.h"

void testTraverseIterator() {
    BinaryTree tree;

    tree.insert(50);
    tree.insert(30);
    tree.insert(70);
    tree.insert(20);
    tree.insert(40);

    // Тест обхода LNR (in-order)
    int lnr_expected[] = { 20, 30, 40, 50, 70 };
    int lnr_index = 0;
    tree.traverseLNR( [&](int value) {
        assert(value == lnr_expected[lnr_index]);
        lnr_index++;
        });

    // Тест обхода RNL (reverse in-order)
    int rnl_expected[] = { 70, 50, 40, 30, 20 };
    int rnl_index = 0;
    tree.traverseRNL([&](int value) {
        assert(value == rnl_expected[rnl_index]);
        rnl_index++;
        });

  
    std::cout << "Traverse test passed\n";

}

void testBinaryTree() {
    BinaryTree tree;

    tree.insert(50);
    tree.insert(30);
    tree.insert(70);
    tree.insert(20);
    tree.insert(40);

    BinaryTree::Iterator it = tree.iterator();

    // Тест 1: Проверка обхода элементов дерева
    int expected[] = { 20, 30, 40, 50, 70 };
    int index = 0;
    while (it.hasNext()) {
        assert(it.next() == expected[index]);
        index++;
    }

    std::cout << "Iterator test passed\n";
}

// деревья - пустые вырожденные и 1 эл
int main() {
    testBinaryTree();
    testTraverseIterator();
    return 0;
}