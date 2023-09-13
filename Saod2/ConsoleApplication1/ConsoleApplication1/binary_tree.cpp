#include <stdlib.h>
#include <iostream>

#include "binary_tree.h"


using namespace std;




int main() {
    Node<int>* root = newNode<int>(1);
    root->left = newNode(2);
    root->right = newNode(3);
    root->right->left = newNode(9);
    root->left->left = newNode(4);
    root->right->right = newNode(15);

    cout << "preorder: ";
    traversePreOrder(root);
    cout << "\nInorder: ";
    traverseInOrder(root);
    cout << "\nPostorder: ";
    traversePostOrder(root);

    deleteNode(root);

    traverseInOrder(root);

}