#ifndef CIRCULAR_LINKED_LIST_H_
#define CIRCULAR_LINKED_LIST_H_

#include "Node.h"

/*------------------------------------------------------------------------------*/
template <class T>
class CircularLinkedList{
  Node<T> *head;
public:
  CircularLinkedList();
  ~CircularLinkedList();

  Node<T>* insert(T val);
  Node<T>* search(T val, bool walkForward = true);
  void remove(Node<T> *node);
};

#endif /* CIRCULAR_LINKED_LIST_H_ */
