#include <iostream>
#include "List.h"
#include "Node.h"

using namespace std;

List::List() {
  first = NULL;
}

List::~List() {
  first = NULL;
}

//add to end of list
void List::addMem(Node* newNode) {
  //if empty list, make first node in list
  if (first == NULL) {
    first = newNode;
    first->next = NULL;
    return;
  }
  //otherwise, run through list until you find the last node in the list, then set its next node to the node you're adding
  Node* currentNode = first;
  while (currentNode->next != NULL) {
    currentNode = currentNode->next;
  }
  currentNode->next = newNode;
  newNode->next = NULL;
}

Node* List::getFirst() {
  return first;
}
