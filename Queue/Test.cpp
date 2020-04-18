#include <iostream>
#include "Queue.h"

/*------------------------------------------------------------------------------*/
// including for template defination linkage
#include "Queue.cpp"

/*------------------------------------------------------------------------------*/
#include "Log.h"

#undef LOG_LEVEL
#ifndef LOG_LEVEL_CONF_TEST
#define LOG_LEVEL LOG_LEVEL_INFO
#else /* LOG_LEVEL_CONF_TEST */
#define LOG_LEVEL LOG_LEVEL_CONF_TEST
#endif /* LOG_LEVEL_CONF_TEST */

/*------------------------------------------------------------------------------*/
#define USE_DEFAULT_QUEUE_SIZE 0

/*------------------------------------------------------------------------------*/
static void
checkAndPrint(Queue<int> *queue){
  int val;
  if(queue->dequeue(&val)){
    LOG_INFO("dequeue succeed: %d\n", val);
  } else{
    LOG_INFO("dequeue failed\n");
  }
}

/*------------------------------------------------------------------------------*/
int 
main(int argc, char *argv[]){
#if USE_DEFAULT_QUEUE_SIZE
  Queue<int> *queue = new Queue<int>(); // Using default queue size
#else /* USE_DEFAULT_QUEUE_SIZE */
  Queue<int> *queue = new Queue<int>(5); // Setting queue size to 5
#endif /* USE_DEFAULT_QUEUE_SIZE */

  // try to get while queue is empty
  LOG_INFO("Step-0: get 1 item\n");
  checkAndPrint(queue);

  LOG_INFO("Step-1: add 10 item\n");
  // try to push 10 item
  for(int i = 0; i < 10; i++){
    queue->enqueue(i);
  }

  LOG_INFO("Step-2: get 2 item, free num: %d\n", queue->getFreeNum());
  // get 2 items
  for(int i = 0; i < 2; i++){
    checkAndPrint(queue);
  }
  
  LOG_INFO("Step-3: add 1 item\n");
  // add 1 item  
  queue->enqueue(10);
  
  LOG_INFO("Step-4: get 1 item\n");
  // get 1 item
  checkAndPrint(queue);

  LOG_INFO("Step-5: add 4 item\n");
  // add 4 item
  queue->enqueue(11);
  queue->enqueue(12);
  queue->enqueue(13);
  queue->enqueue(14);

  LOG_INFO("Step-6: get all item\n");
  // get all item
  while(!(queue->isEmpty())){
    checkAndPrint(queue);
  }

  // queue not allocated dynamically so deconstructor will call end of main block
  return 0;
}
