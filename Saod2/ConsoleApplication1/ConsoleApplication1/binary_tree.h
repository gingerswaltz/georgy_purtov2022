#pragma once
#include <iostream>
#include <stack>
#include <functional>
#include <vector>
#include <queue>
#include "Iterator.h"
// ��������� ����� ��������� ��������� ������
template<typename T>
struct Node {
    T data;
     Node* left;
     Node* right;

    Node() {
        left = nullptr;
        right = nullptr;
    }

};

// ��������� ����������� ���� ������
template<typename T>
 Node<T>* newNode(T data) {
    Node<T>* node = new Node<T>;
    node->data = data;
    node->left = nullptr;
    node->right = nullptr;
    return node;
}

// ����� ������ � ������� ������� ����, ����� �����, ������ �����
template<typename T>
void traversePreOrder(Node<T>* temp) {
    if (temp != nullptr) {
        std::cout << " " << temp->data;
        traversePreOrder(temp->left);
        traversePreOrder(temp->right);
    }
}

// ����� ������ � ������� ����� �����, ������� ����, ������ �����
template<typename T>
void traverseInOrder(Node<T>* temp) {
    if (temp != nullptr) {
        traverseInOrder(temp->left);
        std::cout << " " << temp->data;
        traverseInOrder(temp->right);
    }
}

// ����� ������ � ������� ����� �����, ������ �����, ������� ����
template<typename T>
void traversePostOrder(Node<T>* temp) {
    if (temp != nullptr) {
        traversePostOrder(temp->left);
        traversePostOrder(temp->right);
        std::cout << " " << temp->data;
    }
}

// �������� ���� ������
template<typename T>
void deleteNode(Node<T>* temp) {
    if (temp != nullptr) {
        deleteNode(temp->left);
        deleteNode(temp->right);
        delete temp;
    }
}


template<typename T>
int countNodes(Node<T>* root) {
    if (root == nullptr) {
        // ���� ������ ����� (������ ����� nullptr), ���������� 0.
        return 0;
    }
    else {
        // �����, ���������� ������� ���������� ����� � ����� � ������ �����������,
        // � ����� ��������� 1 ��� �������� ���� (�����).
        return 1 + countNodes(root->left) + countNodes(root->right);
    }
}


// ����� ������ � ���� ������, ����� �� LNR
template<typename T>
void printTree(Node<T>* root, int level = 0) {
    if (root == nullptr) {
        return;
    }

    // ���������� ������� ����� ���������
    printTree(root->left, level + 1);

    // ������� ������ � ����������� �� ������ ����
    for (int i = 0; i < level; ++i) {
        std::cout << "    ";
    }

    // ������� �������� ����
    std::cout << root->data << std::endl;

    // ���������� ������� ������ ���������
    printTree(root->right, level + 1);
}



// ����������� �������� ������ ������� ��� ������ �����
template<typename T>
int findTreeDepth(Node<T>* root) {
    if (root == nullptr) {
        return 0; // ��� ������� ������ ������� ����� 0
    }

    // ���� ��� �������� ��� ����� ������ � �� ������� � ������
    std::stack<std::pair<Node<T>*, int> > nodeStack;

    nodeStack.push(std::make_pair(root, 1)); // �������� ���� � ������� 1

    int maxDepth = 0;
    
    // ���� ���� �� ����
    while (!nodeStack.empty()) {
        // ������� ���� - ������ � �����
        Node<T>* currentNode = nodeStack.top().first;
        // ������ ������� ����� (������ ����) - ������� �������
        int currentDepth = nodeStack.top().second;
        // ����� ��������� ������ ���� ������� �� �����
        nodeStack.pop();

        // ��������� ������������ �������, ���� ������� ������� ������
        if (currentDepth > maxDepth) {
            maxDepth = currentDepth;
        }
        // ��������� ���������� � ��������� �������
        if (currentNode->left) {
            nodeStack.push(std::make_pair(currentNode->left, currentDepth + 1));
        }

        if (currentNode->right) {
            nodeStack.push(std::make_pair(currentNode->right, currentDepth + 1));
        }
    }

    return maxDepth;
}

template<typename T>
Node<T>* insert(Node<T>* root, T value) {
    // ���� ������ �����, ������� ����� ���� � ������ ��� ��������
    if (root == nullptr) {
        return newNode(value);
    }

    // ���������� ��������� �������� � ������ ���������, ���� ��� ������ �������� ����
    if (value > root->data) {
        root->right = insert(root->right, value);
    }
    // ��� � ����� ���������, ���� ��� ������ ��� ����� �������� ����
    else {
        root->left = insert(root->left, value);
    }

    return root;
}

template<typename T>
Node<T>* search(Node<T>* root, T value) {
    // ���� ������ ����� ��� ������� ���� �������� ������� ��������, ������� ������� ����
    if (root == nullptr || root->data == value) {
        return root;
    }

    // ���� ������� �������� ������ �������� �������� ����,
    // ���������� ������ � ������ ���������
    if (value > root->data) {
        return search(root->right, value);
    }

    // ����� ������ � ����� ���������
    Node<T>* result = search(root->left, value);

    // ���� ��������� ������ � ����� ��������� �� ����� nullptr, ������, �������� �������
    // � �� ��� ����������, ����� ���������� nullptr
    return (result != nullptr) ? result : nullptr;
}


// ������� ��� ������ ������ � ������� LNR � ���������� ��������� � ������
template<typename T>
void treeToVector(Node<T>* root, std::vector<T>& result) {
    if (root != nullptr) {
        // ���������� ������� ����� ���������
        treeToVector(root->left, result);

        // ��������� �������� �������� ���� � ������
        result.push_back(root->data);

        // ���������� ������� ������ ���������
        treeToVector(root->right, result);
    }
}


// ������� ��� ���������� ��������� ����
template<typename T>
Node<T>* findSuccessor(Node<T>* node) {
    while (node->left != nullptr) {
        node = node->left;
    }
    return node;
}

template<typename T>
Node<T>* deleteNodeWithSuccessor(Node<T>* root, T key) {
    if (root == nullptr) {
        return root; // ���� ������ ������, ���������� nullptr
    }

    // ���������� ���� ����, ������� ����� �������
    if (key < root->data) {
        root->left = deleteNodeWithSuccessor(root->left, key);
    }
    else if (key > root->data) {
        root->right = deleteNodeWithSuccessor(root->right, key);
    }
    else {
        // ���� ������, �������� ��������

        // � ������ 1 � 2 (���� ��� ������ ��� ����� �����), ������ ������� ����
        if (root->left == nullptr) {
            Node<T>* temp = root->right;
            delete root;
            return temp;
        }
        else if (root->right == nullptr) {
            Node<T>* temp = root->left;
            delete root;
            return temp;
        }

        // � ������ 3 (���� � ����� ������) ������ ���������
        Node<T>* successor = findSuccessor(root->right);

        // �������� ������ �������� ���� ������� ���������
        root->data = successor->data;

        // ���������� ������� ��������� �� ������� ���������
        root->right = deleteNodeWithSuccessor(root->right, successor->data);
    }

    return root;
}

// ������� ��� ������ ������ � ���������� ������� � ������� ��������
template<typename T>
void applyFunction(Node<T>* root, T(*func)(T)) {
    if (root != nullptr) {
        // ��������� ������� � �������� ��������
        root->data = func(root->data);
        // ���������� ������� ����� � ������ ����������
        applyFunction(root->left, func);
        applyFunction(root->right, func);
    }
}

// Breadth-First Search, �������� ������ ������ � ������
template<typename T>
std::vector<Node<T>*> breadthFirstSearch(Node<T>* root) {
    std::vector<Node<T>*> result;

    if (root == nullptr) {
        return result;
    }

    std::queue<Node<T>*> q;
    q.push(root);

    while (!q.empty()) {
        Node<T>* current = q.front();
        q.pop();

        // ��������� ������� ���� � ������ 
        result.push_back(current);

        // ��������� �������� ���� � �������
        if (current->left != nullptr) {
            q.push(current->left);
        }
        if (current->right != nullptr) {
            q.push(current->right);
        }
    }

    return result;
}

// �������� ����������� ��������� ������
template<typename T>
Node<T>* copyTree(Node<T>* source) {
    if (source == nullptr) {
        return nullptr; // ���� �������� ������ �����, ���������� nullptr
    }

    // ������� ����� ���� � ��� �� ���������
    Node<T>* new_node= newNode(source->data);

    // ���������� �������� ����� � ������ ����������
    new_node->left = copyTree(source->left);
    new_node->right = copyTree(source->right);

    return new_node;
}


template<typename T>
void deleteTree(Node<T>* node) {
    if (node == nullptr) {
        return;
    }

    // ���������� ������� ����� � ������ ���������
    deleteTree(node->left);
    deleteTree(node->right);

    // ������� ������� ����
    delete node;
}

// ������� ��� ���������� ����� � �������
template<typename T>
T square(T x) {
    return x * x;
}

template <typename T>
class BinaryTreeIterator : public Iterator<T> {
public:
    BinaryTreeIterator(Node<T>* start) : current(start) {
        if (current) {
            initializeStack(current);
        }
    }

    T operator*() const override {
        if (current) {
            return current->data;
        }
        else {
            throw std::runtime_error("Dereferencing a nullptr iterator");
        }
    }

    BinaryTreeIterator<T>& operator++() override {
        if (nodeStack.empty()) {
            current = nullptr;
        }
        else {
            current = nodeStack.top();
            nodeStack.pop();
            if (current->right) {
                initializeStack(current->right);
            }
        }
        return *this;
    }

    bool operator==(const Iterator<T>& other) const override {
        const BinaryTreeIterator<T>* otherIterator = dynamic_cast<const BinaryTreeIterator<T>*>(&other);
        if (otherIterator) {
            return current == otherIterator->current;
        }
        return false;
    }

    bool operator!=(const Iterator<T>& other) const override {
        return !(*this == other);
    }

    explicit operator bool() const {
        return current != nullptr;
    }

private:
    Node<T>* current;
    std::stack<Node<T>*> nodeStack;

    void initializeStack(Node<T>* node) {
        while (node) {
            nodeStack.push(node);
            node = node->left;
        }
    }
};
