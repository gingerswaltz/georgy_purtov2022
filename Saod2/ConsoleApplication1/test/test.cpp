#include "pch.h"
#include "../ConsoleApplication1/binary_tree.h"
#include <iostream>
#include <vector>
#include "gtest/gtest.h" // Подключите библиотеку Google Test


TEST(BinaryTreeTest, BalancedTree) {
    // Создаем сбалансированное дерево
    Node<int> root;
    root.data = 1;
    root.left = new Node<int>();
    root.right = new Node<int>();
    root.left->data = 2;
    root.right->data = 3;

    // Проверяем корректность дерева
    EXPECT_EQ(root.data, 1);
    EXPECT_EQ(root.left->data, 2);
    EXPECT_EQ(root.right->data, 3);

    // Освобождаем память
    delete root.left;
    delete root.right;
}

TEST(BinaryTreeTest, EmptyTree) {
    // Создаем пустое дерево (указатели на nullptr)
    Node<int>* root = nullptr;

    // Проверяем, что дерево пусто
    EXPECT_EQ(root, nullptr);
}

TEST(BinaryTreeTest, DegenerateTree) {
    // Создаем вырожденное дерево
    Node<int> root;
    root.data = 1;
    root.left = new Node<int>();
    root.left->data = 2;

    // Проверяем корректность дерева
    EXPECT_EQ(root.data, 1);
    EXPECT_EQ(root.left->data, 2);

    // Освобождаем память
    delete root.left;
}

// Тестирование traversePreOrder на сбалансированном дереве
TEST(TraversePreOrderTest, BalancedTree) {
    Node<int>* root = newNode(1);
    root->left = newNode(2);
    root->right = newNode(3);
    root->left->left = newNode(4);
    root->left->right = newNode(5);

    testing::internal::CaptureStdout(); // Захват вывода в консоль

    traversePreOrder(root);

    std::string output = testing::internal::GetCapturedStdout(); // Получение захваченного вывода

    EXPECT_EQ(output, " 1 2 4 5 3"); // Проверка, что вывод соответствует ожидаемому порядку
    delete root; // Освобождение памяти
}

// Тестирование traversePreOrder на пустом дереве
TEST(TraversePreOrderTest, EmptyTree) {
    Node<int>* root = nullptr;

    testing::internal::CaptureStdout();

    traversePreOrder(root);

    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, ""); // Проверка, что вывод пуст, так как дерево пусто
}

// Тестирование traversePreOrder на вырожденном дереве
TEST(TraversePreOrderTest, DegenerateTree) {
    Node<int>* root = newNode(1);
    root->left = newNode(2);
    root->left->left = newNode(3);

    testing::internal::CaptureStdout();

    traversePreOrder(root);

    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, " 1 2 3"); // Проверка, что вывод соответствует ожидаемому порядку
    delete root;
}

// Тестирование traverseInOrder на сбалансированном дереве
TEST(TraverseInOrderTest, BalancedTree) {
    Node<int>* root = newNode(2);
    root->left = newNode(1);
    root->right = newNode(3);

    testing::internal::CaptureStdout();

    traverseInOrder(root);

    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, " 1 2 3"); // Проверка, что вывод соответствует ожидаемому порядку
    delete root;
}

// Тестирование traverseInOrder на пустом дереве
TEST(TraverseInOrderTest, EmptyTree) {
    Node<int>* root = nullptr;

    testing::internal::CaptureStdout();

    traverseInOrder(root);

    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, ""); // Проверка, что вывод пуст, так как дерево пусто
}

// Тестирование traverseInOrder на вырожденном дереве
TEST(TraverseInOrderTest, DegenerateTree) {
    Node<int>* root = newNode(1);
    root->left = newNode(2);
    root->left->left = newNode(3);

    testing::internal::CaptureStdout();

    traverseInOrder(root);

    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, " 3 2 1"); // Проверка, что вывод соответствует ожидаемому порядку
    delete root;
}

// Тестирование traversePostOrder на сбалансированном дереве
TEST(TraversePostOrderTest, BalancedTree) {
    Node<int>* root = newNode(2);
    root->left = newNode(1);
    root->right = newNode(3);

    testing::internal::CaptureStdout();

    traversePostOrder(root);

    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, " 1 3 2"); // Проверка, что вывод соответствует ожидаемому порядку
    delete root;
}

// Тестирование traversePostOrder на пустом дереве
TEST(TraversePostOrderTest, EmptyTree) {
    Node<int>* root = nullptr;

    testing::internal::CaptureStdout();

    traversePostOrder(root);

    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, ""); // Проверка, что вывод пуст, так как дерево пусто
}

// Тестирование traversePostOrder на вырожденном дереве
TEST(TraversePostOrderTest, DegenerateTree) {
    Node<int>* root = newNode(1);
    root->left = newNode(2);
    root->left->left = newNode(3);

    testing::internal::CaptureStdout();

    traversePostOrder(root);

    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, " 3 2 1"); // Проверка, что вывод соответствует ожидаемому порядку
    delete root;
}


// Тестирование search на сбалансированном дереве
TEST(SearchTest, BalancedTree) {
    Node<int>* root = newNode(2);
    root->left = newNode(1);
    root->right = newNode(3);

    Node<int>* result = search(root, 2);

    EXPECT_EQ(result->data, 2); // Проверка, что найден корректный узел
    delete root;
}

// Тестирование search на пустом дереве
TEST(SearchTest, EmptyTree) {
    Node<int>* root = nullptr;

    Node<int>* result = search(root, 42);

    EXPECT_EQ(result, nullptr); // Проверка, что результат равен nullptr, так как дерево пусто
}

// Тестирование search на вырожденном дереве
TEST(SearchTest, DegenerateTree) {
    Node<int>* root = newNode(1);
    root->right = newNode(2);
    root->right->right = newNode(3);
    Node<int>* result = search(root, 2);

    EXPECT_EQ(result->data, 2); // Проверка, что найден корректный узел
    delete root;
}

TEST(TreeToVectorTest, DegenerateTree) {
    // Создаем вырожденное дерево: 1 -> 2 -> 3
    Node<int>* root = newNode(1);
    root->right = newNode(2);
    root->right->right = newNode(3);

    std::vector<int> result;
    treeToVector(root, result);

    // Ожидаем, что элементы будут добавлены в вектор в порядке LNR
    std::vector<int> expected = { 1, 2, 3 };

    EXPECT_EQ(result, expected);

    delete root;
}

TEST(DeleteNodeWithSuccessorTest, BalancedTree) {
    // Создаем сбалансированное дерево
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

    // Удаляем узел со значением 3
    root = deleteNodeWithSuccessor(root, 3);


    std::vector<int> result;
    treeToVector(root, result);

    std::vector<int> expected = { 2, 4, 5, 8, 9 };
    EXPECT_EQ(result, expected);

    delete(root);
}

TEST(DeleteNodeWithSuccessorTest, EmptyTree) {
    Node<int>* root = nullptr;

    // Удаляем узел со значением 42 из пустого дерева
    root = deleteNodeWithSuccessor(root, 42);

    // Ожидаем, что дерево останется пустым
    EXPECT_EQ(root, nullptr);
}

TEST(DeleteNodeWithSuccessorTest, DegenerateTree) {
    // Создаем вырожденное дерево: 1 -> 2 -> 3
    Node<int>* root = newNode(1);
    root->right = newNode(2);
    root->right->right = newNode(3);

    // Удаляем узел со значением 2
    root = deleteNodeWithSuccessor(root, 2);

    // Ожидаем, что после удаления дерево станет следующим:
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
    // Создаем сбалансированное дерево
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

    EXPECT_EQ(depth, 3); // Ожидаемая глубина для сбалансированного дерева
    delete root;
}

TEST(FindTreeDepthTest, EmptyTree) {
    Node<int>* root = nullptr;

    int depth = findTreeDepth(root);

    EXPECT_EQ(depth, 0); // Ожидаемая глубина для пустого дерева
}

TEST(FindTreeDepthTest, DegenerateTree) {
    // Создаем вырожденное дерево
    //   1
    //    \
    //     2
    //      \
    //       3
    Node<int>* root = newNode(1);
    root->right = newNode(2);
    root->right->right = newNode(3);

    int depth = findTreeDepth(root);

    EXPECT_EQ(depth, 3); // Ожидаемая глубина для вырожденного дерева
    delete root;
}

TEST(ApplyFunctionTest, BalancedTree) {
    // Создаем сбалансированное дерево
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

    // Применяем функцию возведения в квадрат ко всем элементам
    applyFunction(root, square);


    // Ожидаемые значения после применения функции
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

    // Применяем функцию к пустому дереву
    applyFunction(root, square);

    // Ничего не должно измениться
    EXPECT_EQ(root, nullptr);
}

TEST(ApplyFunctionTest, DegenerateTree) {
    // Создаем вырожденное дерево
    //   1
    //    \
    //     2
    //      \
    //       3
    Node<int>* root = newNode(1);
    root->right = newNode(2);
    root->right->right = newNode(3);

    // Применяем функцию возведения в квадрат ко всем элементам
    applyFunction(root, square);

    // Ожидаем, что все элементы в дереве будут возведены в квадрат
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

    // Проверка оператора равенства
    EXPECT_EQ(it1, it2);

    // Перемещаем it1 к следующему элементу
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

    // Проверка оператора неравенства
    EXPECT_FALSE(it1 != it2);

    // Перемещаем it1 к следующему элементу
    ++it1;
    EXPECT_TRUE(it1 != it2);
}


TEST(BinaryTreeIteratorTest, IteratorCustomTest) {
    // Создаем бинарное дерево
    Node<int>* root = newNode(5);
    root->left = newNode(3);
    root->right = newNode(8);
    root->left->left = newNode(2);
    root->left->right = newNode(4);
    root->right->left = newNode(7);
    root->right->right = newNode(9);

    // Создаем итератор начиная с корня
    BinaryTreeIterator<int> it(root);

    // Создаем ожидаемый порядок значений в дереве
        std::vector<int> expected = { 5, 3, 2, 4, 8, 7, 9 };

    // Проверяем, что итератор возвращает значения в правильном порядке
    for (int value : expected) {
        ASSERT_EQ(value, *it);
        ++it;
    }
}


