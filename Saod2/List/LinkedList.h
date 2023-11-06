/// @author gingerswatlz
#pragma once
#include "ListNode.h"
/// ��������� ����� ������������ ������ � �������������� ����� ���� ������ (ListNode)
template <class T>
class LinkedList {
private:
    ListNode<T>* head;            /// ��������� �� �������� ���� ������
    ListNode<T>* tail;            /// ��������� �� ��������� ���� ������
    int size;                     /// ������ ������

public:
    /// ����������� �� ���������
    LinkedList() : head(nullptr), tail(nullptr), size(0) {}

    /// ����������
    ~LinkedList() {
        ClearList();
    }

    /// ������� �������� � ������ ������
    void InsertAtHead(const T& value) {
        ListNode<T>* newNode = new ListNode<T>(value);

        if (head == nullptr) {
            // ���� ������ ����, ������������� ����� ���� ��� �������� � ���������
            head = newNode;
            tail = newNode;
        }
        else {
            // �����, ��������� ����� ���� � �������� ����� � ��������� �������� ����
            newNode->SetNext(head);
            head->SetPrev(newNode);
            head = newNode;
        }

        size++;
    }

    /// ������� �������� � ����� ������
    void InsertAtTail(const T& value) {
        ListNode<T>* newNode = new ListNode<T>(value);

        if (head == nullptr) {
            // ���� ������ ����, ������������� ����� ���� ��� �������� � ���������
            head = newNode;
            tail = newNode;
        }
        else {
            // �����, ��������� ����� ���� � ��������� ����� � ��������� ��������� ����
            newNode->SetPrev(tail);
            tail->SetNext(newNode);
            tail = newNode;
        }

        size++;
    }

    /// ����� ���� � ��������� ������
    ListNode<T>* Search(const T& key) {
        ListNode<T>* current = head;

        while (current != nullptr) {
            if (current->Data() == key) {
                return current;
            }

            current = current->Next();
        }

        return nullptr; // ���� � ��������� ������ �� ������
    }

    /// ������� �������� ����� ���� � ��������� ������
    void InsertAfter(const T& key, const T& value) {
        ListNode<T>* node = Search(key);

        if (node == nullptr) {
            // ���� � ��������� ������ �� ������, �� ������ ������� ���������
            return;
        }

        if (node == tail) {
            // ���� ��������� ���� �������� ��������� �����, ��������� ����� ���� � ����� ������
            InsertAtTail(value);
        }
        else {
            // �����, ������� ����� ���� � ��������� ��� � ��������� ����� � ��������� �����
            ListNode<T>* newNode = new ListNode<T>(value);
            newNode->SetPrev(node);
            newNode->SetNext(node->Next());

            node->Next()->SetPrev(newNode);
            node->SetNext(newNode);
            size++;
        }
    }
   
    /// �������� �������� � ��������� ������
    void Remove(const T& key) {
        ListNode<T>* node = Search(key);

        if (node == nullptr) {
            // ���� � ��������� ������ �� ������, �� ������ ������� ���������
            return;
        }

        if (node == head) {
            // ���� ��������� ���� �������� ��������, ��������� �������� ����
            head = node->Next();
            if (head != nullptr) {
                head->SetPrev(nullptr);
            }
        }
        else if (node == tail) {
            // ���� ��������� ���� �������� ���������, ��������� ��������� ����
            tail = node->Prev();
            if (tail != nullptr) {
                tail->SetNext(nullptr);
            }
        }
        else {
            // �����, ��������� ���������� ���� � ��������� ����� � ��������� ������
            node->Prev()->SetNext(node->Next());
            node->Next()->SetPrev(node->Prev());
        }
        delete node;
        node = nullptr;
        size--;
    }

    /// ������� ������
    void ClearList() {
        ListNode<T>* current = head;
        while (current != nullptr) {
            ListNode<T>* temp = current;
            current = current->Next();
            delete temp;
        }

        head = nullptr;
        tail = nullptr;
        size = 0;
    }

    /// ����� ������ � ������������ ������
    T* toListArray() const {
        if (size == 0) {
            return nullptr;
        }

        T* array = new T[size];
        ListNode<T>* current = head;
        int i = 0;

        while (current != nullptr) {
            array[i] = current->Data();
            current = current->Next();
            i++;
        }

        return array;
    }

    /// ��������� ������� ������
    int Size() const {
        return size;
    }

template <class U>
    /// ��������� ����� �������� LinkedList
    class Iterator {
    private:
        ListNode<T>* current; // ��������� �� ������� ����

    public:
        /// ����������� ��� ����������
        Iterator(ListNode<T>* node) : current(node) {}

        /// �������� �������������
        T operator*() const {
            return current->Data();
        }

        /// �������� ����������� ����������
        Iterator<T>& operator++() {
            current = current->Next();
            return *this;
        }

        /// �������� ������������ ����������
        Iterator<T> operator++(int) {
            Iterator<T> temp = *this;
            current = current->Next();
            return temp;
        }

        /// �������� "�����"
        bool operator==(const Iterator<T>& it) const {
            return current == it.current;
        }

        /// ��������� "�� �����"
        bool operator!=(const Iterator<T>& it) const {
            return current != it.current;
        }
    };

    /// ������ ������� ������
    Iterator<T> begin() const {
        return Iterator<T>(head);
    }

    /// �������, ��������� �� ��������� ��������� ������
    Iterator<T> end() const {
        return Iterator<T>(nullptr);
    }
};