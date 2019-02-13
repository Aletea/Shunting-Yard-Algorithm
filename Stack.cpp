#include <iostream>
#include "Stack.h"
#include "Node.h"

using namespace std;

Stack::Stack() {
  head = NULL;
}

Stack::~Stack() {
  head = NULL;
}

//return top of stack
Node* Stack::getTop() {
  return head;
}

//add a node to stack
void Stack::push(Node* newNode) {
  //create new node to add to stack
  Node* addNode = new Node();
  addNode->data = newNode->data;
  addNode->subL = newNode->subL;
  addNode->subR = newNode->subR;
  //set as first node if stack empty
  if (head == NULL) {
    head = addNode;
    head->next = NULL;
    return;
  }
  //otherwise, set as top of stack
  else {
    addNode->next = head;
    head = addNode;
  }
}
//remove top node from stack and return it
Node* Stack::pop() {
  //get top node, reset top node, make the node your returning's next node NULL
  Node* top = head;
  head = head->next;
  top->next = NULL;
  return top;
}
