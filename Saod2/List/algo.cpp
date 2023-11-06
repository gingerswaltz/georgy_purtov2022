#include <iostream>
#include <algorithm>
#include <vector>

// Функция для демонстрации использования for_each
void for_each_example() {
    std::vector<int> numbers = {1, 2, 3, 4, 5};
    
    // Используем std::for_each для вывода каждого элемента вектора
    // doc syntax+work logic
    std::for_each(numbers.begin(), numbers.end(), [](int x) {
        std::cout << x << " ";
    });
    std::cout << std::endl;             
}

// Функция для демонстрации использования any_of
void any_of_example() {
    std::vector<int> numbers = {1, 2, 3, 4, 5};
    
    // Используем std::any_of для проверки, есть ли хотя бы одно четное число
    bool hasEven = std::any_of(numbers.begin(), numbers.end(), [](int x) {
        return x % 2 == 0;
    });
    
    if (hasEven) {
        std::cout << "There is at least one even number." << std::endl;
    }
}

// Функция для демонстрации использования all_of
void all_of_example() {
    std::vector<int> numbers = {2, 4, 6, 8, 10};
    
    // Используем std::all_of для проверки, являются ли все числа четными
    bool allEven = std::all_of(numbers.begin(), numbers.end(), [](int x) {
        return x % 2 == 0;
    });
    
    if (allEven) {
        std::cout << "All numbers are even." << std::endl;
    }
}

// Функция для демонстрации использования none_of
void none_of_example() {
    std::vector<int> numbers = {1, 3, 5, 7, 9};
    
    // Используем std::none_of для проверки, что ни одно число не является четным
    bool noneEven = std::none_of(numbers.begin(), numbers.end(), [](int x) {
        return x % 2 == 0;
    });
    
    if (noneEven) {
        std::cout << "None of the numbers are even." << std::endl;
    }
}

// Функция для демонстрации использования transform
void transform_example() {
    std::vector<int> numbers = {1, 2, 3, 4, 5};
    std::vector<int> squared;
    
    // Используем std::transform для создания нового вектора, где каждый элемент - квадрат исходного
    std::transform(numbers.begin(), numbers.end(), std::back_inserter(squared), [](int x) {
        return x * x;
    });
    
    // Выводим новый вектор
    for (int num : squared) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

// Функция для демонстрации использования copy_if
void copy_if_example() {
    std::vector<int> numbers = {1, 2, 3, 4, 5};
    std::vector<int> evenNumbers;
    
    // Используем std::copy_if для создания нового вектора, содержащего только четные числа
    std::copy_if(numbers.begin(), numbers.end(), std::back_inserter(evenNumbers), [](int x) {
        return x % 2 == 0;
    });
    
    // Выводим новый вектор
    for (int num : evenNumbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

int main() {
    for_each_example();
    any_of_example();
    all_of_example();
    none_of_example();
    transform_example();
    copy_if_example();
    return 0;
}
