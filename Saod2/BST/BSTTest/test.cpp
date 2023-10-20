#include "pch.h"
#include "../bst.h"

TEST(BinarySearchTreeTest, ConstructorWithInitialValue) {
    // Создаем дерево с начальным значением
    BinarySearchTree<int> tree(10);

    // Проверяем, что дерево содержит начальное значение
    EXPECT_TRUE(tree.search(10));
    EXPECT_EQ(tree.depth(), 1);
}

TEST(BinarySearchTreeTest, CopyConstructorBalancedTree) {
    // Создаем сбалансированное дерево
    BinarySearchTree<int> originalTree;
    originalTree.insert(10);
    originalTree.insert(5);
    originalTree.insert(15);

    // Копируем дерево
    BinarySearchTree<int> copiedTree(originalTree);

    // Проверяем, что копирование прошло успешно
    EXPECT_TRUE(copiedTree.search(10));
    EXPECT_TRUE(copiedTree.search(5));
    EXPECT_TRUE(copiedTree.search(15));
    EXPECT_EQ(copiedTree.depth(), 2);
}

TEST(BinarySearchTreeTest, CopyConstructorDegenerateTree) {
    // Создаем вырожденное дерево
    BinarySearchTree<int> originalTree;
    originalTree.insert(10);
    originalTree.insert(5);
    originalTree.insert(3);

    // Копируем дерево
    BinarySearchTree<int> copiedTree(originalTree);

    // Проверяем, что копирование прошло успешно
    EXPECT_TRUE(copiedTree.search(10));
    EXPECT_TRUE(copiedTree.search(5));
    EXPECT_TRUE(copiedTree.search(3));
    EXPECT_EQ(copiedTree.depth(), 3);
}

TEST(BinarySearchTreeTest, MoveAssignmentOperator) {
    // Создаем дерево и наполняем его данными
    BinarySearchTree<int> originalTree;
    originalTree.insert(10);
    originalTree.insert(5);
    originalTree.insert(15);

    // Создаем новое пустое дерево и перемещаем данные из оригинального дерева в него
    BinarySearchTree<int> movedTree;
    movedTree = std::move(originalTree);

    // Проверяем, что перемещение прошло успешно и оригинальное дерево теперь пусто
    EXPECT_EQ(originalTree.depth(), 0);
    EXPECT_EQ(movedTree.depth(), 2); // Глубина нового дерева

    // Проверяем, что новое дерево содержит вставленные данные
    EXPECT_TRUE(movedTree.search(10));
    EXPECT_TRUE(movedTree.search(5));
    EXPECT_TRUE(movedTree.search(15));
}

TEST(BreadthFirstSearchTest, BalancedTree) {
    BinarySearchTree<int> bst;
    bst.insert(10);
    bst.insert(5);
    bst.insert(15);
    bst.insert(3);
    bst.insert(7);
    bst.insert(12);
    bst.insert(18);

    std::vector<Node<int>*> result = bst.breadthFirstSearch();

    ASSERT_EQ(result.size(), 7);
    EXPECT_EQ(result[0]->data, 10);
    EXPECT_EQ(result[1]->data, 5);
    EXPECT_EQ(result[2]->data, 15);
    EXPECT_EQ(result[3]->data, 3);
    EXPECT_EQ(result[4]->data, 7);
    EXPECT_EQ(result[5]->data, 12);
    EXPECT_EQ(result[6]->data, 18);
}

TEST(BreadthFirstSearchTest, DegenerateTree) {
    BinarySearchTree<int> bst;
    bst.insert(1);
    bst.insert(2);
    bst.insert(3);
    bst.insert(4);
    bst.insert(5);

    std::vector<Node<int>*> result = bst.breadthFirstSearch();

    ASSERT_EQ(result.size(), 5);
    for (int i = 0; i < 5; ++i) {
        EXPECT_EQ(result[i]->data, i + 1);
    }
}

TEST(BreadthFirstSearchTest, EmptyTree) {
    BinarySearchTree<int> bst;

    std::vector<Node<int>*> result = bst.breadthFirstSearch();

    EXPECT_TRUE(result.empty());
}

TEST(CopyConstructorTest, BalancedTree) {
    BinarySearchTree<int> originalTree;
    originalTree.insert(10);
    originalTree.insert(5);
    originalTree.insert(15);
    originalTree.insert(3);
    originalTree.insert(7);
    originalTree.insert(12);
    originalTree.insert(18);

    BinarySearchTree<int> copiedTree(originalTree);

    // Проверяем, что глубины деревьев совпадают
    EXPECT_EQ(originalTree.depth(), copiedTree.depth());

    // Проверяем, что деревья одинаковы с точки зрения структуры и значений узлов
    std::vector<Node<int>*> originalNodes = originalTree.breadthFirstSearch();
    std::vector<Node<int>*> copiedNodes = copiedTree.breadthFirstSearch();

    ASSERT_EQ(originalNodes.size(), copiedNodes.size());
    for (size_t i = 0; i < originalNodes.size(); ++i) {
        EXPECT_EQ(originalNodes[i]->data, copiedNodes[i]->data);
    }
}

TEST(CopyConstructorTest, DegenerateTree) {
    BinarySearchTree<int> originalTree;
    originalTree.insert(1);
    originalTree.insert(2);
    originalTree.insert(3);
    originalTree.insert(4);
    originalTree.insert(5);

    BinarySearchTree<int> copiedTree(originalTree);

    // Проверяем, что глубины деревьев совпадают
    EXPECT_EQ(originalTree.depth(), copiedTree.depth());

    // Проверяем, что деревья одинаковы с точки зрения структуры и значений узлов
    std::vector<Node<int>*> originalNodes = originalTree.breadthFirstSearch();
    std::vector<Node<int>*> copiedNodes = copiedTree.breadthFirstSearch();

    ASSERT_EQ(originalNodes.size(), copiedNodes.size());
    for (size_t i = 0; i < originalNodes.size(); ++i) {
        EXPECT_EQ(originalNodes[i]->data, copiedNodes[i]->data);
    }
}

TEST(CopyConstructorTest, EmptyTree) {
    BinarySearchTree<int> originalTree;
    BinarySearchTree<int> copiedTree(originalTree);

    // Проверяем, что глубины деревьев совпадают (должны быть 0)
    EXPECT_EQ(originalTree.depth(), copiedTree.depth());

    // Проверяем, что деревья одинаковы с точки зрения структуры
    std::vector<Node<int>*> originalNodes = originalTree.breadthFirstSearch();
    std::vector<Node<int>*> copiedNodes = copiedTree.breadthFirstSearch();

    EXPECT_EQ(originalNodes.size(), 0);
    EXPECT_EQ(copiedNodes.size(), 0);
}



TEST(MoveConstructorTest, BalancedTree) {
    BinarySearchTree<int> originalTree;
    originalTree.insert(10);
    originalTree.insert(5);
    originalTree.insert(15);
    originalTree.insert(3);
    originalTree.insert(7);
    originalTree.insert(12);
    originalTree.insert(18);

    BinarySearchTree<int> movedTree(originalTree);

    // Проверяем, что глубина нового дерева совпадает с исходным
    EXPECT_EQ(originalTree.depth(), movedTree.depth());

   
}

TEST(MoveConstructorTest, DegenerateTree) {
    BinarySearchTree<int> originalTree;
    originalTree.insert(1);
    originalTree.insert(2);
    originalTree.insert(3);
    originalTree.insert(4);
    originalTree.insert(5);

    BinarySearchTree<int> movedTree(originalTree);

    // Проверяем, что глубина нового дерева совпадает с исходным
    EXPECT_EQ(originalTree.depth(), movedTree.depth());

    
}

TEST(MoveConstructorTest, EmptyTree) {
    BinarySearchTree<int> originalTree;
    BinarySearchTree<int> movedTree(originalTree);

    // Проверяем, что глубина нового дерева совпадает с исходным (должна быть 0)
    EXPECT_EQ(originalTree.depth(), movedTree.depth());

}

TEST(BinarySearchTreeMoveConstructorTest, BalancedTree) {
    BinarySearchTree<int> balancedTree;
    balancedTree.insert(10);
    balancedTree.insert(5);
    balancedTree.insert(15);

    BinarySearchTree<int> movedTree(std::move(balancedTree));

    // Проверяем, что глубина нового дерева совпадает с исходным (должна быть 2)
    EXPECT_EQ(balancedTree.depth(), 0);
    EXPECT_EQ(movedTree.depth(), 2);
}

TEST(BinarySearchTreeMoveConstructorTest, DegenerateTree) {
    BinarySearchTree<int> degenerateTree;
    for (int i = 1; i <= 10; ++i) {
        degenerateTree.insert(i);
    }

    BinarySearchTree<int> movedTree(std::move(degenerateTree));

    // Проверяем, что глубина нового дерева совпадает с исходным (должна быть 10)
    EXPECT_EQ(degenerateTree.depth(), 0);
    EXPECT_EQ(movedTree.depth(), 10);
}

TEST(BinarySearchTreeMoveConstructorTest, EmptyTree) {
    BinarySearchTree<int> emptyTree;

    BinarySearchTree<int> movedTree(std::move(emptyTree));

    // Проверяем, что глубина нового дерева совпадает с исходным (должна быть 0)
    EXPECT_EQ(emptyTree.depth(), 0);
    EXPECT_EQ(movedTree.depth(), 0);
}

TEST(BinarySearchTreeCopyAssignmentTest, BalancedTree) {
    BinarySearchTree<int> balancedTree;
    balancedTree.insert(10);
    balancedTree.insert(5);
    balancedTree.insert(15);

    BinarySearchTree<int> copiedTree;
    copiedTree = balancedTree;

    // Проверяем, что глубина нового дерева совпадает с исходным (должна быть 2)
    EXPECT_EQ(copiedTree.depth(), 2);
}

TEST(BinarySearchTreeCopyAssignmentTest, DegenerateTree) {
    BinarySearchTree<int> degenerateTree;
    for (int i = 1; i <= 10; ++i) {
        degenerateTree.insert(i);
    }

    BinarySearchTree<int> copiedTree;
    copiedTree = degenerateTree;

    // Проверяем, что глубина нового дерева совпадает с исходным (должна быть 10)
    EXPECT_EQ(copiedTree.depth(), 10);
}

TEST(BinarySearchTreeCopyAssignmentTest, EmptyTree) {
    BinarySearchTree<int> emptyTree;

    BinarySearchTree<int> copiedTree;
    copiedTree = emptyTree;

    // Проверяем, что глубина нового дерева совпадает с исходным (должна быть 0)
    EXPECT_EQ(copiedTree.depth(), 0);
}
