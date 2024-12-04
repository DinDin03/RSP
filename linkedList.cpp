#include <iostream>
using namespace std;

struct Node {
  int data;
  Node* next;

  Node() {
    data = 0;
    next = nullptr;
  }
};

class LinkedList {
 private:
  Node* head;

 public:
  LinkedList() { head = nullptr; }

  void insertAtBeginning(int value) {
    Node* newNode = new Node();
    newNode->data = value;
    newNode->next = head;
    head = newNode;
  }

  void insertAtEnd(int value) {
    Node* newNode = new Node();
    newNode->data = value;
    newNode->next = nullptr;
    Node* temp = head;
    while (temp->next != nullptr) {
      temp = temp->next;
    }
    temp->next = newNode;
  }

  void insertAtPosition(int value, int position) {
    Node* newNode = new Node();
    newNode->data = value;
    Node* temp = head;
    for (int i = 1; i < position - 1; i++) {
      temp = temp->next;
    }
    newNode->next = temp->next;
    temp->next = newNode;
  }

  void deleteFromBeginning() {
    Node* temp = head;
    head = head->next;
    delete temp;
  }

  void deleteFromEnd() {
    Node* temp = head;
    while (temp->next->next != nullptr) {
      temp = temp->next;
    }
    temp->next = nullptr;
    delete temp->next;
  }

  void deleteFromPosition(int position) {
    Node* temp = head;
    for (int i = 1; i < position - 1; i++) {
      temp = temp->next;
    }
    Node* nodeToDelete = temp->next;
    temp->next = temp->next->next;
    delete nodeToDelete;
  }

  void display() {
    Node* temp = head;
    while (temp != nullptr) {
      cout << temp->data << " ";
      temp = temp->next;
    }
    cout << "NULL" << endl;
  }

  void findAndDelete(int value) {
    Node* temp = head;
    while (temp->next != nullptr && temp->next->data != value) {
      temp = temp->next;
    }
    Node* nodeToDelete = temp->next;
    temp->next = temp->next->next;  // Skip the node to be deleted
    delete nodeToDelete;
  }
};

void displayMenu() {
  cout << "1: Insert at the beginning" << endl;
  cout << "2: Insert at the end" << endl;
  cout << "3: Insert at position" << endl;
  cout << "4: Delete at the beginning" << endl;
  cout << "5: Delete at the end" << endl;
  cout << "6: Delete at position" << endl;
  cout << "7: Find and delete" << endl;
  cout << "-1: Exit" << endl;
  cout << "Enter your option: ";
}

int getUserInput() {
  int option;
  cin >> option;
  return option;
}

int main() {
  LinkedList list;
  int option = 0, value, position;
  displayMenu();

  while (option != -1) {
    option = getUserInput();
    switch (option) {
      case 1:

        cout << "What's the value: ";
        cin >> value;
        list.insertAtBeginning(value);
        list.display();
        break;
      case 2:
        cout << "What's the value: ";
        cin >> value;
        list.insertAtEnd(value);
        list.display();
        break;
      case 3:
        cout << "What's the value: ";
        cin >> value;
        cout << "What's the position: ";
        cin >> position;
        list.insertAtPosition(value, position);
        list.display();
        break;
      case 4:
        list.deleteFromBeginning();
        list.display();
        break;
      case 5:
        list.deleteFromEnd();
        list.display();
        break;
      case 6:
        cout << "What's the position: ";
        cin >> position;
        list.deleteFromPosition(position);
        list.display();
        break;
      case 7:
        cout << "Enter the value: ";
        cin >> value;
        list.findAndDelete(value);
        list.display();
        break;
      case -1:
        list.display();
        return 0;
    }
    displayMenu();
  }
}
