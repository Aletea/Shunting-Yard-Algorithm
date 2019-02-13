#ifndef STACK_H
#define STACK_H
#include "Node.h"
#include <iostream>

using namespace std;

class Stack {
 public:
  Stack();
  ~Stack();

  Node* getTop();
  void push(Node* newNode);
  Node* pop();

 private:
  Node* head;

};

#endif
