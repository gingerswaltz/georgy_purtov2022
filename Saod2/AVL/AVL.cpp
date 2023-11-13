// author:gingerswaltz
#include <iostream>
#include "AVL_tree.h"

// Функция для тестирования балансировки дерева
void testBalance()
{
    AVLTree<int> tree;
    tree.insert(10);
    tree.insert(20);
    tree.insert(30); // Эта вставка должна вызвать балансировку
    // Проверка баланса дерева
    assert(tree.isBalanced());

    std::cout << "[OK] Тест балансировки пройден." << std::endl;
}

void testInsertAndBalance()
{
    AVLTree<int> tree;

    // Вставляем элементы
    tree.insert(30);
    tree.insert(20);
    tree.insert(40);
    tree.insert(10); // Эта вставка должна вызвать балансировку

    // Проверка баланса дерева
    assert(tree.isBalanced());

    std::cout << "[OK] Тест вставки и балансировки пройден." << std::endl;
}

void testDeleteAndBalance()
{
    AVLTree<int> tree;

    // Вставляем элементы
    tree.insert(30);
    tree.insert(20);
    tree.insert(40);
    tree.insert(10);

    // Удаляем элемент и проверяем балансировку
    tree.remove(20); // Это удаление должно вызвать балансировку

    // Проверяем, что удаленный элемент больше не существует и дерево остается сбалансированным
    assert(!tree.search(20));
    assert(tree.isBalanced());

    std::cout << "[OK] Тест удаления и балансировки пройден." << std::endl;
}

// todo: вырожденные и 1эл
int main()
{

    testBalance();
    testInsertAndBalance();
    testDeleteAndBalance();

    return 0;
}
