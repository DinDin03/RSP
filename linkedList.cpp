#include <iostream>
using namespace std;

struct Node { // Create a structure called Node which has 2 member variables data and next
  int data; // Data stores the actual data representing the node
  Node* next; // Next is a type of Node which stores the next Node pointed by the current node 

  Node() { // Default constructor for Node. This will be called when a node is created 
    data = 0; // Set the value of the node to 0 
    next = nullptr; // Set the next pointer to null
  }
};

class LinkedList { // Class called linkedList 
 private:
  Node* head; // Stores a private member called head which stores the current head of the linked list

 public:
  LinkedList() { head = nullptr; } // Default constructor for LinkedList which sets the head to NULL. List is empty

  void insertAtBeginning(int value) { // Function to insert a value at the beginning of the list
    Node* newNode = new Node(); // Create a new Node called newNode
    newNode->data = value; // Set the data of newly created newNode to the value that we pass as a parameter 
    newNode->next = head; // Set the next node of the newNode to point to the 'current' head
    head = newNode; // update the head to the newNode since we want to insert this at the beginning. newNode will become the head of the list
  }

  void insertAtEnd(int value) { // Function to insert a value at the end of the list
    Node* newNode = new Node(); // Create a new node called newNode
    newNode->data = value; // set the data of the newNode to be the value that we pass as a parameter
    newNode->next = nullptr; // set the next pointer of the newNode to be the null pointer since we are adding it at the end of the list 
    Node* temp = head; // create a temporary node called temp which will be the head of the node
    while (temp->next != nullptr) { // iterate through the list until the last element before the null pointer
      temp = temp->next; // increment. ie make the temp node point to the next node of the list
    }
    temp->next = newNode; // since we want to insert at the end, the element before the nullpointer should now point to the newNode we created
    delete temp; // delete temp to free memory
  }

  void insertAtPosition(int value, int position) { // Function to insert a value at any poisition, takes 2 paramters one for value and one for position
    Node* newNode = new Node(); // create a new Node called newNode
    newNode->data = value; // make the data of the newNode be the value that we pass
    Node* temp = head; // Create a temporary node which is set to the head of the list
    for (int i = 1; i < position - 1; i++) { // iterate through the list until the element before the desired position
      temp = temp->next; // Increment the temp
    }
    newNode->next = temp->next; // set the next of the newNode to point to the desired poisiton
    temp->next = newNode; // update the next of the previous position to point to the new Node
  }

  void deleteFromBeginning() { // Function to delete a node from the beginning of the list
    Node* temp = head; // Create a temporary node which points to the head of the list
    head = head->next; // Set the head to point to the next head, meaning set the next node after the head the new head
    delete temp; // Delete the head by freeing memory
  }

  void deleteFromEnd() { // function to delete a node from the end of a list
    Node* temp = head; // Create a temporary node which points to the head of the list
    while (temp->next->next != nullptr) { // iterate trough the list until the node before the last element, so two nodes before the null pointer 
      temp = temp->next; // Increment temp by pointing to the next node
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
