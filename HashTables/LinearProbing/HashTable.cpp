#include <iostream>
#include <cstdlib>
#include "HashTable.h"

/*------------------------------------------------------------------------------*/
#include "Log.h"

#undef LOG_LEVEL
#ifndef LOG_LEVEL_CONF_HASH_TABLE
#define LOG_LEVEL LOG_LEVEL_INFO
#else /* LOG_LEVEL_CONF_HASH_TABLE */
#define LOG_LEVEL LOG_LEVEL_CONF_HASH_TABLE
#endif /* LOG_LEVEL_CONF_HASH_TABLE */

/*------------------------------------------------------------------------------*/
HashTable::HashTable(int tableSize){
  LOG_DBG("HashTable Constructor\n");
  
  this->tableSize = tableSize;
  this->table = new KeyValue[tableSize];
  if(this->table == NULL){
    LOG_ERR("HashTable allocation failed!\n");
    exit(-1);
  }

  // Bitmap constructor exits if allocation failed
  this->bitmap = new Bitmap(tableSize);
}

/*------------------------------------------------------------------------------*/
HashTable::~HashTable(){
  LOG_DBG("HashTable Deconstructor\n");
  if(this->table != NULL){
    delete [] this->table;
  }

  if(this->bitmap != NULL){
    delete this->bitmap;
  }
}

/*------------------------------------------------------------------------------*/
bool
HashTable::insert(string key, void *ptr){
  int index = this->hash(key);

  // check is there any space
  if(bitmap->isFull()){
    LOG_WARN("Trying to insert already full table: key=\"%s\"\n", key.c_str());
    return false;
  }

  // find empty index
  while(this->bitmap->isUsed(index)){
    LOG_DBG("Collision: for key \"%s\" index %d\n", key.c_str(), index);
    index = (index + 1) % this->tableSize;
  }

  LOG_DBG("insert[%d] = \"%s\"\n", index, key.c_str());

  // set table and bitmap as used
  this->table[index].set(key, ptr);
  this->bitmap->set(index);

  // insert succceed
  return true;
}

/*------------------------------------------------------------------------------*/
bool
HashTable::remove(string key){
  int index = this->searchIndex(key);

  if(index < this->tableSize){
    LOG_DBG("remove[%d] = \"%s\"\n", index, key.c_str());
    this->table[index].set("", NULL);
    return this->bitmap->reset(index);
  }

  LOG_INFO("Key \"%s\" not found on table for removing!\n", key.c_str());
  return false;
}

/*------------------------------------------------------------------------------*/
void *
HashTable::search(string key){
  int index = this->searchIndex(key);

  if(index < this->tableSize){
    // return KeyValue pair's value
    return this->table[index].value();
  }

  LOG_INFO("Key \"%s\" not found on table!\n", key.c_str());
  return NULL;
}

/*------------------------------------------------------------------------------*/
/*-----------------------------PRIVATE-FUNCTIONS--------------------------------*/
/*------------------------------------------------------------------------------*/
int 
HashTable::hash(string key){
  int hash = 0;
  for(unsigned int i = 0; i < key.length(); i++){
    hash += (i + (int)key[i]);
  }

  return hash % this->tableSize;
}

/*------------------------------------------------------------------------------*/
int
HashTable::searchIndex(string key){
  int index = this->hash(key);
  int startPointIndex = index;

  do{
    // if index used
    if(this->bitmap->isUsed(index)){
      // check key matches
      if(key.compare(this->table[index].key()) == 0){
        return index;
      }

      LOG_DBG("Searching \"%s\" key not matched in index %d trying next!\n", 
        key.c_str(), index);
    }

    // set index to next
    index = (index + 1) % this->tableSize;
  } while(startPointIndex != index); /* end when index reached again 
                                      * the startPointIndex, this mean 
                                      * we checked every item on table */

  // if reach here all table checked and not found
  return this->tableSize; // return unvalid index
}
