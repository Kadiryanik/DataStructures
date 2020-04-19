#include <iostream>
#include "HashTable.h"
#include "Person.h"

/*------------------------------------------------------------------------------*/
#include "Log.h"

#undef LOG_LEVEL
#ifndef LOG_LEVEL_CONF_TEST
#define LOG_LEVEL LOG_LEVEL_INFO
#else /* LOG_LEVEL_CONF_TEST */
#define LOG_LEVEL LOG_LEVEL_CONF_TEST
#endif /* LOG_LEVEL_CONF_TEST */

/*------------------------------------------------------------------------------*/
static void
searchAndLog(HashTable *hashTable, string str){
  void *ptr = hashTable->search(str);
  if(ptr != NULL){
    Person *person = (Person *)ptr;
    person->print();
  } else{
    LOG_INFO("\"%s\" not found\n", str.c_str());
  }
}

/*------------------------------------------------------------------------------*/
int 
main(int argc, char *argv[]){
  // define all person
  Person p1("Jones", "Williams", 55);
  Person p2("Davies", "Taylor", 30);
  Person p3("Thomas", "Johnson", 45);
  Person p4("Roberts", "Walker", 10);
  Person p5("Wright", "Robinson", 20);
  Person p6("Thompson", "White", 25);
  Person p7("Hughes", "Edwards", 18);

  // TODO: try with 1000 person and searh performance test with hashTable or not

  // init hashTable
  HashTable *hashTable = new HashTable(5);

  LOG_INFO("Step-1: Inserting\n");
  // insert items to table
  hashTable->insert(p1.key(), (void *)&p1);
  hashTable->insert(p2.key(), (void *)&p2);
  hashTable->insert(p3.key(), (void *)&p3);
  hashTable->insert(p4.key(), (void *)&p4);
  hashTable->insert(p5.key(), (void *)&p5);

  // this will fail, hash table size equal 5
  hashTable->insert(p6.key(), (void *)&p6);
  hashTable->insert(p7.key(), (void *)&p7);

  LOG_INFO("Step-2: Searching\n");
  // try to find via key
  searchAndLog(hashTable, p1.key());
  searchAndLog(hashTable, p2.key());
  searchAndLog(hashTable, p3.key());
  searchAndLog(hashTable, p4.key());
  searchAndLog(hashTable, p5.key());
  searchAndLog(hashTable, p6.key());
  searchAndLog(hashTable, p7.key());

  LOG_INFO("Step-3: Removing\n");
  // remove 2 person
  hashTable->remove(p1.key());
  hashTable->remove(p3.key());

  LOG_INFO("Step-4: Inserting\n");
  // insert 2 person
  hashTable->insert(p6.key(), (void *)&p6);
  hashTable->insert(p7.key(), (void *)&p7);

  LOG_INFO("Step-5: Searching\n");
  // look again
  searchAndLog(hashTable, p1.key());
  searchAndLog(hashTable, p3.key());
  searchAndLog(hashTable, p6.key());
  searchAndLog(hashTable, p7.key());

  // clean up
  delete hashTable;

  return 0;
}
