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



// Функция для тестирования балансировки дерева
void testBalance1()
{
    AVLTree<int> tree;
    tree.insert(10);
    
    // Проверка баланса дерева
    assert(tree.isBalanced());

    std::cout << "[OK] Тест балансировки пройден." << std::endl;
}

void testInsertAndBalance1()
{
    AVLTree<int> tree;

    // Вставляем элементы
    tree.insert(30);
   
    // Проверка баланса дерева
    assert(tree.isBalanced());

    std::cout << "[OK] Тест вставки и балансировки пройден." << std::endl;
}

void testDeleteAndBalance1()
{
    AVLTree<int> tree;

    // Вставляем элементы
    tree.insert(30);
    
    // Удаляем элемент и проверяем балансировку
    tree.remove(20); // Это удаление должно вызвать балансировку

    // Проверяем, что удаленный элемент больше не существует и дерево остается сбалансированным
    assert(!tree.search(20));
    assert(tree.isBalanced());

    std::cout << "[OK] Тест удаления и балансировки пройден." << std::endl;
}


int TestToarr() {
    AVLTree<int> tree;

    // Вставляем элементы в AVL дерево
    tree.insert(10);
    tree.insert(20);
    tree.insert(5);

    // Создаем массив для хранения элементов дерева
    const int expectedSize = 3;
    int expected[expectedSize];

    // Копируем элементы дерева в массив
    int actualSize = tree.addToArr(expected, expectedSize);

    // Проверяем размер и содержимое массива
    assert(actualSize == expectedSize);
    assert(expected[0] == 5);  // Элементы должны быть отсортированы
    assert(expected[1] == 10);
    assert(expected[2] == 20);

    std::cout << "[OK] Тест массива пройден успешно!" << std::endl;
    return 0;
}



int main()
{

    testBalance();
    testInsertAndBalance();
    testDeleteAndBalance();

    testBalance1();
    testInsertAndBalance1();
    testDeleteAndBalance1();
    TestToarr();
    return 0;
}
