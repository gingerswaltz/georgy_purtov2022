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
    std::vector<int> elements;
    printTree(root);

    
    
    cout << "\npreorder: ";
    traversePreOrder(root);
    cout << "\nInorder: ";
    traverseInOrder(root);
    cout << "\nPostorder: ";
    traversePostOrder(root);
    cout << "\nCount node: "<< countNodes(root);
    cout<<"\nDepth of tree:"<<findTreeDepth(root);
    
    treeToVector(root, elements);
    //  applyFunctionToTree(root, square);
   

    cout << "\nDeleting";
    cout << "\n";
    deleteNodeWithSuccessor(root, 1);
    deleteNodeWithSuccessor(root, 15);
    printTree(root);
    




    /*for (const int& element : elements) {
        std::cout << element << " ";
    }*/
    deleteNode(root);

    
}