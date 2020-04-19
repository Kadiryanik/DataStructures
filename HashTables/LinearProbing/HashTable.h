#ifndef HASH_TABLE_H_
#define HASH_TABLE_H_

#include "KeyValue.h"
#include "Bitmap.h"

/*------------------------------------------------------------------------------*/
class HashTable{
  /* Table ptr and size */
  KeyValue *table;
  int tableSize;

  /* stores the which indexes is used or not used */
  Bitmap *bitmap;

  int hash(string key);
  int searchIndex(string key);
public:
  HashTable(int tableSize);
  ~HashTable();

  bool insert(string key, void *ptr);
  bool remove(string key);
  void* search(string key);
};

#endif /* HASH_TABLE_H_ */
