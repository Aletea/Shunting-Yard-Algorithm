#ifndef NODE_H
#define NODE_H
#include <iostream>

using namespace std;


struct Node{
  Node* next = NULL;
  Node* subL = NULL;
  Node* subR = NULL;
  char* data = NULL;
};

#endif
