#include <iostream>
#include <cstring>
#include "List.h"
#include "Stack.h"
#include "Tree.h"

using namespace std;

char* printList(List* list);
List* postfix(char* input);
Tree* makeTree(List* &postFix);
void postfixTree(Node* input, List* &output);
void infix(Node* input, List* &output);
void prefix(Node* input, List* &output);

int main() {
  bool stillGoing = true;
  while (stillGoing == true) {
  //get mathmatical expression
  cout << "Input mathmatical expression or 'quit' to quit" << endl;
  char* input = new char[100];
  cin.get(input, 100);
  cin.get();
  //if wanna quit, do that
  if (strcmp(input, "quit") == 0) {
    cout << "Goodbye!" << endl;
    return 0;
  }
  //make sure no letters are in the input
  for (int i = 0; i < strlen(input); i++) {
    if (isalpha(input[i])) {
      cout << "invalid input" << endl;
      return 0;
    }
  }
  //get postFixForm list and print it out
  List* postfixForm = postfix(input);
  char* postFixChar = printList(postfixForm);
  cout << "Post Fix: " << postFixChar << endl;
  //create binary tree
  Tree* treeForm = makeTree(postfixForm);
  //print binary tree in postfix, infix, and prefix based on user input
  cout << "Would like to print postfix, infix, or prefix?" << endl;
  input = new char[15];
  cin.get(input, 15);
  cin.get();
  //make sure user input matches a form
  while (strcmp(input, "postfix") != 0 && strcmp(input, "prefix") != 0 && strcmp(input, "infix") != 0) {
    cout << "invalid input" << endl;
    cin.get(input, 15);
    cin.get();
  }
  //if user requested postfix, print that
  if (strcmp(input, "postfix") == 0) {
  List* postFixFormTree = new List();
  postfixTree(treeForm->getHead(), postFixFormTree);
  char* postFixTreeChar = printList(postFixFormTree);
  cout << "Post Fix: " << postFixTreeChar << endl;
  }
  //if user requested infix, print it
  if (strcmp(input, "infix") == 0) {
  List* infixForm = new List();
  infix(treeForm->getHead(), infixForm);
  char* infixChar = printList(infixForm);
  cout << "Infix: " << infixChar << endl;
  }
  //if prefix, do that
  if (strcmp(input, "prefix") == 0) {
  List* prefixForm = new List();
  prefix(treeForm->getHead(), prefixForm);
  char* prefixChar = printList(prefixForm);
  cout << "Prefix: " << prefixChar << endl;
  }
  }
  return 0;
}

//print out a list of nodes for postfix/prefix/infix
char* printList(List* list) {
  //make new char array to put the data from the list into
  char* postFixChar = new char[100];
  int count = 0;
  //run through each node in the list and add the data (number/operator) to the character array
  Node* currentNode = list->getFirst();
  while (currentNode != NULL) {
    for (int i = 0; i < strlen(currentNode->data); i++) {
      postFixChar[count] = currentNode->data[i];
      count++;
    }
     if (currentNode->next == NULL) {
       currentNode = NULL;
     }
     else {
       currentNode = currentNode->next;
     }
  }
  //return the character array
  return postFixChar;
}

//create postfix form using the stack
List* postfix(char* input) {
  //create an output list of nodes and a stack
  List* output = new List();
  Stack* stack = new Stack();
  //run through each number/operator and add it to the stack/add to output/pop stack and then add it/etc.
  for (int i = 0; i < strlen(input); i++) {
    //make new node and set the number/operator as the data portion of the node
    Node* newNode = new Node();
    (newNode->data) = new char[10];
    newNode->data[0] = input[i];
    int count = 1;
    //if there is a multi-digit number, add the remaining digits to the data portion of the node
    if (isdigit(input[i])) {
    while (isdigit(input[i+1])) {
      newNode->data[count] = input[i+1];
      i++;
      count++;
    }
      }
    newNode->data[count] = '\0';
    //if it's a number, move directly to output
    if (isdigit(input[i])) {
      output->addMem(newNode);
    }
    //if opening parenthesis, add to stack
    else if (input[i] == '(') {
      stack->push(newNode);
    }
    //if ending parenthesis, move everything from stack to output until encountering the opening parenthesis. Then, pop the opening parenthesis off the stack and delete that node cuz it's irrelevant now
    else if (input[i] == ')') {
      while (stack->getTop()->data[0] != '(') {
	Node* addNode = stack->pop();
	output->addMem(addNode);
	     
      }
      Node* parenthesis = stack->pop();
      delete parenthesis;
    }
    //if operator is ^, push to stack
    else if (input[i] == '^') {
	stack->push(newNode);
    }
    //if operator is multiplication or division, pop anything of equal or higher precedence on the top of the stack to the output, then push to the stack
    else if (input[i] == '*' || input[i] == 'x' || input[i] == '/') {
      if (stack->getTop() == NULL) {
	stack->push(newNode);
      }
      
      else if (stack->getTop()->data[0] == '/' || stack->getTop()->data[0] == '*' || stack->getTop()->data[0] == 'x' || stack->getTop()->data[0] == '^') {
	while (stack->getTop() != NULL && stack->getTop()->data[0] != '(' && stack->getTop()->data[0] != '+' && stack->getTop()->data[0] != '-') {
	  Node* newNode2 = stack->pop();
	  output->addMem(newNode2);
	}
	stack->push(newNode);
      }
      else {
	stack->push(newNode);
      }
    }
    //if addition of subtration, while the operator at the top of the stack is of greater of equal precedence (and not the same operator), pop the top of the stack and add to output. Then, push the add/subtract operator to the stack
    else if (input[i] == '-' || input[i] == '+') {
      if (stack->getTop() != NULL) {
      if (stack->getTop()->data[0] != input[i]) {
	while (stack->getTop() != NULL && stack->getTop()->data[0] != '(' && stack->getTop()->data[0] != input[i]) {
	  Node* newNode5 = stack->pop();
	output->addMem(newNode5);
      }
      }
      }
      stack->push(newNode);
    }
  }
  //when finished, move the rest of the stack to the output
  while (stack->getTop() != NULL) {
    Node* newNode3 = stack->pop();
    output->addMem(newNode3);
  }
  //return the output linked list!
  return output;
}

//make a binary expression tree from the linked list in postfix form
Tree* makeTree(List* &postFix) {
  //get the top node and make a stack
  Node* currentNode = postFix->getFirst();
  Stack* stack = new Stack();
  //while not at the end of the list
  while(currentNode != NULL) {
    //if the node is a number, push to stack
    if (isdigit(currentNode->data[0])) {
      stack->push(currentNode);
    }
    //if node is an operator, create a new tree in which the operator is the head node, and the top two nodes in the stack are the subnodes. Then, add the operator node to the stack
    else {
      Node* subRight = stack->pop();
      Node* subLeft = stack->pop();
      Tree* newTree = new Tree();
      newTree->addTree(currentNode, subLeft, subRight);
      stack->push(currentNode);
      //if this node is only node in the stack, this is the final tree. Return this tree.
      if (stack->getTop()->next == NULL && currentNode->next == NULL) {
	return newTree;
      }
    }
    //if the next node is null, set currentNode to NULL to end the loop
    if (currentNode->next == NULL) {
      currentNode = NULL;
    }
    //otherwise, move on to the next node in the list
    else {
      currentNode = currentNode->next;
    }
  }
  //error if the tree has not been returned by this point (which should not happen)
  cout << "error" << endl;
}

//postfix creation from the binary free. Adds to a linked list already established and uses the top node of a binary tree
void postfixTree(Node* input, List* &output) {
  //if the left node is an operator, run this function for that operator
  if (!isdigit(input->subL->data[0])) {
    postfixTree(input->subL, output);
  }
  //if the left node is a number, add it to the linked list
  if (isdigit(input->subL->data[0])) {
    output->addMem(input->subL);
  }
  //if the right node is an operator, run this function for that oeprator
  if(!isdigit(input->subR->data[0])) {
    postfixTree(input->subR, output);
  }
  //if the right node is a number, add it to the linked list
  if(isdigit(input->subR->data[0])) {
    output->addMem(input->subR);
  }
  //then, add the input (which will be an operator) to the stack
  output->addMem(input);
}

//infix notation w binary tree
void infix(Node* input, List* &output) {
  //if left node is an operator, rerun this function with that operator
  if (!isdigit(input->subL->data[0])) {
    infix(input->subL, output);
  }
  //if left node is a number
  if (isdigit(input->subL->data[0])) {
    //add number to list
    output->addMem(input->subL);
    //add operator to list
    output->addMem(input);
    //if the right node is an operator, run this function for that node
    if (!isdigit(input->subR->data[0])) {
      infix(input->subR, output);
    }
    //if right node is number, add to list
    if (isdigit(input->subR->data[0])) {
      output->addMem(input->subR);
    }
  }
  //if right node is an operator, add the current node (which is definitely an operator) to the list, then run this program for the right node
  if (!isdigit(input->subR->data[0])) {
    output->addMem(input);
    infix(input->subR, output);
  }
  //if right node is a number, add the operator input and then the number to the list
  if (isdigit(input->subR->data[0])) {
    output->addMem(input);
    output->addMem(input->subR);
  }
}

//prefix notation for binary tree
void prefix(Node* input, List* &output) {
  //add the current input (which should be an operator)
  output->addMem(input);
  //if left node is an operator, run this program for that node
  if (!isdigit(input->subL->data[0])) {

    prefix(input->subL, output);
  }
  //if left node is a number, add it to the list
  if (isdigit(input->subL->data[0])) {
    output->addMem(input->subL);
  }
  //if right node is an operator, run this for that node
  if (!isdigit(input->subR->data[0])) {
    prefix(input->subR, output);
  }
  //if right node is a number, add it to the list
  if (isdigit(input->subR->data[0])) {
    output->addMem(input->subR);
  }
}
