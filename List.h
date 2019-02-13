#ifndef LIST_H
#define LIST_H
#include "Node.h"
#include <iostream>

using namespace std;

class List {
 public:
  List();
  ~List();

  void addMem(Node* newNode);
  Node* getFirst();

 private:
  Node* first;


};
#endif
