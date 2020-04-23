/*
 * Data Structures - Simple circular linked list implementation
 *
 * Copyright (C) Kadir Yanık - <kdrynkk@gmail.com>, 2020
 */
#include <iostream>
#include <unistd.h>
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

    // point head's next and prev to head
    this->head->prev = this->head;
    this->head->next = this->head;

    LOG_DBG("insert to head: %p\n", this->head);
    return this->head;
  } else{
    // allocate to end of list
    Node<T>* newNode = new Node<T>(val);

    if(newNode != NULL){
      // add new-node as head-prev
      this->head->prev->next = newNode;

      // set new-node-prev to current head-prev
      newNode->prev = this->head->prev;

      // set new-node-next to head
      newNode->next = this->head;

      // finally set head-prev to new-node
      this->head->prev = newNode;
    } else{
      LOG_ERR("insert: memory allocation failed!\n");
      return NULL;
    }

    LOG_DBG("insert: %p<-%p->%p\n", newNode->prev, newNode, newNode->next);
    return newNode;
  }
}

/*------------------------------------------------------------------------------*/
template <class T> Node<T>* 
LinkedList<T>::search(T val, bool walkForward){
  Node<T> *ptr = this->head;
  
  if(walkForward){
    while(ptr != NULL){
      if(ptr->val() == val){
        return ptr;
      }

      ptr = ptr->next;
      if(ptr == this->head){
        // we are back to the head, all nodes checked 
        break;
      }
    }
  } else{ // walkBackward
    while(ptr != NULL){
      if(ptr->val() == val){
        return ptr;
      }

      ptr = ptr->prev;
      if(ptr == this->head){
        // we are back to the head, all nodes checked 
        break;
      }
    }
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

  LOG_DBG("remove: %p .. %p<-%p->%p\n", head, node->prev, node, node->next);
  
  // indirect pointer points to the address of the node we will update
  Node<T> **indirect = &head;

  // find the node on list
  while((*indirect) != node){
    indirect = &(*indirect)->next;
  }

  // next one is pointing node, this mean there is only one node
  if((*indirect)->next == node){
    this->head = NULL; // which is head
  } else{
    // link the removing nodes prev-next to node->next
    (*indirect)->prev->next = node->next;

    // just remove it, doesnt matter head or any index
    *indirect = node->next;

    // circular list doesn't has NULL ptr so do not check and
    // set current prev to removing node prev
    (*indirect)->prev = node->prev;
  }

  
  // clean up node
  delete node;
}
