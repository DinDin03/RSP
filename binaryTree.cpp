#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

struct Node {
  int data;
  Node *left, *right;

  Node(int key) {
    data = key;
    left = right = nullptr;
  }
};

class BST {
 private:
  Node *root;
  Node *insertHelper(Node *node, int value) {
    if (node == nullptr) {
      return new Node(value);
    }
    if (value < node->data) {
      node->left = insertHelper(node->left, value);
    } else if (value > node->data) {
      node->right = insertHelper(node->right, value);
    }
    return node;
  }
  Node *findMin(Node *node) {
    while (node->left != nullptr) {
      node = node->left;
    }
    return node;
  }
  Node *deleteHelper(Node *node, int value) {
    if (node == nullptr) {
      return nullptr;
    }
    if (value < node->data) {
      node->left = deleteHelper(node->left, value);
    } else if (value > node->data) {
      node->right = deleteHelper(node->right, value);
    } else {
      if (node->left == nullptr) {
        Node *temp = node->right;
        delete node;
        return temp;
      }
      if (node->right == nullptr) {
        Node *temp = node->left;
        delete node;
        return temp;
      }
      Node *temp = findMin(node->right);
      node->data = temp->data;
      node->right = deleteHelper(node->right, temp->data);
    }
    return node;
  }
  void inOrder(Node *node) {
    if (node == nullptr) {
      return;
    }
    inOrder(node->left);
    cout << node->data << " ";
    inOrder(node->right);
  }
  void preOrder(Node *node) {
    if (node == nullptr) {
      return;
    }
    cout << node->data << " ";
    preOrder(node->left);
    preOrder(node->right);
  }
  void postOrder(Node *node) {
    if (node == nullptr) {
      return;
    }
    postOrder(node->left);
    postOrder(node->right);
    cout << node->data << " ";
  }

 public:
  BST() { root = nullptr; }
  void insert(int value) { root = insertHelper(root, value); }
  void deleteNode(int value) { root = deleteHelper(root, value); }
  void inOrder() {
    inOrder(root);
    cout << "In-order " << endl << endl;
  }
  void preOrder() {
    preOrder(root);
    cout << "Pre-order " << endl << endl;
  }
  void postOrder() {
    postOrder(root);
    cout << "post-order " << endl << endl;
  }
};

struct Command{
  char operation;
  int value;
};

int main() {
  BST bst;

  string inputLine;
  vector<Command> commands;

  cout << "Enter: ";
  getline(cin, inputLine);
  stringstream ss(inputLine);
  string token;

  while(ss >> token){
    char operation = token[0];
    int value = stoi(token.substr(1));
    switch(operation){
      case 'I':
        bst.insert(value);
        break;
      case 'D':
        bst.deleteNode(value);
        break;
    }
  }
  bst.inOrder();
  bst.preOrder();
  bst.postOrder();

  return 0;
}