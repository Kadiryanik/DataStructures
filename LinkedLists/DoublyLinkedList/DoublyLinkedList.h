#ifndef DOUBLY_LINKED_LIST_H_
#define DOUBLY_LINKED_LIST_H_

#include "Node.h"

/*------------------------------------------------------------------------------*/
template <class T>
class DoublyLinkedList{
  Node<T> *head;
  Node<T> *tail;
public:
  DoublyLinkedList();
  ~DoublyLinkedList();

  Node<T>* insert(T val);
  Node<T>* search(T val, bool walkForward = true);
  void remove(Node<T> *node);
};

#endif /* DOUBLY_LINKED_LIST_H_ */
