#pragma once
template <typename T>
class Iterator {
public:
    // Оператор разыменования для получения текущего элемента
    virtual T operator*() const = 0;

    // Оператор инкремента для перемещения к следующему элементу
    virtual Iterator<T>& operator++() = 0;

    // Оператор сравнения на равенство
    virtual bool operator==(const Iterator<T>& other) const = 0;

    // Оператор сравнения на неравенство
    virtual bool operator!=(const Iterator<T>& other) const = 0;

    // Виртуальный деструктор
    virtual ~Iterator() = default;
};
