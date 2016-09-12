#include <iostream>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long ll;

struct node {
  int key;
  int height;
  node* left;
  node* right;
  node* parent;
};
class Bst {
  node* root;
  int size;

 public:
  // constractor
  Bst() : root(NULL), size(0) {}
  
  int height(node* N) {
    if (N == NULL) return 0;
    return N->height;
  }
  
  void update_height(node *N){
    if(N == NULL)return;
    N->height = max(height(N->left), height(N->right))+1;
  }

  int getBalance(node* N) {
    if (N == NULL) return 0;
    return height(N->left) - height(N->right);
  }
 
  node* newNode(int key) {
    node* new_node = new node;
    new_node->key = key;
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->parent = NULL;
    new_node->height = 1;  // leaf
    return (new_node);
  }
  //rotate left
  void leftRotate(node *cur){
    cur = cur->right;
    cur->parent->right = cur->left;
    cur->left->parent = cur->parent;
    cur->left = cur->parent;
    cur->parent = cur->left->parent;
    cur->left->parent = cur;
    if(cur->parent != NULL){
      if(cur->key > cur->parent->key) 
        cur->parent->right = cur;
      else 
        cur->parent->left = cur;
    }
    update_height(cur->left);
    update_height(cur);
    update_height(cur->parent);
  }
  //rotate right
  void rightRotate(node *cur){
    cur = cur->left;
    cur->parent->left = cur->right;
    cur->right->parent = cur->parent;
    cur->right = cur->parent;
    cur->parent = cur->right->parent;
    cur->right->parent = cur;
    if(cur->parent != NULL){
      if(cur->key > cur->parent->key) 
        cur->parent->right = cur;
      else 
        cur->parent->left = cur;
    }
    update_height(cur->right);
    update_height(cur);
    update_height(cur->parent);
  }
  // rebalance
  void rebalance(node* pre) {
    if (pre == NULL) return;
    pre->height =
        max(height(pre->left), height(pre->right)) + 1;  // update height
    int balance = getBalance(pre);  // get balance factor
    // If this node becomes unbalanced, then there are 4 cases

    if (balance > 1) {
      // Left Left Case
      if (height(pre->left->left) >= height(root->left->right)) {
        rightRotate(pre);
      } else {  // left right case
        leftRotate(pre->left);
        rightRotate(pre);
      }
    } else if (balance < -1) {
      // right right case
      if (height(pre->right->right) >= height(pre->right->left)) {
        leftRotate(pre);
      } else {  // right left case
        rightRotate(pre->right);
        leftRotate(pre);
      }
    }
    rebalance(pre->parent);
  }
  // insert
  void insert(int key) {
    if (size == 0 || root == NULL) {  // tree is empty
      root = newNode(key);
      size++;
      return;
    }

    node* pre = find(key);
    if (pre->key == key) return;  // the element in already in the tree

    node* new_node = newNode(key);
    if (pre->key > key) {
      pre->left = new_node;
    } else {
      pre->right = new_node;
    }
    new_node->parent = pre;
    size++;
    rebalance(pre);
  }
  // delete
  void del(int key) {
    node* cur = find(key);
    if (cur == NULL || cur->key != key) return;
    if (cur->right == NULL) {  // leaf or have left only
      if (cur->parent != NULL) {
        if (cur->key > cur->parent->key)
          cur->parent->right = cur->left;  // cur right child
        else
          cur->parent->left = cur->left;
        if (cur->left != NULL) cur->left->parent = cur->parent;
      } else {
        root = cur->left;
        if (cur->left != NULL) cur->left->parent = NULL;
      }
    } else {
      node* ans = next(cur);

      if (ans->key > ans->parent->key)
        ans->parent->right = ans->right;
      else
        ans->parent->left = ans->right;

      ans->left = cur->left;
      ans->right = cur->right;
      ans->parent = cur->parent;

      if (ans->parent == NULL) {
        root = ans;
      } else {
        if (ans->key > ans->parent->key)
          ans->parent->right = ans;
        else
          ans->parent->left = ans;
      }
    }
    size--;
  }
  // next
  node* next(node* cur) {
    cur = cur->right;
    while (cur->left != NULL) {
      cur = cur->left;
    }
    return cur;
  }
  // find
  node* find(int key) {
    node* pre;
    node* cur;
    pre = cur = root;
    while (cur != NULL) {
      pre = cur;
      if (cur->key == key) {
        return cur;
      } else if (cur->key > key) {
        cur = cur->left;
      } else {
        cur = cur->right;
      }
    }
    return pre;
  }
  int get_size() { return size; }
};
int main() {
  freopen("c.in", "r", stdin);
  freopen("c.out", "w", stdout);
  Bst b;
  b.insert(5);
  b.insert(6);
  b.insert(3);
  b.insert(2);
  cout << b.get_size() << "\n";
}
