/// @author gingerswatlz
#pragma once
#include "ListNode.h"
/// шаблонный класс односвязного списка с использованием класс узел списка (ListNode)
template <class T>
class LinkedList {
private:
    ListNode<T>* head;            /// Указатель на головной узел списка
    ListNode<T>* tail;            /// Указатель на хвостовой узел списка
    int size;                     /// Размер списка

public:
    /// Конструктор по умолчанию
    LinkedList() : head(nullptr), tail(nullptr), size(0) {}

    /// Деструктор
    ~LinkedList() {
        ClearList();
    }

    /// Вставка элемента в начало списка
    void InsertAtHead(const T& value) {
        ListNode<T>* newNode = new ListNode<T>(value);

        if (head == nullptr) {
            // Если список пуст, устанавливаем новый узел как головной и хвостовой
            head = newNode;
            tail = newNode;
        }
        else {
            // Иначе, связываем новый узел с головным узлом и обновляем головной узел
            newNode->SetNext(head);
            head->SetPrev(newNode);
            head = newNode;
        }

        size++;
    }

    /// Вставка элемента в конец списка
    void InsertAtTail(const T& value) {
        ListNode<T>* newNode = new ListNode<T>(value);

        if (head == nullptr) {
            // Если список пуст, устанавливаем новый узел как головной и хвостовой
            head = newNode;
            tail = newNode;
        }
        else {
            // Иначе, связываем новый узел с хвостовым узлом и обновляем хвостовой узел
            newNode->SetPrev(tail);
            tail->SetNext(newNode);
            tail = newNode;
        }

        size++;
    }

    /// Поиск узла с указанным ключом
    ListNode<T>* Search(const T& key) {
        ListNode<T>* current = head;

        while (current != nullptr) {
            if (current->Data() == key) {
                return current;
            }

            current = current->Next();
        }

        return nullptr; // Узел с указанным ключом не найден
    }

    /// Вставка элемента после узла с указанным ключом
    void InsertAfter(const T& key, const T& value) {
        ListNode<T>* node = Search(key);

        if (node == nullptr) {
            // Узел с указанным ключом не найден, не делаем никаких изменений
            return;
        }

        if (node == tail) {
            // Если указанный узел является хвостовым узлом, вставляем новый узел в конец списка
            InsertAtTail(value);
        }
        else {
            // Иначе, создаем новый узел и связываем его с указанным узлом и следующим узлом
            ListNode<T>* newNode = new ListNode<T>(value);
            newNode->SetPrev(node);
            newNode->SetNext(node->Next());

            node->Next()->SetPrev(newNode);
            node->SetNext(newNode);
            size++;
        }
    }
   
    /// Удаление элемента с указанным ключом
    void Remove(const T& key) {
        ListNode<T>* node = Search(key);

        if (node == nullptr) {
            // Узел с указанным ключом не найден, не делаем никаких изменений
            return;
        }

        if (node == head) {
            // Если удаляемый узел является головным, обновляем головной узел
            head = node->Next();
            if (head != nullptr) {
                head->SetPrev(nullptr);
            }
        }
        else if (node == tail) {
            // Если удаляемый узел является хвостовым, обновляем хвостовой узел
            tail = node->Prev();
            if (tail != nullptr) {
                tail->SetNext(nullptr);
            }
        }
        else {
            // Иначе, связываем предыдущий узел с следующим узлом и обновляем ссылки
            node->Prev()->SetNext(node->Next());
            node->Next()->SetPrev(node->Prev());
        }
        delete node;
        node = nullptr;
        size--;
    }

    /// Очистка списка
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

    /// Вывод списка в динамический массив
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

    /// Получение размера списка
    int Size() const {
        return size;
    }


    /// шаблонный класс итератор LinkedList
    template<class T>
    class Iterator {
    private:
        ListNode<T>* current; // Указатель на текущий узел

    public:
        /// Конструктор без параметров
        Iterator(ListNode<T>* node) : current(node) {}

        /// Оператор разыменования
        T operator*() const {
            return current->Data();
        }

        /// Оператор префиксного инкремента
        Iterator<T>& operator++() {
            current = current->Next();
            return *this;
        }

        /// Оператор постфиксного инкремента
        Iterator<T> operator++(int) {
            Iterator<T> temp = *this;
            current = current->Next();
            return temp;
        }

        /// Оператор "равно"
        bool operator==(const Iterator<T>& it) const {
            return current == it.current;
        }

        /// Оператора "не равно"
        bool operator!=(const Iterator<T>& it) const {
            return current != it.current;
        }
    };

    /// Первый элемент списка
    Iterator<T> begin() const {
        return Iterator<T>(head);
    }

    /// Элемент, следующий за последним элементом списка
    Iterator<T> end() const {
        return Iterator<T>(nullptr);
    }
};