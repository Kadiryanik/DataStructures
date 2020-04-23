/*
 * Data Structures - Simple singly linked list implementation
 *
 * Copyright (C) Kadir Yanık - <kdrynkk@gmail.com>, 2020
 */
#include <iostream>
#include "LinkedList.h"

/*------------------------------------------------------------------------------*/
#include "Log.h"

#undef LOG_LEVEL
#ifndef LOG_LEVEL_CONF_LIST
#define LOG_LEVEL LOG_LEVEL_INFO
#else /* LOG_LEVEL_CONF_LIST */
#define LOG_LEVEL LOG_LEVEL_CONF_LIST
#endif /* LOG_LEVEL_CONF_LIST */

/*------------------------------------------------------------------------------*/
template <class T>
LinkedList<T>::LinkedList(){
  LOG_DBG("List Constructor\n");
  
  this->head = NULL;
  this->tail = NULL;
}

/*------------------------------------------------------------------------------*/
template <class T>
LinkedList<T>::~LinkedList(){
  LOG_DBG("List Deconstructor\n");

  while(head != NULL){
    remove(head);
  }
}

/*------------------------------------------------------------------------------*/
template <class T> Node<T>* 
LinkedList<T>::insert(T val){
  if(this->head == NULL){
    this->head = new Node<T>(val);
    this->tail = this->head;

    LOG_DBG("insert to head: %p\n", this->head);
    return this->head;
  } else{
    // allocate to end of list
    Node<T>* newNode = new Node<T>(val);

    if(newNode != NULL){
      // set current tail's next
      this->tail->next = newNode;

      // update tail
      this->tail = newNode;
    } else{
      LOG_ERR("insert: memory allocation failed!\n");
      return NULL;
    }

    LOG_DBG("insert: %p\n", newNode);
    return newNode;
  }
}

/*------------------------------------------------------------------------------*/
template <class T> Node<T>* 
LinkedList<T>::search(T val, bool walkForward){
  Node<T> *ptr = this->head;
  
  while(ptr != NULL){
    if(ptr->val() == val){
      return ptr;
    }
    ptr = ptr->next;
  }

  return NULL;
}

/*------------------------------------------------------------------------------*/
template <class T> void
LinkedList<T>::remove(Node<T> *node){
  if(node == NULL){
    LOG_WARN("remove: NULL pointer!\n");
    return;
  }

  LOG_DBG("remove: %p\n", node);

  // indirect pointer points to the address of the node we will update
  Node<T> **indirect = &head;

  // find the node on list
  while((*indirect) != node){
    indirect = &(*indirect)->next;
  }

  // just remove it, doesnt matter head, tail or any index
  *indirect = node->next;

  // clean up node
  delete node;
}
