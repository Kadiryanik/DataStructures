/*
 * Data Structures - Simple stack implementation
 *
 * Copyright (C) Kadir Yanık - <kdrynkk@gmail.com>, 2020
 */
#ifndef STACK_H_
#define STACK_H_

#define DEFAULT_STACK_SIZE 10

/*------------------------------------------------------------------------------*/
template <class T>
class Stack{
  T *stack;
  int stackSize;
  int stackOffset;
public:
  Stack(int size = DEFAULT_STACK_SIZE);
  ~Stack();

  bool push(T val);
  bool pop(T *ret);
  bool peek(T *ret);
  bool isEmpty();
  bool isFull();
  void clear();
};

#endif /* STACK_H_ */
