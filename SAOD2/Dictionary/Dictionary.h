#include <iostream>
#include <utility>
#include <optional>
#include "../Hash Table/Hash-table.h" 

template <class K, class V>
struct KeyValuePair {
    K key;
    V value;

    KeyValuePair(K key, V value) : key(key), value(value) {}

    bool operator==(const KeyValuePair& other) const {
        return key == other.key;
    }
};

template <class K, class V>
class HashMap {
private:
    HashTable<KeyValuePair<K, V>> table;

    static unsigned long DefaultHashFunction(const KeyValuePair<K, V>& kvp) {
        return std::hash<K>()(kvp.key);
    }

public:
    HashMap(int nbuckets)
        : table(nbuckets, DefaultHashFunction) {}

    std::optional<V> put(const K& key, const V& value) {
        KeyValuePair<K, V> kvp(key, value);
        std::optional<V> oldValue;

        if (Node<KeyValuePair<K, V>>* existingNode = table.search(kvp)) {
            oldValue = existingNode->data.value;
            existingNode->data.value = value; // Обновляем значение
        } else {
            table.insert(kvp); // Вставляем новую пару
        }

        return oldValue;
    }

    std::optional<V> get(const K& key) {
        KeyValuePair<K, V> searchKey(key, V()); // Создаем пару для поиска
        if (Node<KeyValuePair<K, V>>* node = table.search(searchKey)) {
            return node->data.value; // Возвращаем значение, если ключ найден
        } else {
            return {}; // Возвращаем пустой optional, если ключ не найден
        }
    }

    std::optional<V> remove(const K& key) {
        KeyValuePair<K, V> searchKey(key, V()); // Создаем пару для удаления
        if (Node<KeyValuePair<K, V>>* node = table.search(searchKey)) {
            V removedValue = node->data.value;
            table.remove(searchKey); // Удаляем пару
            return removedValue; // Возвращаем удаленное значение
        } else {
            return {}; // Возвращаем пустой optional, если ключ не найден
        }
    }

    int size() const {
        return table.getSize(); // Возвращаем количество элементов в HashTable
    }
};
