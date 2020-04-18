#include <iostream>
#include <cstdlib>
#include "Queue.h"

/*------------------------------------------------------------------------------*/
#include "Log.h"

#undef LOG_LEVEL
#ifndef LOG_LEVEL_CONF_QUEUE
#define LOG_LEVEL LOG_LEVEL_INFO
#else /* LOG_LEVEL_CONF_QUEUE */
#define LOG_LEVEL LOG_LEVEL_CONF_QUEUE
#endif /* LOG_LEVEL_CONF_QUEUE */

/*------------------------------------------------------------------------------*/
template <class T>
Queue<T>::Queue(int size){
  LOG_DBG("Queue Constructor\n");
  
  this->queue = new T[size];
  if(this->queue == NULL){
    LOG_ERR("Queue allocation failed!\n");
    exit(-1);
  }

  this->queueSize = size;
  this->clear();
}

/*------------------------------------------------------------------------------*/
template <class T>
Queue<T>::~Queue(){
  LOG_DBG("Queue Deconstructor\n");

  if(this->queue != NULL){
    delete [] this->queue;
  }
}

/*------------------------------------------------------------------------------*/
template <class T> bool
Queue<T>::enqueue(T val){
  if(!this->isFullVar){
    queue[this->queueEnqOffset] = val;
    LOG_DBG("enqueue[%d] .. ", this->queueEnqOffset);
    this->queueEnqOffset = (this->queueEnqOffset + 1) % this->queueSize;
    LOG_DBG_("new offset [%d]\n", this->queueEnqOffset);

    if(this->queueEnqOffset == this->queueDeqOffset){
      // set flag
      isFullVar = true;
    }
    return true;
  }

  LOG_WARN("Queue full!\n");
  return false;
}

/*------------------------------------------------------------------------------*/
template <class T> bool
Queue<T>::dequeue(T *ret){
  if(!isEmpty() && ret != NULL){
    if(this->queueEnqOffset == this->queueDeqOffset){
      // release flag
      isFullVar = false;
    }

    (*ret) = queue[this->queueDeqOffset];
    LOG_DBG("dequeue[%d] .. ", this->queueDeqOffset);
    this->queueDeqOffset = (this->queueDeqOffset + 1) % this->queueSize;
    LOG_DBG_("new offset %d\n", this->queueDeqOffset);
    return true;
  }

  LOG_WARN("Queue empty!\n");
  return false;
}

/*------------------------------------------------------------------------------*/
template <class T> bool
Queue<T>::isEmpty(){
  if(this->queueEnqOffset == this->queueDeqOffset && !isFullVar){
    LOG_DBG("Queue empty!\n");
    return true;
  }

  return false;
}

template <class T> bool
Queue<T>::isFull(){
  return isFullVar;
}

/*------------------------------------------------------------------------------*/
template <class T> void
Queue<T>::clear(){
  this->queueEnqOffset = 0;
  this->queueDeqOffset = 0;
  this->isFullVar = false;
}

/*------------------------------------------------------------------------------*/
template <class T> int
Queue<T>::getFreeNum(){
  int ret;
  if(this->queueEnqOffset == this->queueDeqOffset){
    if(this->isFullVar){
      ret = 0;
    } else{
      ret = this->queueSize;
    }
  } else if(this->queueEnqOffset > this->queueDeqOffset){
    ret = this->queueEnqOffset - this->queueDeqOffset;
  } else{
    ret = this->queueEnqOffset + this->queueSize - this->queueDeqOffset;
  }

  return ret;
}
