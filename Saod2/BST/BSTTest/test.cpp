#include "pch.h"
#include "../bst.h"

TEST(BinarySearchTreeTest, ConstructorWithInitialValue) {
    // ������� ������ � ��������� ���������
    BinarySearchTree<int> tree(10);

    // ���������, ��� ������ �������� ��������� ��������
    EXPECT_TRUE(tree.search(10));
    EXPECT_EQ(tree.depth(), 1);
}

TEST(BinarySearchTreeTest, CopyConstructorBalancedTree) {
    // ������� ���������������� ������
    BinarySearchTree<int> originalTree;
    originalTree.insert(10);
    originalTree.insert(5);
    originalTree.insert(15);

    // �������� ������
    BinarySearchTree<int> copiedTree(originalTree);

    // ���������, ��� ����������� ������ �������
    EXPECT_TRUE(copiedTree.search(10));
    EXPECT_TRUE(copiedTree.search(5));
    EXPECT_TRUE(copiedTree.search(15));
    EXPECT_EQ(copiedTree.depth(), 2);
}

TEST(BinarySearchTreeTest, CopyConstructorDegenerateTree) {
    // ������� ����������� ������
    BinarySearchTree<int> originalTree;
    originalTree.insert(10);
    originalTree.insert(5);
    originalTree.insert(3);

    // �������� ������
    BinarySearchTree<int> copiedTree(originalTree);

    // ���������, ��� ����������� ������ �������
    EXPECT_TRUE(copiedTree.search(10));
    EXPECT_TRUE(copiedTree.search(5));
    EXPECT_TRUE(copiedTree.search(3));
    EXPECT_EQ(copiedTree.depth(), 3);
}

TEST(BinarySearchTreeTest, MoveAssignmentOperator) {
    // ������� ������ � ��������� ��� �������
    BinarySearchTree<int> originalTree;
    originalTree.insert(10);
    originalTree.insert(5);
    originalTree.insert(15);

    // ������� ����� ������ ������ � ���������� ������ �� ������������� ������ � ����
    BinarySearchTree<int> movedTree;
    movedTree = std::move(originalTree);

    // ���������, ��� ����������� ������ ������� � ������������ ������ ������ �����
    EXPECT_EQ(originalTree.depth(), 0);
    EXPECT_EQ(movedTree.depth(), 2); // ������� ������ ������

    // ���������, ��� ����� ������ �������� ����������� ������
    EXPECT_TRUE(movedTree.search(10));
    EXPECT_TRUE(movedTree.search(5));
    EXPECT_TRUE(movedTree.search(15));
}
