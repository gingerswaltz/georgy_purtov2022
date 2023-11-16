//@author: gingerswaltz
#include "BinaryTree.h"
// Класс узла AVL дерева
template <class T>
class AVLNode : public TreeNode<T>
{
public:
    int height;

    // Конструктор
    AVLNode(const T &value) : TreeNode<T>(value, nullptr, nullptr), height(0) {}

    void updateHeight()
    {
        // Вычисляем высоту левого поддерева. Если левое поддерево существует, используем его высоту.
        // Если левого поддерева нет (узел левого поддерева равен nullptr), принимаем его высоту за -1.
        int leftHeight = this->left ? dynamic_cast<AVLNode<T> *>(this->left)->height : -1;

        // Аналогично вычисляем высоту правого поддерева.
        int rightHeight = this->right ? dynamic_cast<AVLNode<T> *>(this->right)->height : -1;

        // Высота текущего узла равна наибольшей высоте его поддеревьев плюс 1 (сам узел).
        // Это обеспечивает корректное вычисление высоты для всех узлов дерева.
        height = 1 + max(leftHeight, rightHeight);
    }

    int getBalance()
    {
        // Аналогично методу updateHeight, вычисляем высоту левого и правого поддеревьев.
        int leftHeight = this->left ? dynamic_cast<AVLNode<T> *>(this->left)->height : -1;
        int rightHeight = this->right ? dynamic_cast<AVLNode<T> *>(this->right)->height : -1;

        // Баланс узла равен разнице между высотами левого и правого поддеревьев.
        // Это показатель, насколько поддеревья узла "сбалансированы".
        return leftHeight - rightHeight;
    }
};

/// todo: doc, метод который обходит дерево и возвращает массив, и проверить его на свойство бинарного дерева
// Класс AVL дерева
template <class T>
class AVLTree
{
private:
    // корень дерева
    AVLNode<T> *root;

    // Метод правого поворота
    AVLNode<T> *rightRotate(AVLNode<T> *y)
    {
        // Получаем левого потомка узла y как узел x.
        AVLNode<T> *x = dynamic_cast<AVLNode<T> *>(y->left);

        // Получаем правого потомка узла x, который будет перемещен.
        AVLNode<T> *T2 = dynamic_cast<AVLNode<T> *>(x->right);

        // Выполняем правое вращение.
        x->right = y; // Устанавливаем узел y как правого потомка узла x.
        y->left = T2; // Перемещаем узел T2 как левого потомка узла y.

        // Обновляем высоты узлов y и x после вращения.
        y->updateHeight();
        x->updateHeight();

        // Возвращаем новый корень поддерева после вращения.
        return x;
    }

    // Метод левого поворота
    AVLNode<T> *leftRotate(AVLNode<T> *x)
    {
        // Получаем правого потомка узла x как узел y.
        AVLNode<T> *y = dynamic_cast<AVLNode<T> *>(x->right);

        // Получаем левого потомка узла y, который будет перемещен.
        AVLNode<T> *T2 = dynamic_cast<AVLNode<T> *>(y->left);

        // Выполняем левое вращение.
        y->left = x;   // Устанавливаем узел x как левого потомка узла y.
        x->right = T2; // Перемещаем узел T2 как правого потомка узла x.

        // Обновляем высоты узлов x и y после вращения.
        x->updateHeight();
        y->updateHeight();

        // Возвращаем новый корень поддерева после вращения.
        return y;
    }

    // Метод балансировки
    AVLNode<T> *balanceNode(AVLNode<T> *node)
    {
        if (node == nullptr)
            return nullptr;

        // Обновление высоты узла
        node->updateHeight();

        // Вычисление баланса узла
        int balance = node->getBalance();

        // Если узел несбалансирован, то есть, если разница высот поддеревьев больше 1
        // Левый Левый Случай
        if (balance > 1 && node->left && dynamic_cast<AVLNode<T> *>(node->left)->getBalance() >= 0)
        {
            return rightRotate(node);
        }

        // Левый Правый Случай
        if (balance > 1 && node->left && dynamic_cast<AVLNode<T> *>(node->left)->getBalance() < 0)
        {
            node->left = leftRotate(dynamic_cast<AVLNode<T> *>(node->left));
            return rightRotate(node);
        }

        // Правый Правый Случай
        if (balance < -1 && node->right && dynamic_cast<AVLNode<T> *>(node->right)->getBalance() <= 0)
        {
            return leftRotate(node);
        }

        // Правый Левый Случай
        if (balance < -1 && node->right && dynamic_cast<AVLNode<T> *>(node->right)->getBalance() > 0)
        {
            node->right = rightRotate(dynamic_cast<AVLNode<T> *>(node->right));
            return leftRotate(node);
        }

        return node;
    }

    // Метод вставки
    AVLNode<T> *insertNode(AVLNode<T> *node, const T &key)
    {
        // Обычная вставка BST
        if (node == nullptr)
            return new AVLNode<T>(key);

        if (key < node->data)
        {
            node->left = insertNode(dynamic_cast<AVLNode<T> *>(node->left), key);
        }
        else if (key > node->data)
        {
            node->right = insertNode(dynamic_cast<AVLNode<T> *>(node->right), key);
        }
        else
        {
            // Дубликаты не допускаются
            return node;
        }

        // Балансировка узла
        return balanceNode(node);
    }

    // Рекурсивная функция для проверки баланса каждого узла
    bool isBalanced(AVLNode<T> *node)
    {
        // Базовый случай рекурсии: если текущий узел пустой (nullptr), то он сбалансирован
        if (node == nullptr)
        {
            return true;
        }

        // Вычисляем высоту левого поддерева.
        // Если левое поддерево существует (node->left не nullptr), то используем его высоту.
        // Если левое поддерево отсутствует, принимаем его высоту за 0.
        int leftHeight = node->left ? dynamic_cast<AVLNode<T> *>(node->left)->height : 0;

        // Аналогично вычисляем высоту правого поддерева.
        int rightHeight = node->right ? dynamic_cast<AVLNode<T> *>(node->right)->height : 0;

        // Вычисляем баланс текущего узла (balanceFactor).
        // Баланс узла — это абсолютная разница в высотах левого и правого поддеревьев.
        // Это показатель того, насколько поддеревья "сбалансированы" относительно друг друга.
        int balanceFactor = abs(leftHeight - rightHeight);

        // Для того чтобы текущий узел считался сбалансированным, должны выполняться два условия:
        // 1. Баланс узла (разница в высотах поддеревьев) не должен превышать 1.
        // 2. Все поддеревья текущего узла также должны быть сбалансированы.
        // Для проверки второго условия вызываем функцию isBalanced рекурсивно для левого и правого поддеревьев.
        return balanceFactor <= 1 && isBalanced(dynamic_cast<AVLNode<T> *>(node->left)) && isBalanced(dynamic_cast<AVLNode<T> *>(node->right));
    }

public:
    // Конструктор
    AVLTree() : root(nullptr) {}

    // Публичный интерфейс вставки
    void insert(const T &key)
    {
        root = insertNode(root, key);
    }

    // Публичный интерфейс удаления элемента
    void remove(const T &key)
    {
        // Приводим root к типу AVLNode<T>* для вызова deleteNode
        AVLNode<T> *newRoot = dynamic_cast<AVLNode<T> *>(deleteNode(root, key));

        // newRoot не является nullptr после приведения типов
        if (newRoot != nullptr)
        {
            root = newRoot;
        }

        // balanceNode, даже если newRoot равен nullptr,
        // так как балансировка может потребоваться в любом случае.
        root = this->balanceNode(root);
    }


    // Публичный интерфейс поиска
    bool search(const T &data)
    {
        return Search(root, data);
    }

    // Публичный интерфейс вывода дерева
    void printTree()
    {
        PrintTree(root, 0);
    }

    // Отладочный метод для получения корневого узла
    TreeNode<T> *getRoot() const
    {
        return root;
    }

    // Публичный интерфейс для отладочной функции
    bool isBalanced()
    {
        return isBalanced(root);
    }

    // Публичный интерфейс для обхода в глубину
    void BreadthFirstSearch()
    {
        BFS(root);
    }

   int addToArr(T arr[], int size) {
        if (this->root == nullptr || arr == nullptr || size <= 0) {
            return 0; // Возвращаем 0, если дерево пусто или массив недействителен.
        }
        return AddArr(this->root, arr, 0);
    }
};
