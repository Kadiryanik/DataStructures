#ifndef SINGLY_LINKED_LIST_H_
#define SINGLY_LINKED_LIST_H_

#include "Node.h"

/*------------------------------------------------------------------------------*/
template <class T>
class SinglyLinkedList{
  Node<T> *head;
  Node<T> *tail;
public:
  SinglyLinkedList();
  ~SinglyLinkedList();

  Node<T>* insert(T val);
  Node<T>* search(T val);
  void remove(Node<T> *node);
};

#endif /* SINGLY_LINKED_LIST_H_ */
