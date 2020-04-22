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
  /* INFO: colUplimit not used in this collision handling 
   * technique initialized for common usage */
  HashTable(int tableSize, int colUplimit = 3);
  ~HashTable();

  bool insert(string key, void *ptr);
  bool remove(string key);
  void* search(string key);

  int getTableSize();
};

#endif /* HASH_TABLE_H_ */
