//@author: gingerswaltz
#include "BinaryTree.h"


template <class T>
class AVLNode : public TreeNode<T> {
public:
    int height;

    // Конструктор
    AVLNode(const T& value) : TreeNode<T>(value, nullptr, nullptr), height(0) {}

    void updateHeight() {
        // Вычисляем высоту левого поддерева. Если левое поддерево существует, используем его высоту.
        // Если левого поддерева нет (узел левого поддерева равен nullptr), принимаем его высоту за -1.
        int leftHeight = this->left ? static_cast<AVLNode<T>*>(this->left)->height : -1;

        // Аналогично вычисляем высоту правого поддерева.
        int rightHeight = this->right ? static_cast<AVLNode<T>*>(this->right)->height : -1;

        // Высота текущего узла равна наибольшей высоте его поддеревьев плюс 1 (сам узел).
        // Это обеспечивает корректное вычисление высоты для всех узлов дерева.
        height = 1 + max(leftHeight, rightHeight);
    }


    int getBalance() {
        // Аналогично методу updateHeight, вычисляем высоту левого и правого поддеревьев.
        int leftHeight = this->left ? static_cast<AVLNode<T>*>(this->left)->height : -1;
        int rightHeight = this->right ? static_cast<AVLNode<T>*>(this->right)->height : -1;

        // Баланс узла равен разнице между высотами левого и правого поддеревьев.
        // Это показатель, насколько поддеревья узла "сбалансированы".
        return leftHeight - rightHeight;
    }

};

template <class T>
class AVLTree {
private:
    AVLNode<T>* root;

    AVLNode<T>* rightRotate(AVLNode<T>* y) {
        AVLNode<T>* x = static_cast<AVLNode<T>*>(y->left);
        AVLNode<T>* T2 = static_cast<AVLNode<T>*>(x->right);

        // Выполнение вращения
        x->right = y;
        y->left = T2;

        // Обновление высот
        y->updateHeight();
        x->updateHeight();

        // Возвращаем новый корень
        return x;
    }

    AVLNode<T>* leftRotate(AVLNode<T>* x) {
        AVLNode<T>* y = static_cast<AVLNode<T>*>(x->right);
        AVLNode<T>* T2 = static_cast<AVLNode<T>*>(y->left);

        // Выполнение вращения
        y->left = x;
        x->right = T2;

        // Обновление высот
        x->updateHeight();
        y->updateHeight();

        // Возвращаем новый корень
        return y;
}

    AVLNode<T>* balanceNode(AVLNode<T>* node) {
    if (node == nullptr) return nullptr;

    // Обновление высоты узла
    node->updateHeight();

    // Вычисление баланса узла
    int balance = node->getBalance();

    // Если узел несбалансирован, то есть, если разница высот поддеревьев больше 1
    // Левый Левый Случай
    if (balance > 1 && node->left && static_cast<AVLNode<T>*>(node->left)->getBalance() >= 0) {
        return rightRotate(node);
    }

    // Левый Правый Случай
    if (balance > 1 && node->left && static_cast<AVLNode<T>*>(node->left)->getBalance() < 0) {
        node->left = leftRotate(static_cast<AVLNode<T>*>(node->left));
        return rightRotate(node);
    }

    
    // Правый Правый Случай
    if (balance < -1 && node->right && static_cast<AVLNode<T>*>(node->right)->getBalance() <= 0) {
        return leftRotate(node);
    }

    // Правый Левый Случай
    if (balance < -1 && node->right && static_cast<AVLNode<T>*>(node->right)->getBalance() > 0) {
        node->right = rightRotate(static_cast<AVLNode<T>*>(node->right));
        return leftRotate(node);
    }

    return node;
}


    AVLNode<T>* insertNode(AVLNode<T>* node, const T& key) {
    // Обычная вставка BST
    if (node == nullptr) return new AVLNode<T>(key);

    if (key < node->data) {
        node->left = insertNode(static_cast<AVLNode<T>*>(node->left), key);
    } else if (key > node->data) {
        node->right = insertNode(static_cast<AVLNode<T>*>(node->right), key);
    } else {
        // Дубликаты не допускаются
        return node;
    }

        // Балансировка узла
        return balanceNode(node);
    }
    
    AVLNode<T>* deleteNode(AVLNode<T>* root, const T& key) {
        // Если текущий узел пустой, то ничего не делаем и возвращаем nullptr.
        if (root == nullptr) return root;

        // Если ключ меньше данных текущего узла, рекурсивно удаляем ключ из левого поддерева.
        if (key < root->data) {
            root->left = deleteNode(static_cast<AVLNode<T>*>(root->left), key);
        }
        // Если ключ больше, удаляем из правого поддерева.
        else if (key > root->data) {
            root->right = deleteNode(static_cast<AVLNode<T>*>(root->right), key);
        }
        // Если ключ равен данным в узле, то узел должен быть удален.
        else {
            // Случай, когда у узла нет потомков или только один потомок.
            if (root->left == nullptr || root->right == nullptr) {
                AVLNode<T>* temp = root->left ? static_cast<AVLNode<T>*>(root->left) : static_cast<AVLNode<T>*>(root->right);

                // Если у узла нет потомков.
                if (temp == nullptr) {
                    temp = root;
                    root = nullptr;
                }
                // Если у узла есть один потомок.
                else {
                    // Сохраняем текущий узел, который будет удален, и перемещаем его единственного ребенка на его место.
                    AVLNode<T>* tempToDel = root;
                    root = temp;
                    delete tempToDel; // Удаляем сохраненный узел.
                }
            }
            // Случай, когда у узла два потомка.
            else {
                // Находим узел с минимальным значением в правом поддереве (следующий за удаляемым по порядку).
                AVLNode<T>* temp = static_cast<AVLNode<T>*>(FindMin(root->right));

                // Копируем данные из этого узла в удаляемый узел.
                root->data = temp->data;

                // Рекурсивно удаляем минимальный узел из правого поддерева.
                root->right = deleteNode(static_cast<AVLNode<T>*>(root->right), temp->data);
            }
        }

        // Если после удаления дерево стало пустым, возвращаем nullptr.
        if (root == nullptr) return root;

        // Балансируем дерево после удаления узла.
        return balanceNode(root);
    }
    



    // Рекурсивная функция для проверки баланса каждого узла
    bool isBalanced(AVLNode<T>* node) {
        // Базовый случай рекурсии: если текущий узел пустой (nullptr), то он сбалансирован
        if (node == nullptr) {
            return true;
        }

        // Вычисляем высоту левого поддерева.
        // Если левое поддерево существует (node->left не nullptr), то используем его высоту.
        // Если левое поддерево отсутствует, принимаем его высоту за 0.
        int leftHeight = node->left ? static_cast<AVLNode<T>*>(node->left)->height : 0;

        // Аналогично вычисляем высоту правого поддерева.
        int rightHeight = node->right ? static_cast<AVLNode<T>*>(node->right)->height : 0;

        // Вычисляем баланс текущего узла (balanceFactor).
        // Баланс узла — это абсолютная разница в высотах левого и правого поддеревьев.
        // Это показатель того, насколько поддеревья "сбалансированы" относительно друг друга.
        int balanceFactor = abs(leftHeight - rightHeight);

        // Для того чтобы текущий узел считался сбалансированным, должны выполняться два условия:
        // 1. Баланс узла (разница в высотах поддеревьев) не должен превышать 1.
        // 2. Все поддеревья текущего узла также должны быть сбалансированы.
        // Для проверки второго условия вызываем функцию isBalanced рекурсивно для левого и правого поддеревьев.
        return balanceFactor <= 1
            && isBalanced(static_cast<AVLNode<T>*>(node->left))
            && isBalanced(static_cast<AVLNode<T>*>(node->right));
    }

public:
    AVLTree() : root(nullptr) {}

    void insert(const T& key) {
        root = insertNode(root, key);
    }

    void remove(const T& key) {
        root = deleteNode(root, key);
    }

    bool search(const T& data) {
        return Search(root, data);  
    }

    void printTree() {
        PrintTree(root, 0);
    }

    // Отладочный метод для получения корневого узла
    TreeNode<T>* getRoot() const {
        return root;
    }

    bool isBalanced() {
        return isBalanced(root);
    }

    void BreadthFirstSearch() {
        BFS(root);
    }
};
