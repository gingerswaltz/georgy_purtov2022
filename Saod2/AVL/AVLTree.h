//@author: gingerswaltz
#include <iostream>
#include "binary_tree.h"

class AVLTree : public BinaryTree {
private:
  struct AVLNode : TreeNode {
    int height;
    
    AVLNode(int data) : TreeNode(data), height(1) {}
  };

  void updateHeight(AVLNode* node) {
    int leftHeight = (node->left) ? static_cast<AVLNode*>(node->left)->height : 0;
    int rightHeight = (node->right) ? static_cast<AVLNode*>(node->right)->height : 0;
    node->height = 1 + std::max(leftHeight, rightHeight);
  }

  int getBalance(AVLNode* node) {
    int leftHeight = (node->left) ? static_cast<AVLNode*>(node->left)->height : 0;
    int rightHeight = (node->right) ? static_cast<AVLNode*>(node->right)->height : 0;
    return leftHeight - rightHeight;
  }

  AVLNode* rotateRight(AVLNode* node) {
    AVLNode* left = static_cast<AVLNode*>(node->left);
    node->left = left->right;
    left->right = node;
    updateHeight(node);
    updateHeight(left);
    return left;
  }

  AVLNode* rotateLeft(AVLNode* node) {
    AVLNode* right = static_cast<AVLNode*>(node->right);
    node->right = right->left;
    right->left = node;
    updateHeight(node);
    updateHeight(right);
    return right;
  }

  AVLNode* balance(AVLNode* node) {
    updateHeight(node);
    int balance = getBalance(node);

    if (balance > 1) {
      if (getBalance(static_cast<AVLNode*>(node->right)) < 0) {
        node->right = rotateRight(static_cast<AVLNode*>(node->right));
      }
      return rotateLeft(node);
    } else if (balance < -1) {
      if (getBalance(static_cast<AVLNode*>(node->left)) > 0) {
        node->left = rotateLeft(static_cast<AVLNode*>(node->left));
      }
      return rotateRight(node);
    }

    return node;
  }

  AVLNode* insertNode(AVLNode* node, int value) {
    if (node == nullptr) {
      return new AVLNode(value);
    }
    if (value < node->data) {
      node->left = insertNode(static_cast<AVLNode*>(node->left), value);
    } else {
      node->right = insertNode(static_cast<AVLNode*>(node->right), value);
    }
    return balance(node);
  }

  void destroy(AVLNode* node) {
    if (node != nullptr) {
      destroy(static_cast<AVLNode*>(node->left));
      destroy(static_cast<AVLNode*>(node->right));
      delete node;
    }
  }

public:
  AVLTree() {
    root = nullptr;
  }

  void insert(int value) {
    root = insertNode(static_cast<AVLNode*>(root), value);
  }

  ~AVLTree() {
    destroy(static_cast<AVLNode*>(root));
  }
};
