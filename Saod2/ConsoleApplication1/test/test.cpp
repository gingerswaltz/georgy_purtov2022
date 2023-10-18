#include "pch.h"
#include "../ConsoleApplication1/binary_tree.h"
#include <iostream>
#include <vector>
#include "gtest/gtest.h" // ���������� ���������� Google Test


TEST(BinaryTreeTest, BalancedTree) {
    // ������� ���������������� ������
    Node<int> root;
    root.data = 1;
    root.left = new Node<int>();
    root.right = new Node<int>();
    root.left->data = 2;
    root.right->data = 3;

    // ��������� ������������ ������
    EXPECT_EQ(root.data, 1);
    EXPECT_EQ(root.left->data, 2);
    EXPECT_EQ(root.right->data, 3);

    // ����������� ������
    delete root.left;
    delete root.right;
}

TEST(BinaryTreeTest, EmptyTree) {
    // ������� ������ ������ (��������� �� nullptr)
    Node<int>* root = nullptr;

    // ���������, ��� ������ �����
    EXPECT_EQ(root, nullptr);
}

TEST(BinaryTreeTest, DegenerateTree) {
    // ������� ����������� ������
    Node<int> root;
    root.data = 1;
    root.left = new Node<int>();
    root.left->data = 2;

    // ��������� ������������ ������
    EXPECT_EQ(root.data, 1);
    EXPECT_EQ(root.left->data, 2);

    // ����������� ������
    delete root.left;
}

// ������������ traversePreOrder �� ���������������� ������
TEST(TraversePreOrderTest, BalancedTree) {
    Node<int>* root = newNode(1);
    root->left = newNode(2);
    root->right = newNode(3);
    root->left->left = newNode(4);
    root->left->right = newNode(5);

    testing::internal::CaptureStdout(); // ������ ������ � �������

    traversePreOrder(root);

    std::string output = testing::internal::GetCapturedStdout(); // ��������� ������������ ������

    EXPECT_EQ(output, " 1 2 4 5 3"); // ��������, ��� ����� ������������� ���������� �������
    delete root; // ������������ ������
}

// ������������ traversePreOrder �� ������ ������
TEST(TraversePreOrderTest, EmptyTree) {
    Node<int>* root = nullptr;

    testing::internal::CaptureStdout();

    traversePreOrder(root);

    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, ""); // ��������, ��� ����� ����, ��� ��� ������ �����
}

// ������������ traversePreOrder �� ����������� ������
TEST(TraversePreOrderTest, DegenerateTree) {
    Node<int>* root = newNode(1);
    root->left = newNode(2);
    root->left->left = newNode(3);

    testing::internal::CaptureStdout();

    traversePreOrder(root);

    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, " 1 2 3"); // ��������, ��� ����� ������������� ���������� �������
    delete root;
}

// ������������ traverseInOrder �� ���������������� ������
TEST(TraverseInOrderTest, BalancedTree) {
    Node<int>* root = newNode(2);
    root->left = newNode(1);
    root->right = newNode(3);

    testing::internal::CaptureStdout();

    traverseInOrder(root);

    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, " 1 2 3"); // ��������, ��� ����� ������������� ���������� �������
    delete root;
}

// ������������ traverseInOrder �� ������ ������
TEST(TraverseInOrderTest, EmptyTree) {
    Node<int>* root = nullptr;

    testing::internal::CaptureStdout();

    traverseInOrder(root);

    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, ""); // ��������, ��� ����� ����, ��� ��� ������ �����
}

// ������������ traverseInOrder �� ����������� ������
TEST(TraverseInOrderTest, DegenerateTree) {
    Node<int>* root = newNode(1);
    root->left = newNode(2);
    root->left->left = newNode(3);

    testing::internal::CaptureStdout();

    traverseInOrder(root);

    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, " 3 2 1"); // ��������, ��� ����� ������������� ���������� �������
    delete root;
}

// ������������ traversePostOrder �� ���������������� ������
TEST(TraversePostOrderTest, BalancedTree) {
    Node<int>* root = newNode(2);
    root->left = newNode(1);
    root->right = newNode(3);

    testing::internal::CaptureStdout();

    traversePostOrder(root);

    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, " 1 3 2"); // ��������, ��� ����� ������������� ���������� �������
    delete root;
}

// ������������ traversePostOrder �� ������ ������
TEST(TraversePostOrderTest, EmptyTree) {
    Node<int>* root = nullptr;

    testing::internal::CaptureStdout();

    traversePostOrder(root);

    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, ""); // ��������, ��� ����� ����, ��� ��� ������ �����
}

// ������������ traversePostOrder �� ����������� ������
TEST(TraversePostOrderTest, DegenerateTree) {
    Node<int>* root = newNode(1);
    root->left = newNode(2);
    root->left->left = newNode(3);

    testing::internal::CaptureStdout();

    traversePostOrder(root);

    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, " 3 2 1"); // ��������, ��� ����� ������������� ���������� �������
    delete root;
}


// ������������ search �� ���������������� ������
TEST(SearchTest, BalancedTree) {
    Node<int>* root = newNode(2);
    root->left = newNode(1);
    root->right = newNode(3);

    Node<int>* result = search(root, 2);

    EXPECT_EQ(result->data, 2); // ��������, ��� ������ ���������� ����
    delete root;
}

// ������������ search �� ������ ������
TEST(SearchTest, EmptyTree) {
    Node<int>* root = nullptr;

    Node<int>* result = search(root, 42);

    EXPECT_EQ(result, nullptr); // ��������, ��� ��������� ����� nullptr, ��� ��� ������ �����
}

// ������������ search �� ����������� ������
TEST(SearchTest, DegenerateTree) {
    Node<int>* root = newNode(1);
    root->right = newNode(2);
    root->right->right = newNode(3);
    Node<int>* result = search(root, 2);

    EXPECT_EQ(result->data, 2); // ��������, ��� ������ ���������� ����
    delete root;
}

TEST(TreeToVectorTest, DegenerateTree) {
    // ������� ����������� ������: 1 -> 2 -> 3
    Node<int>* root = newNode(1);
    root->right = newNode(2);
    root->right->right = newNode(3);

    std::vector<int> result;
    treeToVector(root, result);

    // �������, ��� �������� ����� ��������� � ������ � ������� LNR
    std::vector<int> expected = { 1, 2, 3 };

    EXPECT_EQ(result, expected);

    delete root;
}

TEST(DeleteNodeWithSuccessorTest, BalancedTree) {
    // ������� ���������������� ������
    //       5
    //      / \
    //     3   8
    //    / \   \
    //   2   4   9
    Node<int>* root = newNode(5);
    root->left = newNode(3);
    root->right = newNode(8);
    root->left->left = newNode(2);
    root->left->right = newNode(4);
    root->right->right = newNode(9);

    // ������� ���� �� ��������� 3
    root = deleteNodeWithSuccessor(root, 3);


    std::vector<int> result;
    treeToVector(root, result);

    std::vector<int> expected = { 2, 4, 5, 8, 9 };
    EXPECT_EQ(result, expected);

    delete(root);
}

TEST(DeleteNodeWithSuccessorTest, EmptyTree) {
    Node<int>* root = nullptr;

    // ������� ���� �� ��������� 42 �� ������� ������
    root = deleteNodeWithSuccessor(root, 42);

    // �������, ��� ������ ��������� ������
    EXPECT_EQ(root, nullptr);
}

TEST(DeleteNodeWithSuccessorTest, DegenerateTree) {
    // ������� ����������� ������: 1 -> 2 -> 3
    Node<int>* root = newNode(1);
    root->right = newNode(2);
    root->right->right = newNode(3);

    // ������� ���� �� ��������� 2
    root = deleteNodeWithSuccessor(root, 2);

    // �������, ��� ����� �������� ������ ������ ���������:
    //       1
    //        \
    //         3

    std::vector<int> result;
    treeToVector(root, result);

    std::vector<int> expected = { 1, 3 };
    EXPECT_EQ(result, expected);

    delete(root);
}
TEST(FindTreeDepthTest, BalancedTree) {
    // ������� ���������������� ������
    //       5
    //      / \
    //     3   8
    //    / \   \
    //   2   4   9
    Node<int>* root = newNode(5);
    root->left = newNode(3);
    root->right = newNode(8);
    root->left->left = newNode(2);
    root->left->right = newNode(4);
    root->right->right = newNode(9);

    int depth = findTreeDepth(root);

    EXPECT_EQ(depth, 3); // ��������� ������� ��� ����������������� ������
    delete root;
}

TEST(FindTreeDepthTest, EmptyTree) {
    Node<int>* root = nullptr;

    int depth = findTreeDepth(root);

    EXPECT_EQ(depth, 0); // ��������� ������� ��� ������� ������
}

TEST(FindTreeDepthTest, DegenerateTree) {
    // ������� ����������� ������
    //   1
    //    \
    //     2
    //      \
    //       3
    Node<int>* root = newNode(1);
    root->right = newNode(2);
    root->right->right = newNode(3);

    int depth = findTreeDepth(root);

    EXPECT_EQ(depth, 3); // ��������� ������� ��� ������������ ������
    delete root;
}

TEST(ApplyFunctionTest, BalancedTree) {
    // ������� ���������������� ������
    //       5
    //      / \
    //     3   8
    //    / \   \
    //   2   4   9
    Node<int>* root = newNode(5);
    root->left = newNode(3);
    root->right = newNode(8);
    root->left->left = newNode(2);
    root->left->right = newNode(4);
    root->right->right = newNode(9);

    // ��������� ������� ���������� � ������� �� ���� ���������
    applyFunction(root, square);


    // ��������� �������� ����� ���������� �������
    int expected[] = { 4, 9, 16, 25, 64, 81 };
    int i = 0;
    std::vector<int> result;
    treeToVector(root, result);
    for (int value : result) {
        EXPECT_EQ(value, expected[i++]);
    }

    delete root;
}





TEST(ApplyFunctionTest, EmptyTree) {
    Node<int>* root = nullptr;

    // ��������� ������� � ������� ������
    applyFunction(root, square);

    // ������ �� ������ ����������
    EXPECT_EQ(root, nullptr);
}

TEST(ApplyFunctionTest, DegenerateTree) {
    // ������� ����������� ������
    //   1
    //    \
    //     2
    //      \
    //       3
    Node<int>* root = newNode(1);
    root->right = newNode(2);
    root->right->right = newNode(3);

    // ��������� ������� ���������� � ������� �� ���� ���������
    applyFunction(root, square);

    // �������, ��� ��� �������� � ������ ����� ��������� � �������
    std::vector<int> expected = { 1, 4, 9 };
    std::vector<int> result;
    treeToVector(root, result);
    EXPECT_EQ(result, expected);

    delete root;
}



TEST(BinaryTreeIteratorTest, IteratorEquality) {
    Node<int> root;
    root.data = 1;
    root.left = new Node<int>();
    root.left->data = 2;

    BinaryTreeIterator<int> it1(&root);
    BinaryTreeIterator<int> it2(&root);

    // �������� ��������� ���������
    EXPECT_EQ(it1, it2);

    // ���������� it1 � ���������� ��������
    ++it1;
    EXPECT_NE(it1, it2);
}

TEST(BinaryTreeIteratorTest, IteratorInequality) {
    Node<int> root;
    root.data = 1;
    root.left = new Node<int>();
    root.left->data = 2;

    BinaryTreeIterator<int> it1(&root);
    BinaryTreeIterator<int> it2(&root);

    // �������� ��������� �����������
    EXPECT_FALSE(it1 != it2);

    // ���������� it1 � ���������� ��������
    ++it1;
    EXPECT_TRUE(it1 != it2);
}


TEST(BinaryTreeIteratorTest, IteratorCustomTest) {
    // ������� �������� ������
    Node<int>* root = newNode(5);
    root->left = newNode(3);
    root->right = newNode(8);
    root->left->left = newNode(2);
    root->left->right = newNode(4);
    root->right->left = newNode(7);
    root->right->right = newNode(9);

    // ������� �������� ������� � �����
    BinaryTreeIterator<int> it(root);

    // ������� ��������� ������� �������� � ������
        std::vector<int> expected = { 5, 3, 2, 4, 8, 7, 9 };

    // ���������, ��� �������� ���������� �������� � ���������� �������
    for (int value : expected) {
        ASSERT_EQ(value, *it);
        ++it;
    }
}


