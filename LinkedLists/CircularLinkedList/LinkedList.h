#ifndef LINKED_LIST_H_
#define LINKED_LIST_H_

#include "Node.h"

/*------------------------------------------------------------------------------*/
template <class T>
class LinkedList{
  Node<T> *head;
public:
  LinkedList();
  ~LinkedList();

  Node<T>* insert(T val);
  Node<T>* search(T val, bool walkForward = true);
  void remove(Node<T> *node);
};

#endif /* LINKED_LIST_H_ */
