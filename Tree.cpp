#include <iostream>
#include "Node.h"
#include "Tree.h"

using namespace std;

Tree::Tree() {
  head = NULL;
}

Tree::~Tree() {
  head = NULL;
}

//make new tree by creating a head node and setting left and right
void Tree::addTree(Node* &newNode, Node* subLeft, Node*subRight) {
  newNode->subL = subLeft;
  newNode->subR = subRight;
  head = newNode;
}

//return top node of tree
Node* Tree::getHead() {
  return head;
}

//return the top node of the tree's left node
Node* Tree::getLeft() {
  return head->subL;
}

//same as above for right node
Node* Tree::getRight() {
  return head->subR;
}
