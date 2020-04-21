#include <iostream>
#include "LinkedList.h"

/*------------------------------------------------------------------------------*/
// including for template defination linkage
#include "LinkedList.cpp"
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
  LOG_INFO("--Checking With Int--\n");
  LinkedList<int> list;

  for(int i = 0; i < 10; i++){
    list.insert(i);
  }

  // match test, searching with walkBackward
  int val = 5;
  LOG_INFO("Step-1: Searching[%d]: %p\n", val, list.search(val, false));
  // not match test
  val = 20;
  LOG_INFO("Step-2: Searching[%d]: %p\n", val, list.search(val));

  LOG_INFO("Step-3: Removing Items\n");
  // removing containing item test
  list.remove(list.search(8));
  // removing not containing item test
  list.remove(list.search(20));


  LOG_INFO("--Checking With Char--\n");
  // char tests
  LinkedList<char> listChar;

  listChar.insert('A');
  listChar.insert('E');
  listChar.insert('S');
  
  // match test
  char c = 'A';
  LOG_INFO("Step-1: Searching[%c]: %p\n", c, listChar.search(c));
  // not match test
  c = 'D';
  LOG_INFO("Step-2: Searching[%c]: %p\n", c, listChar.search(c));

  LOG_INFO("Step-3: Removing Items\n");
  // removing containing item test
  listChar.remove(listChar.search('A'));
  // removing not containing item test
  listChar.remove(listChar.search('T'));

  // lists not allocated dynamically so deconstructor will call end of main block
  return 0;
}
