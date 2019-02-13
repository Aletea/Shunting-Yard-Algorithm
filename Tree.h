#ifndef TREE_H
#define TREE_H
#include <iostream>
#include "Node.h"

using namespace std;

class Tree {
 public:
  Tree();
  ~Tree();
  void addTree(Node* &newNode, Node* subLeft, Node* subRight);
  Node* getHead();
  Node* getLeft();
  Node* getRight();
  
 private:
  Node* head;


};

#endif
