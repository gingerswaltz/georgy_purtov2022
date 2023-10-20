
#include "LinkedList.h"
#include <iostream>

using namespace std;
int main()
{
    LinkedList<int>* list1 = new LinkedList<int>();
 
    list1->InsertAtTail(5);///  5 10 20 30 40
    list1->InsertAtTail(10);
    list1->InsertAtTail(20);
    list1->InsertAtTail(30);
    list1->InsertAfter(30,40);

    //list1->Remove(10);
    //list1->Remove(40);
    //list1->Remove(5);
    //list1->Remove(20);
    //list1->Remove(30);

    //list1->ClearList();

    int* arr = new int[list1->Size()];
    arr = list1->toListArray();
    for (int i = 0; i < list1->Size(); i++)
    {
        cout << arr[i] << endl;
    }

    cout << "Size = " << list1->Size() << endl;;

    cout << "Used iterator: " << endl;
    for (LinkedList<int>::Iterator<int> it = list1->begin(); it != list1->end(); ++it) {
        cout << *it << " ";
    }
}

