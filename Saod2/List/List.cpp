#include <cassert>
#include "LinkedList.h"
#include <iostream>
using namespace std;
// todo: empty list, 1 elem
void testLinkedListIterator() {
    LinkedList<int> list1;
    list1.InsertAtTail(1);
    list1.InsertAtTail(2);
    list1.InsertAtTail(3);

    cout << "Used iterator: " << endl;
    int expected[] = { 1, 2, 3 };
    int i = 0;

    for (LinkedList<int>::Iterator<int> it = list1.begin(); it != list1.end(); ++it) {
        assert(*it == expected[i]);
        ++i;
    }

    cout << "Iterator test passed!" << endl;
}

int main() {
    testLinkedListIterator();
    return 0;
}