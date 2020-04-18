#include <iostream>
#include "Node.h"

/*------------------------------------------------------------------------------*/
#include "Log.h"

#undef LOG_LEVEL
#ifndef LOG_LEVEL_CONF_NODE
#define LOG_LEVEL LOG_LEVEL_INFO
#else /* LOG_LEVEL_CONF_NODE */
#define LOG_LEVEL LOG_LEVEL_CONF_NODE
#endif /* LOG_LEVEL_CONF_NODE */

/*------------------------------------------------------------------------------*/
template <class T>
Node<T>::Node(T value){
  LOG_DBG("Node Constructor\n");

  this->value = value;
  this->next = NULL;
}

/*------------------------------------------------------------------------------*/
template <class T>
Node<T>::~Node(){
  LOG_DBG("Node Deconstructor\n");
  // do nothing
}

/*------------------------------------------------------------------------------*/
template <class T> T 
Node<T>::val(){
  return this->value;
}
