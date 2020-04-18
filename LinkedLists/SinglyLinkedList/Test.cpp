#include <iostream>
#include "SinglyLinkedList.h"

/*------------------------------------------------------------------------------*/
// including for template defination linkage
#include "SinglyLinkedList.cpp"
#include "Node.cpp"

/*------------------------------------------------------------------------------*/
#include "Log.h"

#undef LOG_LEVEL
#ifndef LOG_LEVEL_CONF_TEST
#define LOG_LEVEL LOG_LEVEL_INFO
#else /* LOG_LEVEL_CONF_TEST */
#define LOG_LEVEL LOG_LEVEL_CONF_TEST
#endif /* LOG_LEVEL_CONF_TEST */

/*------------------------------------------------------------------------------*/
int 
main(int argc, char *argv[]){
  SinglyLinkedList<int> list;

  for(int i = 0; i < 10; i++){
    list.insert(i);
  }

  // match test
  int val = 5;
  LOG_INFO("Searching[%d]: %p\n", val, list.search(val));
  // not match test
  val = 20;
  LOG_INFO("Searching[%d]: %p\n", val, list.search(val));

  LOG_INFO("Removing Items\n");
  // removing containing item test
  list.remove(list.search(8));
  // removing containing item test
  list.remove(list.search(20));

  // char tests
  SinglyLinkedList<char> listChar;

  list.insert('A');
  list.insert('E');
  list.insert('S');

  // match test
  char c = 'A';
  LOG_INFO("Searching[%c]: %p\n", c, list.search(c));
  // not match test
  c = 'D';
  LOG_INFO("Searching[%c]: %p\n", c, list.search(c));

  LOG_INFO("Removing Items\n");
  // removing containing item test
  list.remove(list.search('A'));
  // removing containing item test
  list.remove(list.search('T'));

  // list not allocated dynamically so deconstructor will call end of main block
  return 0;
}