// @author: gingerswaltz
#pragma once
#include "..//ConsoleApplication1/ConsoleApplication1/binary_tree.h"
// ����� ��������� ������ ������
template<typename T>
class BinarySearchTree {
private:
    Node<T>* root;



public:
    BinarySearchTree() {
        root = nullptr;
    }

    // ����������� � ����������
    BinarySearchTree(T initialValue) {
        root = newNode(initialValue); // ������� �������� ���� � ��������� ���������
    }

    // ����������� �����������
    BinarySearchTree(const BinarySearchTree& other) {
        // �������� ������� ����������� ������ � ����������� �������� ����
        root = copyTree(other.root);
    }

    // ����������� �����������
    BinarySearchTree(BinarySearchTree&& other) noexcept {
        // ���������� ��������� �� �������� ���� �� ������� �������
        root = other.root;

        // ������������� ��������� � ������ ������� �� nullptr,
        // ����� �������� ������������ ������ ��� ���������� ������� �������
        other.root = nullptr;
    }

    // ����������� � ����������, ����������� ��������� �� �������� ����
    BinarySearchTree(Node<T>* rootNode) {
        root = rootNode;
    }

    // �������� ������������ ������������
    BinarySearchTree& operator=(BinarySearchTree&& other) noexcept {
        if (this == &other) {
            return *this; // �������� �� ����������������
        }

        // ����������� ������� �������� �������
        deleteTree(root);

        // ���������� ��������� �� �������� ���� �� ������� �������
        root = other.root;

        // ������������� ��������� � ������ ������� �� nullptr,
        // ����� �������� ������������ ������ ��� ���������� ������� �������
        other.root = nullptr;

        return *this;
    }

    // �������� ������������ ������������
    BinarySearchTree& operator=(const BinarySearchTree& other) {
        if (this == &other) {
            return *this; // �������� �� ����������������
        }

        // ����������� ������� �������� �������
        deleteTree(root);

        // �������� ������ �� ������� �������
        root = copyTree(other.root);

        return *this;
    }


    ~BinarySearchTree() {
        // �������� ������� �������� ������ ��� ������������ ������
        deleteTree(root);
    }

    // ����� ��� ������� �������� � BST
    void insert(T value) {
        root = ::insert(root, value);
    }

    // ����� ��� ������ �������� � BST
    bool search(T value) {
        Node<T>* result = ::search(root, value);
        return (result != nullptr);
    }


    // ����� ��� ������ ������
    void print() {
        printTree(root);
    }

    // ����� ��� ���������� ������� ������
    int depth() {
        return findTreeDepth(root);
    }

    // ����� ��� �������� ��������
    void remove(T value) {
        root = deleteNodeWithSuccessor(root, value);
    }


    // ����� ��� ������ ������ � ������ � �������� �����
    std::vector<Node<T>*> breadthFirstSearch() {
        return ::breadthFirstSearch(root);
    }


};
