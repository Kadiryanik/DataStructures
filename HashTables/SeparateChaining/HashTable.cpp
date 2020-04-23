/*
 * Data Structures - Simple separate chaining hash table implementation
 *
 * Copyright (C) Kadir Yanık - <kdrynkk@gmail.com>, 2020
 */
#include <iostream>
#include <cstdlib>
#include "HashTable.h"

// including for template defination linkage
#include "LinkedList.cpp"
#include "Node.cpp"

/*------------------------------------------------------------------------------*/
#include "Log.h"

#undef LOG_LEVEL
#ifndef LOG_LEVEL_CONF_HASH_TABLE
#define LOG_LEVEL LOG_LEVEL_INFO
#else /* LOG_LEVEL_CONF_HASH_TABLE */
#define LOG_LEVEL LOG_LEVEL_CONF_HASH_TABLE
#endif /* LOG_LEVEL_CONF_HASH_TABLE */

/*------------------------------------------------------------------------------*/
HashTable::HashTable(int tableSize, int colUplimit){
  LOG_DBG("HashTable Constructor\n");
  
  this->tableSize = tableSize;
  this->colUplimit = colUplimit;
  this->table = new LinkedList<KeyValue>[tableSize];

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
  if(!(this->insertStep(key, ptr))){
    // remap the table
    return this->remap(key, ptr);
  }

  return true;
}

/*------------------------------------------------------------------------------*/
bool
HashTable::remove(string key){
  int index = this->hash(key);

  if(index < this->tableSize){
    LOG_DBG("remove[%d][%d] = \"%s\"\n", index, 
      this->table[index].getItemCount(), key.c_str());

    /* key value == operator checks only key, so create pair with 
     * only key and remove pair from list */
    KeyValue pair(key);
    this->table[index].remove(this->table[index].search(pair));

    bool ret = true;
    if(this->table[index].getItemCount() == 0){
      // if list empty reset bitmap too
      ret = this->bitmap->reset(index);
    }
    return ret;
  }

  LOG_INFO("Key \"%s\" not found on table for removing!\n", key.c_str());
  return false;
}

/*------------------------------------------------------------------------------*/
void *
HashTable::search(string key){
  int index = this->hash(key);

  /* key value == operator checks only key, so create pair with 
   * only key and search pair in list */
  KeyValue pair(key);
  Node<KeyValue> *node = this->table[index].search(pair);

  if(node != NULL){
    // get node value which contain KeyValue pair
    pair = node->val();
    // return KeyValue pair's value
    return pair.value();
  }

  LOG_INFO("Key \"%s\" not found on table!\n", key.c_str());
  return NULL;
}

/*------------------------------------------------------------------------------*/
int 
HashTable::getTableSize(){
  return this->tableSize;
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
bool
HashTable::insertStep(string key, void *ptr){
  int index = this->hash(key);

  int itemCount = this->table[index].getItemCount();
  if(itemCount < this->colUplimit){
    KeyValue pair(key, ptr);
    if(this->table[index].insert(pair) == NULL){
      LOG_ERR("table[%d].insert failed!\n", index);
      exit(-1);
    }
  } else{
    // colUplimit exceeded, return false for remapping
    return false;
  }

  LOG_DBG("insert[%d][%d] = \"%s\"\n", index, itemCount, key.c_str());

  // set bitmap both case (new insertion or not)
  this->bitmap->set(index);

  // insert succceed
  return true;
}

/*------------------------------------------------------------------------------*/
bool
HashTable::remap(string key, void *ptr){
  bool succceed = false;
  int remappingSizeMultiplier = 2;
  HashTable *hashTable;
  
  while(true){
    LOG_WARN("HashTable remapping %d * %d!\n", this->tableSize, 
                                                remappingSizeMultiplier);
    hashTable = new HashTable(this->tableSize * remappingSizeMultiplier);

    // insert last failed first
    hashTable->insertStep(key, ptr);

    succceed = true; // set flag before start
    for(int i = 0; i < this->tableSize; i++){
      // if item used
      if(this->bitmap->isUsed(i)){
        // insert old items to new hashTable
        for(int j = 0; j < this->table[i].getItemCount(); j++){
          Node<KeyValue> *node = this->table[i].get(j);

          if(node != NULL){
            // get node value which contain KeyValue pair
            KeyValue pair = node->val();

            if(!hashTable->insertStep(pair.key(), pair.value())){
              // failed to insert set flag for retry
              succceed = false;

              // break both loop
              i = this->tableSize;
              break;
            }
          } else{
            // didin't expect
            LOG_ERR("FatalError-1: something wrong!\n");
            break;
          }
        }
      }
    }

    if(succceed){
      break; // remapping succeed
    } else{
      remappingSizeMultiplier++;
      delete hashTable; // remapping failed try again
    }
  }

  // clean up this table
  if(this->table != NULL) delete [] this->table;

  // reallocate table
  this->tableSize = hashTable->tableSize;
  this->table = new LinkedList<KeyValue>[this->tableSize];
  if(this->table == NULL){
    LOG_ERR("HashTable allocation failed!\n");
    exit(-1);
  }

  // copy new table to this
  for(int i = 0; i < hashTable->tableSize; i++){
    for(int j = 0; j < hashTable->table[i].getItemCount(); j++){
      Node<KeyValue> *node = hashTable->table[i].get(j);

      if(node != NULL){
        KeyValue pair = node->val();
        this->table[i].insert(pair);
      } else{
        // didin't expect
        LOG_ERR("FatalError-2: something wrong!\n");
        break;
      }
    }
  }

  /* copy new bitmap to this
   * make sure = operator overloaded for deep copy in Bitmap class. */
  *(this->bitmap) = (*(hashTable->bitmap));

  // clean up copy
  delete hashTable;

  LOG_INFO("HashTable remapping succceed!\n");
  // TODO: returns allways true, may retry counter usable for trying to remap
  return true;
}
