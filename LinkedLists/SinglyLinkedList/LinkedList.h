/*
 * Data Structures - Simple singly linked list implementation
 *
 * Copyright (C) Kadir Yanık - <kdrynkk@gmail.com>, 2020
 */
#ifndef LINKED_LIST_H_
#define LINKED_LIST_H_

#include "Node.h"

/*------------------------------------------------------------------------------*/
template <class T>
class LinkedList{
  Node<T> *head;
  Node<T> *tail;
public:
  LinkedList();
  ~LinkedList();

  Node<T>* insert(T val);
  // walkForward parameter not used, added for common library
  Node<T>* search(T val, bool walkForward = true);
  void remove(Node<T> *node);
};

#endif /* LINKED_LIST_H_ */
