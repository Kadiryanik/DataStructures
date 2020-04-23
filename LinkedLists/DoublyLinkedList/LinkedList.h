/*
 * Data Structures - Simple doubly linked list implementation
 *
 * Copyright (C) Kadir Yanık - <kdrynkk@gmail.com>, 2020
 */
#ifndef LINKED_LIST_H_
#define LINKED_LIST_H_

#include "Node.h"

/*------------------------------------------------------------------------------*/
template <class T>
class LinkedList{
  int itemCount;
  Node<T> *head;
  Node<T> *tail;
public:
  LinkedList();
  ~LinkedList();

  Node<T>* insert(T val);
  Node<T>* search(T val, bool walkForward = true);
  Node<T>* get(int index);
  void remove(Node<T> *node);
  int getItemCount();
};

#endif /* LINKED_LIST_H_ */
