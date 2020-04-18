#include <iostream>
#include "Stack.h"

/*------------------------------------------------------------------------------*/
// including for template defination linkage
#include "Stack.cpp"

/*------------------------------------------------------------------------------*/
#include "Log.h"

#undef LOG_LEVEL
#ifndef LOG_LEVEL_CONF_TEST
#define LOG_LEVEL LOG_LEVEL_INFO
#else /* LOG_LEVEL_CONF_TEST */
#define LOG_LEVEL LOG_LEVEL_CONF_TEST
#endif /* LOG_LEVEL_CONF_TEST */

/*------------------------------------------------------------------------------*/
#define USE_DEFAULT_STACK_SIZE 0

/*------------------------------------------------------------------------------*/
int 
main(int argc, char *argv[]){
#if USE_DEFAULT_STACK_SIZE
  Stack<int> *stack = new Stack<int>(); // Using default stack size
#else /* USE_DEFAULT_STACK_SIZE */
  Stack<int> *stack = new Stack<int>(5); // Setting stack size to 5
#endif /* USE_DEFAULT_STACK_SIZE */

  // try to get while empty stack
  int val;
  if(stack->pop(&val)){
    LOG_INFO("pop succeed %d\n", val);
  } else{
    LOG_INFO("pop failed\n");
  }

  // try to push 10 item
  for(int i = 0; i < 10; i++){
    stack->push(i);
  }

  if(stack->isFull()){
    LOG_INFO("Stack Full!\n");
  }

  // peek test
  if(stack->peek(&val)){
    LOG_INFO("peek succeed: %d\n", val);
  } else{
    LOG_INFO("peek failed\n");
  }

  // pop test
  while(!(stack->isEmpty())){
    if(stack->pop(&val)){
      LOG_INFO("pop succeed: %d\n", val);
    } else{
      LOG_INFO("pop failed\n");
    }
  }

  // while loop pops all item in stack, trying pop when stack empty again
  if(stack->pop(&val)){
    LOG_INFO("pop succeed: %d\n", val);
  } else{
    LOG_INFO("pop failed\n");
  }

  // clean up
  delete stack;

  return 0;
}
