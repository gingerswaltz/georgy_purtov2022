#pragma once
#include <cassert>
#include <stack>
#include <stdexcept>
#include <functional>
#include <iostream>
#include <queue>
//    
class TreeNode {
public:
    int data;          //  
    TreeNode* left;    //    
    TreeNode* right;   //    

    //       
    TreeNode(int val) : data(val), left(nullptr), right(nullptr) {}
};

//   
class BinaryTree {
private:
    TreeNode* root;  //    
    //       
    TreeNode* copyTree(TreeNode* node) {
        if (node == nullptr) {
            return nullptr;
        }

        TreeNode* newNode = new TreeNode(node->data);
        newNode->left = copyTree(node->left);
        newNode->right = copyTree(node->right);
        return newNode;
    }

    //      
    int calculateDepth(TreeNode* node) {
        if (node == nullptr) {
            return 0;
        }

        int leftDepth = calculateDepth(node->left);
        int rightDepth = calculateDepth(node->right);

        return std::max(leftDepth, rightDepth) + 1;
    }
public:
    //        nullptr
    BinaryTree() : root(nullptr) {}

    //      
    void insert(int value) {
        root = insertRec(root, value);
    }

    //     
    TreeNode* insertRec(TreeNode* node, int value) {
        //   ,      
        if (node == nullptr) {
            return new TreeNode(value);
        }

        //      ,    
        if (value < node->data) {
            node->left = insertRec(node->left, value);
        }
        else if (value > node->data) {
            node->right = insertRec(node->right, value);
        }

        return node;
    }
     //      
    BinaryTree CopyTree() {
        BinaryTree newTree;
        newTree.root = copyTree(root);
        return newTree;
    }

    //      ( )
    int depth() {
        return calculateDepth(root);
    }

    //      
    void BreadthFirstSearch(std::function<void(int)> callback) {
        if (root == nullptr) {
            return;
        }

        std::queue<TreeNode*> q;
        q.push(root);

        while (!q.empty()) {
            TreeNode* current = q.front();
            q.pop();

            callback(current->data);

            if (current->left != nullptr) {
                q.push(current->left);
            }

            if (current->right != nullptr) {
                q.push(current->right);
            }
        }
    }

    //      
    bool search(int value) {
        return searchRec(root, value);
    }

    //     
    bool searchRec(TreeNode* node, int value) {
        //       ,  true
        if (node == nullptr || node->data == value) {
            return node != nullptr;
        }

        //     ,    
        if (value < node->data) {
            return searchRec(node->left, value);
        }
        else {
            return searchRec(node->right, value);
        }
    }


    //  
    class Iterator {
    private:
        std::stack<TreeNode*> stack;

    public:
        Iterator(TreeNode* root) {
            //  ,        
            while (root != nullptr) {
                stack.push(root);
                root = root->left;
            }
        }

        int next() {
            //   ,     
            if (stack.empty()) {
                throw std::runtime_error("  ");
            }

            //    
            TreeNode* current = stack.top();
            int value = current->data;

            //    
            stack.pop();
            if (current->right != nullptr) {
                current = current->right;
                while (current != nullptr) {
                    stack.push(current);
                    current = current->left;
                }
            }

            return value;
        }

        bool hasNext() const {
            return !stack.empty();
        }
    };

    // ,  
    Iterator iterator() {
        return Iterator(root);
    }


    //  LNR (in-order)   
    void traverseLNR(std::function<void(int)> callback) {
        Iterator it = iterator();
        while (it.hasNext()) {
            callback(it.next());
        }
    }

    //  RNL (reverse in-order)   
    void traverseRNL(std::function<void(int)> callback) {
        std::stack<int> values;
        Iterator it = iterator();
        while (it.hasNext()) {
            values.push(it.next());
        }
        while (!values.empty()) {
            callback(values.top());
            values.pop();
        }
    }
    
    void traverseNLR(TreeNode* node) {
        if (node == nullptr) {
            return;
        }
        //  (,    )
        std::cout << node->data << " ";
        traverseNLR(node->left);
        traverseNLR(node->right);
    }

};

