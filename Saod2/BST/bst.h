// @author: gingerswaltz
#pragma once
#include "../ConsoleApplication1/ConsoleApplication1/binary_tree.h"
// ����� ��������� ������ ������
class BinarySearchTree {
private:
    BinaryTree binaryTree;  // ���������� ����� BinaryTree ������ BinarySearchTree

public:
    // ����������� �� ���������
    BinarySearchTree() : binaryTree() {}

    // ����������� �����������
    BinarySearchTree(const BinarySearchTree& other) : binaryTree(other.binaryTree) {}

    // �������� ������������
    BinarySearchTree& operator=(const BinarySearchTree& other) {
        if (this == &other) {
            return *this;
        }

        binaryTree = other.binaryTree;
        return *this;
    }

    // ����������� �����������
    BinarySearchTree(BinarySearchTree&& other) noexcept : binaryTree(std::move(other.binaryTree)) {}

    // �������� �����������
    BinarySearchTree& operator=(BinarySearchTree&& other) noexcept {
        if (this == &other) {
            return *this;
        }

        binaryTree = std::move(other.binaryTree);
        return *this;
    }



    // ����� ��� ������� �������� � ������
    void insert(int value) {
        binaryTree.insert(value);
    }

    // ����� ��� ������ �������� � ������
    bool search(int value) {
        return binaryTree.search(value);
    }

    // ����� ��� �������� �������� ����� ������
    BinarySearchTree CopyTree() {
        BinarySearchTree newTree;
        newTree.binaryTree = binaryTree.CopyTree();
        return newTree;
    }

    // ����� ��� ���������� ������� ������
    int depth() {
        return binaryTree.depth();
    }

    // ����� ��� ������ ������ � ������
    void BreadthFirstSearch(std::function<void(int)> callback) {
        binaryTree.BreadthFirstSearch(callback);
    }
};
