#pragma once
#include <iostream>
#include <stack>
#include <functional>
#include <vector>

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
    return search(root->left, value);
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
void applyFunctionToTree(Node<T>* root, T(*func)(T)) {
    if (root != nullptr) {
        // ��������� ������� � �������� ��������
        root->data = func(root->data);
        // ���������� ������� ����� � ������ ����������
        applyFunctionToTree(root->left, func);
        applyFunctionToTree(root->right, func);
    }
}

// ������� ��� ���������� ����� � �������
template<typename T>
T square(T x) {
    return x * x;
}



///         1
///        / \       
///       2   3
///      /   / \
///     4   9  15



