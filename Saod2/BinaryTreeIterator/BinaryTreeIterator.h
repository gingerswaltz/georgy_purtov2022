template <typename T>
class BinaryTreeIterator {
public:
    // Конструктор итератора, принимающий начальный узел
    BinaryTreeIterator(Node<T>* start) : current(start) {
        initializeStack(); // Инициализируем стек для обхода
    }

    // Оператор разыменования, возвращающий текущий элемент
    T operator*() const {
        return current->data;
    }

    // Оператор инкремента (переход к следующему элементу)
    BinaryTreeIterator& operator++() {
        if (nodeStack.empty()) { // Если стек пуст, итератор завершил обход
            current = nullptr;
        }
        else {
            current = nodeStack.top(); // Текущий узел - вершина стека
            nodeStack.pop(); // Удаляем вершину стека
            if (current->right) {
                initializeStack(current->right); // Если есть правое поддерево, инициализируем стек
            }
        }
        return *this;
    }

    // Оператор сравнения на неравенство для завершения обхода
    bool operator!=(const BinaryTreeIterator& other) const {
        return current != other.current;
    }

private:
    Node<T>* current; // Текущий узел
    std::stack<Node<T>*> nodeStack; // Стек для обхода

    // Метод инициализации стека для обхода узлов в порядке LNR
    void initializeStack(Node<T>* node = nullptr) {
        while (node) {
            nodeStack.push(node); // Добавляем узел в стек
            node = node->left; // Переходим к левому поддереву
        }
    }
};
