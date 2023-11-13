#pragma once
///@author gingerswaltz

#include <iostream>
#include <vector>
#include <iomanip>
#include <cassert>
#include <queue>

using namespace std;

// объявление объекта для узла бинарного дерева
template <class T>
struct TreeNode
{
    // указатели левого и правого дочерних узлов
    TreeNode<T> *left;
    TreeNode<T> *right;

    // открытый элемент, допускающий обновление
    T data;

    // конструктор инициализирует поля данных и указателей
    // значение NULL соответствует пустому поддереву
    TreeNode(const T &item, TreeNode<T> *lptr, TreeNode<T> *rptr /*int nodeHeight*/)
    //: data(item), left(lptr), right(rptr)
    {
        data = item;
        left = lptr;
        right = rptr;
    }
    // методы доступа к полям указателей
    TreeNode<T> *Left() const { return left; }
    TreeNode<T> *Right() const { return right; }
    // Виртуальный деструктор
    virtual ~TreeNode() = default;
};

/// Удаление дерева
template <class T>
void DeleteTree(TreeNode<T> *root)
{
    if (root != nullptr)
    {
        return;

        DeleteTree(root->Left());
        DeleteTree(root->Right());

        delete root;
    }
    root = nullptr;
}

/// Удаление одного узла
template <class T>
void DeleteTreeNode(TreeNode<T> *node)
{
    delete node;
}

// промежуток между уровнями
const int indentBlock = 6;
// вставить numпробелов в текущей строке
void IndentBlanks(int num)
{
    for (int i = 0; i < num; i++)
        cout << "  ";
}

// печать дерева боком,используя RNL- прохождение
template <class T>
void PrintTree(TreeNode<T> *node, int level)
{
    // печатать правое дерево узла node, пока он не равет nullptr
    if (node != nullptr)
    {
        // печатать правое поддерево узла node
        PrintTree(node->Right(), level + 1);
        // выровнять текущий уровень и вывести поле данных
        IndentBlanks(indentBlock * level);
        cout << node->data << endl;
        // печатать левое поддерево узла node
        PrintTree(node->Left(), level + 1);
    }
}

// подсчет листьев дерева,т.е узлов, которые не имеют потомков
template <class T>
void CountLeaf(TreeNode<T> *t, int &count)
{
    // использование обратного метода прохождения
    if (t != nullptr)
    {
        CountLeaf(t->Left(), count);  // пройти левое поддерево
        CountLeaf(t->Right(), count); // пройти правое поддерево

        // проверить,является ли данный узел листом
        // если да, то произвести приращение переменной count
        if (t->Left() == nullptr && t->Right() == nullptr)
            count++;
    }
}
// подсчет глубины (уровней) дерева
template <class T>
int Depth(TreeNode<T> *t)
{
    int depthLeft, depthRight, depthValue;
    // если дерево пустое,его глубина=-1
    if (t == nullptr)
    {
        depthValue = -1;
    }
    else
    // обратный метод прохождения
    // вычисление глубины правого и левого поддеревьев
    // возвращение их результирующего
    {
        depthLeft = Depth(t->Left());
        depthRight = Depth(t->Right());
        // тернарный оператор
        // выбирает максимальное между depthLeft и depthRight
        // depthValue = 1 + (depthLeft > depthRight ? depthLeft : depthRight);

        if (depthLeft > depthRight)
        {
            depthValue = 1 + depthLeft;
        }
        else
        {

            depthValue = 1 + depthRight;
        }
    }
    return depthValue;
}

// Рекурсивная вспомогательная функция для удаления узла
template <class T>
TreeNode<T> *deleteNode(TreeNode<T> *node, const T &key)
{
    if (node == nullptr)
    {
        return node;
    }

    if (key < node->data)
    {
        // Продолжаем поиск в левом поддереве
        node->left = deleteNode(node->left, key);
    }
    else if (key > node->data)
    {
        // Продолжаем поиск в правом поддереве
        node->right = deleteNode(node->right, key);
    }
    else
    {
        // Нашли узел, который нужно удалить
        if (node->left == nullptr)
        {
            // У узла есть только правый ребенок или нет детей вовсе
            TreeNode<T> *temp = node->right;
            delete node;
            return temp;
        }
        else if (node->right == nullptr)
        {
            // У узла есть только левый ребенок
            TreeNode<T> *temp = node->left;
            delete node;
            return temp;
        }

        // У узла два ребенка: Получаем самый маленький узел в правом поддереве
        TreeNode<T> *temp = minValueNode(node->right);

        // Копируем данные самого маленького узла в узел, который нужно удалить
        node->data = temp->data;

        // Удаляем самый маленький узел в правом поддереве
        node->right = deleteNode(node->right, temp->data);
    }
    return node;
}
template <class T>
// Функция для поиска узла с минимальным значением (используется в deleteNode)
TreeNode<T> *minValueNode(TreeNode<T> *node)
{
    TreeNode<T> *current = node;
    while (current && current->left != nullptr)
    {
        current = current->left;
    }
    return current;
}

// Функция внесения данных
template <class T>
TreeNode<T> *Add(TreeNode<T> *node, const T &aData)

{
    // Если ветки не существует

    if (node == nullptr)

    { // создадим ее и зададим в нее данные

        return new TreeNode<T>(aData, nullptr, nullptr);
    }

    if (aData < node->data)
    {
        // Рекурсивно вставляем значение в левое поддерево
        node->left = Add(node->left, aData);
    }
    else if (aData > node->data)
    {
        // Рекурсивно вставляем значение в правое поддерево
        node->right = Add(node->right, aData);
    }

    // Если значение уже присутствует в дереве, ничего не делаем

    return node;
}

/// Поиск в бинарном дереве
template <class T>
bool Search(TreeNode<T> *root, const T &data)
{
    if (root == nullptr)
    {
        // Дерево пустое или достигнут конец ветки (лист без значения)
        return false;
    }

    if (data == root->data)
    {
        // Значение найдено в текущем узле
        return true;
    }
    else if (data < root->data)
    {
        // Рекурсивно ищем значение в левом поддереве
        return Search(root->left, data);
    }
    else
    {
        // Рекурсивно ищем значение в правом поддереве
        return Search(root->right, data);
    }
}

/// Добавление в массив
template <class T>
int AddArr(TreeNode<T> *node, T arr[], int i)
{
    if (node == nullptr)
    {
        // Дерево пустое или достигнут конец ветки (лист без значения)
        return i;
    }

    if (node->left != nullptr)
    {
        // Рекурсивно вставляем значение в левое поддерево
        i = AddArr(node->left, arr, i);
    }

    arr[i] = node->data;
    i++;

    if (node->right != nullptr)
    {
        // Рекурсивно вставляем значение в правое поддерево
        i = AddArr(node->right, arr, i);
    }
    return i;
}

// построение бинарного дерева из массива, элементы в котором хранятся след.образом
// ( корень,левый и правый потомки,потомки левого,потомки правого и т.д)
template <class T>
void BinaryTreeFromVector(vector<T> vec)
{
    // Создание корневого узла с первым элементом вектора
    TreeNode<int> *root = new TreeNode<int>(vec.at(0), nullptr, nullptr);
    for (int i = 0; i < vec.size(); i++)
    {
        int left = 2 * i + 1; // Вычисление индекса левого потомка
        int right = left + 1; // Вычисление индекса правого потомка
        if (left < vec.size())
            AddNode(root, vec.at(i));
        if (right < vec.size())
            AddNode(root, vec.at(i));
    }
    PrintTree(root, 0);
}

/// Подсчет количества узлов
template <class T>
int countNode(TreeNode<T> *node)
{
    int left, right;

    if (node->Left() == nullptr && node->Right() == nullptr)
        return 1;

    if (node->Left() != nullptr)
        left = countNode(node->Left());
    else
        left = 0;

    if (node->Right() != nullptr)
        right = countNode(node->Right());
    else
        right = 0;

    return left + right + 1;
}

/// Удаление узла
template <class T>
TreeNode<T> *Remove(TreeNode<T> *root, const T &data)
{
    TreeNode<T> *parent;

    if (root == nullptr)
    {
        // Дерево пустое или достигнут конец ветки (лист без значения)
        return nullptr;
    }

    if (data < root->data)
    {
        // Рекурсивно удаляем значение из левого поддерева
        root->left = Remove(root->left, data);
    }
    else if (data > root->data)
    {
        // Рекурсивно удаляем значение из правого поддерева
        root->right = Remove(root->right, data);
    }
    else
    {
        // Найден узел, который нужно удалить

        if (root->left == nullptr && root->right == nullptr)
        {
            // Узел является листом (не имеет потомков)
            delete root;
            root = nullptr;
        }
        else if (root->left == nullptr)
        {
            // Узел имеет только правого потомка
            parent = root;
            root = root->right;
            delete parent;
        }
        else if (root->right == nullptr)
        {
            // Узел имеет только левого потомка
            parent = root;
            root = root->left;
            delete parent;
        }
        else
        {
            // Узел имеет оба потомка
            TreeNode<T> *parent = FindMin(root->right);
            root->data = parent->data;
            root->right = Remove(root->right, parent->data);
        }
    }

    return root;
}

/// Поиск следующего наименьшего
template <class T>
TreeNode<T> *FindMin(TreeNode<T> *root)
{
    if (root == nullptr)
    {
        return nullptr;
    }
    while (root->left != nullptr)
    {
        root = root->left;
    }
    return root;
}

// создать объект TreeNode с указательными полями lptr и rptr.
// по умолчанию указатели содержат NULL.
template <class T>
TreeNode<T> *GetTreeNode(T item, TreeNode<T> *lptr = nullptr,
                         TreeNode<T> *rptr = nullptr)
{
    TreeNode<T> *p;

    // вызвать new для создания нового узла
    // передать туда параметры lptr и rptr
    p = new TreeNode<T>(item, lptr, rptr);

    // если памяти недостаточно, завершить
    // программу сообщением об ошибке
    if (p == nullptr)
    {
        cout << "Ошибка при выделении памяти!\n";
        exit(1);
    }
    // вернуть указатель на выделенную системой память
    return p;
}

// копирование дерева
template <class T>
TreeNode<T> *CopyTree(TreeNode<T> *node)
{
    // создаем указатели на новые узлы
    TreeNode<T> *newlptr, *newrptr, *newnode;
    // Если node равен nullptr, то это базовый случай рекурсии
    if (node == nullptr)
        return nullptr;
    // Если у узла node есть левый потомок (node->left),
    //  вызывается рекурсивный вызов функции CopyTree для копирования левого поддерева. Результат сохраняется в newlptr.
    if (node->left != nullptr)
        newlptr = CopyTree(node->left);
    else
        newlptr = nullptr;
    // Если у узла node есть правый потомок(node->right),
    //  вызывается рекурсивный вызов функции CopyTree для копирования правого поддерева.Результат сохраняется в newrptr.
    if (node->right != nullptr)
        newrptr = CopyTree(node->right);
    else
        newrptr = nullptr;
    // Создается новый узел newnode с данными node->data и указателями
    // на скопированные левое и правое поддеревья(newlptr и newrptr соответственно).
    // Новый узел newnode становится корневым узлом скопированного поддерева.
    newnode = new TreeNode<int>(node->data, newlptr, newrptr);
    return newnode;
}

// проход дерева в ширину с использованием очереди
template <class T>
void BFS(TreeNode<T> *root)
{
    if (root == nullptr)
        return;
    // создаем пустую очередь
    queue<TreeNode<T> *> q;
    // помещаем в очередь корневой узел
    q.push(root);
    // цикл до тех пор, пока queue не станет пустой
    while (!q.empty())
    {
        // создаем указатель на начало очереди
        TreeNode<T> *current = q.front();
        // извлекаем первый элемент
        q.pop();
        // Обработка текущего узла
        PrintNode(current);
        // Добавление левого и правого потомка текущего узла в очередь
        if (current->left != nullptr)
            q.push(current->left);
        if (current->right != nullptr)
            q.push(current->right);
    }
}

// увеличение данных узла на 10
template <class T>
void Inc(TreeNode<T> *node)
{
    node->data += 10;
}

// Умножение данных узла в 10 раз
template <class T>
void Multiplication(TreeNode<T> *node)
{
    node->data = node->data * 10;
}

// Возведение в степерь данных узла
template <class T>
void Sqr(TreeNode<T> *node)
{
    node->data = node->data * node->data;
}
