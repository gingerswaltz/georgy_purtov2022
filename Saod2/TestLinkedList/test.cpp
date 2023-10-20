#include "pch.h"
#include "LinkedList.h" 

TEST(LinkedListTests, InsertAndToArray) {
    LinkedList<int> L1;
    L1.InsertAtTail(5);
    L1.InsertAtTail(10);
    L1.InsertAtTail(20);
    L1.InsertAtTail(30);
    L1.InsertAtTail(40);

    int* arr1 = L1.toListArray();
    ASSERT_EQ(L1.Size(), 5);
    ASSERT_EQ(arr1[0], 5);
    ASSERT_EQ(arr1[1], 10);
    ASSERT_EQ(arr1[2], 20);
    ASSERT_EQ(arr1[3], 30);
    ASSERT_EQ(arr1[4], 40);
    delete[] arr1;  // Не забудьте освободить массив после использования
}

TEST(LinkedListTests, Search) {
    LinkedList<int> L1;
    L1.InsertAtTail(5);
    L1.InsertAtTail(10);
    L1.InsertAtTail(20);

    ASSERT_EQ(L1.Search(5)->Data(), 5);
    ASSERT_EQ(L1.Search(20)->Data(), 20);
    ASSERT_EQ(L1.Search(40), nullptr);
}

TEST(LinkedListTests, Remove) {
    LinkedList<int> L1;
    L1.InsertAtTail(5);
    L1.InsertAtTail(10);
    L1.InsertAtTail(20);

    L1.Remove(5);
    L1.Remove(20);

    ASSERT_EQ(L1.Search(5), nullptr);
    ASSERT_EQ(L1.Search(20), nullptr);
    ASSERT_EQ(L1.Search(10)->Data(), 10);
}

TEST(LinkedListTests, ClearList) {
    LinkedList<int> L1;
    L1.InsertAtTail(5);
    L1.InsertAtTail(10);
    L1.InsertAtTail(20);

    L1.ClearList();

    ASSERT_EQ(L1.Search(5), nullptr);
    ASSERT_EQ(L1.Search(10), nullptr);
    ASSERT_EQ(L1.Search(20), nullptr);
    ASSERT_EQ(L1.Size(), 0);
}
