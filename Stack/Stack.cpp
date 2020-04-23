/*
 * Data Structures - Simple stack implementation
 *
 * Copyright (C) Kadir Yanık - <kdrynkk@gmail.com>, 2020
 */
#include <iostream>
#include <cstdlib>
#include "Stack.h"

/*------------------------------------------------------------------------------*/
#include "Log.h"

#undef LOG_LEVEL
#ifndef LOG_LEVEL_CONF_STACK
#define LOG_LEVEL LOG_LEVEL_INFO
#else /* LOG_LEVEL_CONF_STACK */
#define LOG_LEVEL LOG_LEVEL_CONF_STACK
#endif /* LOG_LEVEL_CONF_STACK */

/*------------------------------------------------------------------------------*/
template <class T>
Stack<T>::Stack(int size){
  LOG_DBG("Stack Constructor\n");
  
  this->stack = new T[size];
  if(this->stack == NULL){
    LOG_ERR("Stack allocation failed!\n");
    exit(-1);
  }

  this->stackSize = size;
  this->stackOffset = 0;
}

/*------------------------------------------------------------------------------*/
template <class T>
Stack<T>::~Stack(){
  LOG_DBG("Stack Deconstructor\n");

  if(this->stack != NULL){
    delete [] this->stack;
  }
}

/*------------------------------------------------------------------------------*/
template <class T> bool
Stack<T>::push(T val){
  if(!isFull()){
    stack[++(this->stackOffset)] = val;
    return true;
  }

  LOG_WARN("Stack full!\n");
  return false;
}

/*------------------------------------------------------------------------------*/
template <class T> bool
Stack<T>::pop(T *ret){
  if(!isEmpty() && ret != NULL){
    (*ret) = stack[this->stackOffset--];
    return true;
  }

  LOG_WARN("Stack empty!\n");
  return false;
}

/*------------------------------------------------------------------------------*/
template <class T> bool
Stack<T>::peek(T *ret){
  if(!isEmpty() && ret != NULL){
    (*ret) = stack[this->stackOffset];
    return true;
  }

  LOG_WARN("Stack empty!\n");
  return false;
}

/*------------------------------------------------------------------------------*/
template <class T> bool
Stack<T>::isEmpty(){
  if(this->stackOffset == 0){
    LOG_DBG("Stack empty!\n");
    return true;
  }

  return false;
}

/*------------------------------------------------------------------------------*/
template <class T> bool
Stack<T>::isFull(){
  if(this->stackOffset < this->stackSize){
    return false;
  }

  LOG_DBG("Stack full!\n");
  return true;
}

/*------------------------------------------------------------------------------*/
template <class T> void
Stack<T>::clear(){
  this->stackOffset = 0;
}