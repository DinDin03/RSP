#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

struct Node { // Create a structure called Node which has 3 member variables
  int data; // Stores the actual data of the node
  Node *left, *right; // Two nodes one for the left child and one for the right child

  Node(int key) { // Default constructor which will take a parameter called key   
    data = key; // Make the data of the node equal to the key 
    left = right = nullptr; // make the left and child be null pointers initially
  }
};

class BST { // Create a class called BST for the binary search tree
 private: // Private variables and methods
  Node *root; // A node called root which will be the root of the tree 
  Node *insertHelper(Node *node, int value) { // A helper function for Insert function which takes a node and a integer value
    if (node == nullptr) { // If the node is null pointer meaning we reached a leaf position in the tree
      return new Node(value); // create and return a new node with the given value
    }
    if (value < node->data) { // If the value to be inserted is less than the value of the current node
      node->left = insertHelper(node->left, value); // recusrively call the function to the left subtree 
    } else if (value > node->data) { // or if the value to be inserted is greatert than the value of the current node
      node->right = insertHelper(node->right, value); // recusrively call the function to the right subtree
    }
    return node; // if the value is equal to the current node's value, no insertions occur since duplications are not allowed in BST. Function returns the node
  }
  Node *findMin(Node *node) { // Function to find the minimum value in the tree
    while (node->left != nullptr) { // Iterate the left tree until a leaf is reached. The smallest node in the tree is the left most node in the tree
      node = node->left; // iterate through the left nodes
    }
    return node; // Return the node with the smallest value
  }
  Node *deleteHelper(Node *node, int value) { // A helper function to delete a node which takes a node and an int value
    if (node == nullptr) { // if the node is null, the value does not exist in the tree
      return nullptr; // return null to indicate no change
    }
    if (value < node->data) { // if the value to be deleted is less than the value of the current node
      node->left = deleteHelper(node->left, value); // recursively call the functin on the left subtree
    } else if (value > node->data) { // If the value to be deleted is greater than the value of the current node
      node->right = deleteHelper(node->right, value); // recursively call the function on the right subtree
    } else { // If the current node's value match the node to be deleted
      if (node->left == nullptr) { // If the node to be deleted has no left child
        Node *temp = node->right; // create a temporary node which points to the right child
        delete node; // delete the current node
        return temp; // return the right child to replace the deleted node
      }
      if (node->right == nullptr) { // If the node to be deleted has no right child
        Node *temp = node->left; // Create a temporary node which stores the left child of the node
        delete node; // Delete the current node
        return temp; // Return the left child to replace the deleted node
      }
      Node *temp = findMin(node->right); // find the minimum node in the right subtree, which will be the in order successor and store it to temp
      node->data = temp->data; // copy the data of the minimum node to the current node
      node->right = deleteHelper(node->right, temp->data); // recursively delete the in order successor
    }
    return node; // return the current node to reconnect the modified subtree to the rest of the tree
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