//@author gingerswaltz
#pragma once
#include <iostream>







template<typename T>
class Node {
public:
    T data;
    Node* next;
    Node* prev;

    Node(int data) {
        this->data = data;
        next = nullptr;
        prev = nullptr;
    }
};





template<typename T>
class LinkedList {
private:
    Node<T>* head;
    Node<T>* tail;

public:
    LinkedList() {
        head = nullptr;
        tail = nullptr;
    }

    void insertHead(const T& data) {
        Node<T>* newNode = new Node<T>(data);
        // Если список пустой, новый узел становится головным и хвостовым
        if (head == nullptr) {
            head = newNode;
            tail = newNode;
        }
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }

    }

    void insert(const T& data) {
        Node<T>* newNode = new Node<T>(data);
        // Если список пустой, новый узел становится головным и хвостовым
        if (head == nullptr) {
            head = newNode;
            tail = newNode;
        }
        else {
            // Привязываем новый узел к текущему хвосту
            tail->next = newNode;
            // Устанавливаем ссылку на предыдущий узел
            newNode->prev = tail;
            // Новый узел становится новым хвостом
            tail = newNode;
        }
    }


    void insertAfter(int DataAfter, const T& data) {
        Node<T>* newNode = new Node<T>(data);
        Node<T>* current = head;

        while (current != nullptr) {
            if (current->data == DataAfter) {
                if (current == tail) {
                    tail = newNode;  // Обновляем хвост списка, если вставляем после хвостового узла
                }
                newNode->prev = current;
                newNode->next = current->next;
                if (current->next != nullptr) {
                    current->next->prev = newNode;
                }
                current->next = newNode;
                return;
            }
            current = current->next;
        }
    }

    void update(const T& oldValue, const T& newValue) {
        Node<T>* current = head;
        while (current != nullptr) {
            if (current->data == oldValue) {
                current->data = newValue;
                return;
            }
            current = current->next;
        }
    }

    void clear() {
        while (head != nullptr) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void print() {
        Node<T>* current = head;
        while (current != nullptr) {
            // Выводим данные текущего узла
            std::cout << current->data << " ";
            // Переходим к следующему узлу
            current = current->next;
        }
        std::cout << std::endl;
    }

    Node<T>* search(const T& data) {
        Node<T>* current = head;
        while (current != nullptr) {
            if (current->data == data) {
                // Возвращаем узел, если найден элемент
                return current;
            }
            current = current->next;
        }
        // Если элемент не найден, возвращаем nullptr
        return nullptr;
    }

    void remove(const T& data) {
        Node<T>* current = head;
        while (current != nullptr) {
            if (current->data == data) {
                if (current == head) {
                    // Обновляем голову списка, если удаляемый элемент - головной узел
                    head = current->next;
                }
                if (current == tail) {
                    // Обновляем хвост списка, если удаляемый элемент - хвостовой узел
                    tail = current->prev;
                }
                if (current->prev != nullptr) {
                    // Обновляем ссылку на следующий узел для предыдущего узла
                    current->prev->next = current->next;
                }
                if (current->next != nullptr) {
                    // Обновляем ссылку на предыдущий узел для следующего узла
                    current->next->prev = current->prev;
                }
                // Удаляем узел
                delete current;
                return;
            }
            current = current->next;
        }
    }

    // Сортировка выбором
    void sort() {
        Node<T>* current = head;
        while (current != nullptr) {
            Node<T>* minNode = current;
            Node<T>* temp = current->next;
            while (temp != nullptr) {
                if (temp->data < minNode->data) {
                    minNode = temp;
                }
                temp = temp->next;
            }
            if (minNode != current) {
                // Обмен значениями узлов
                int tempData = current->data;
                current->data = minNode->data;
                minNode->data = tempData;
            }
            current = current->next;
        }
    }


};