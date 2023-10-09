#include "pch.h"
#include "../bst.h"

TEST(BinarySearchTreeTest, ConstructorWithInitialValue) {
    // —оздаем дерево с начальным значением
    BinarySearchTree<int> tree(10);

    // ѕровер€ем, что дерево содержит начальное значение
    EXPECT_TRUE(tree.search(10));
    EXPECT_EQ(tree.depth(), 1);
}

TEST(BinarySearchTreeTest, CopyConstructorBalancedTree) {
    // —оздаем сбалансированное дерево
    BinarySearchTree<int> originalTree;
    originalTree.insert(10);
    originalTree.insert(5);
    originalTree.insert(15);

    //  опируем дерево
    BinarySearchTree<int> copiedTree(originalTree);

    // ѕровер€ем, что копирование прошло успешно
    EXPECT_TRUE(copiedTree.search(10));
    EXPECT_TRUE(copiedTree.search(5));
    EXPECT_TRUE(copiedTree.search(15));
    EXPECT_EQ(copiedTree.depth(), 2);
}

TEST(BinarySearchTreeTest, CopyConstructorDegenerateTree) {
    // —оздаем вырожденное дерево
    BinarySearchTree<int> originalTree;
    originalTree.insert(10);
    originalTree.insert(5);
    originalTree.insert(3);

    //  опируем дерево
    BinarySearchTree<int> copiedTree(originalTree);

    // ѕровер€ем, что копирование прошло успешно
    EXPECT_TRUE(copiedTree.search(10));
    EXPECT_TRUE(copiedTree.search(5));
    EXPECT_TRUE(copiedTree.search(3));
    EXPECT_EQ(copiedTree.depth(), 3);
}

TEST(BinarySearchTreeTest, MoveAssignmentOperator) {
    // —оздаем дерево и наполн€ем его данными
    BinarySearchTree<int> originalTree;
    originalTree.insert(10);
    originalTree.insert(5);
    originalTree.insert(15);

    // —оздаем новое пустое дерево и перемещаем данные из оригинального дерева в него
    BinarySearchTree<int> movedTree;
    movedTree = std::move(originalTree);

    // ѕровер€ем, что перемещение прошло успешно и оригинальное дерево теперь пусто
    EXPECT_EQ(originalTree.depth(), 0);
    EXPECT_EQ(movedTree.depth(), 2); // √лубина нового дерева

    // ѕровер€ем, что новое дерево содержит вставленные данные
    EXPECT_TRUE(movedTree.search(10));
    EXPECT_TRUE(movedTree.search(5));
    EXPECT_TRUE(movedTree.search(15));
}
