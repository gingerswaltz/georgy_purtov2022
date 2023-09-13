#pragma once
#include <iostream>

// ��������� ����� ��������� ������
template<typename T>
struct Node {
    T data;
    struct Node* left;
    struct Node* right;

    Node() {
        left = nullptr;
        right = nullptr;
    }

    //todo: Node(...)

};

// ��������� ����������� ���� ������
template<typename T>
struct Node<T>* newNode(T data) {
    struct Node<T>* node = new Node<T>;

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
        free(temp);
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

///         1
///        / \       
///       2   3
///      /   / \
///     4   9  15



