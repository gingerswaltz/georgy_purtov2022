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


    printTree(root);

    cout << "\npreorder: ";
    traversePreOrder(root);
    cout << "\nInorder: ";
    traverseInOrder(root);
    cout << "\nPostorder: ";
    traversePostOrder(root);
    cout << "\nCount node: "<< countNodes(root);
    cout<<"\nDepth of tree:"<<findTreeDepth(root);
    

    cout << "\nInserting";
    cout << "\n";
    insert(root, 0);
    insert(root, 5);
    printTree(root);
   

    cout << "\nDeleting";
    cout << "\n";
    deleteNode(root, 0);
    deleteNode(root, 5);
    printTree(root);
    
    
    deleteNode(root);

    
}