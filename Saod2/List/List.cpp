#include <cassert>
#include "LinkedList.h"
#include <iostream>
using namespace std;
void testLinkedListIterator() {
    LinkedList<int> list1;
    list1.InsertAtTail(1);
    list1.InsertAtTail(2);
    list1.InsertAtTail(3);

    int expected[] = { 1, 2, 3 };
    int i = 0;

    for (LinkedList<int>::Iterator<int> it = list1.begin(); it != list1.end(); ++it) {
        assert(*it == expected[i]);
        ++i;
    }
    for (auto it = list1.begin(); it != list1.end(); ++it) {
        assert(*it == expected[i]);
        ++i;
    }

    // for (int x: list1){
    //     assert(*it == expected[i]);
    //     ++i;
    // }

    cout << "Iterator test passed!" << endl;
}

void testLinkedListIterator2() {
    LinkedList<int> list1;
    list1.InsertAtTail(1);
    
    cout << "Used iterator: " << endl;
    int expected[] = { 1 };
    int i = 0;

    for (LinkedList<int>::Iterator<int> it = list1.begin(); it != list1.end(); ++it) {
        assert(*it == expected[i]);
        ++i;
    }

    cout << "Iterator test (1 element) passed!" << endl;
}


void testLinkedListIterator3() {
    LinkedList<int> emptyList;

    cout << "Used iterator on an empty list: " << endl;
    bool iteratorUsed = false;

    for (LinkedList<int>::Iterator<int> it = emptyList.begin(); it != emptyList.end(); ++it) {
        // Итератор не должен зайти в этот цикл на пустом списке.
        iteratorUsed = true;
    }

    assert(!iteratorUsed); // Утверждаем, что итератор не был использован на пустом списке.
    cout << "Empty list iterator test passed!" << endl;
}


int main() {
    testLinkedListIterator();
    testLinkedListIterator2();
    testLinkedListIterator3();
    return 0;
}