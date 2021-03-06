/*
 * Data Structures - Simple quadratic probing hash table implementation
 *
 * Copyright (C) Kadir Yanık - <kdrynkk@gmail.com>, 2020
 */
#ifndef HASH_TABLE_H_
#define HASH_TABLE_H_

#include "KeyValue.h"
#include "Bitmap.h"

/*------------------------------------------------------------------------------*/
class HashTable{
  /* Table ptr and size */
  KeyValue *table;
  int tableSize;
  int colUplimit;

  /* stores the which indexes is used or not used */
  Bitmap *bitmap;

  int hash(string key);
  int searchIndex(string key);
  bool insertStep(string key, void *ptr);
  bool remap(string key, void *ptr);

  void print();
public:
  HashTable(int tableSize, int colUplimit = 3);
  ~HashTable();

  bool insert(string key, void *ptr);
  bool remove(string key);
  void* search(string key);

  int getTableSize();
};

#endif /* HASH_TABLE_H_ */
