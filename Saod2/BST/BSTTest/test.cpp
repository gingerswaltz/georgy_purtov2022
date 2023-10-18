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

TEST(BinarySearchTreeTest, BreadthFirstSearch) {
    // ������� ������ � ��������� ��� �������
    BinarySearchTree<int> tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(3);
    tree.insert(7);
    tree.insert(12);
    tree.insert(20);

    // ��������� ����� ������ � ������
    std::vector<Node<int>*> result = tree.breadthFirstSearch();

    // ���������, ��� ���������� ����� � ���������� ������������� ����������
    EXPECT_EQ(result.size(), 7);

    // ��������� �������� ����� � ����������
    // ��������� ������� ����� ��� ������ � ������: 10, 5, 15, 3, 7, 12, 20
    EXPECT_EQ(result[0]->data, 10);
    EXPECT_EQ(result[1]->data, 5);
    EXPECT_EQ(result[2]->data, 15);
    EXPECT_EQ(result[3]->data, 3);
    EXPECT_EQ(result[4]->data, 7);
    EXPECT_EQ(result[5]->data, 12);
    EXPECT_EQ(result[6]->data, 20);
}
