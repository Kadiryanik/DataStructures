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
HashTable::HashTable(int tableSize, int colUplimit){
  LOG_DBG("HashTable Constructor\n");
  
  this->tableSize = tableSize;
  this->colUplimit = colUplimit;
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
  if(!(this->insertStep(key, ptr))){
    // remap the table
    return this->remap(key, ptr);
  }

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
int
HashTable::searchIndex(string key){
  int index = this->hash(key);
  int i = 1, startPointIndex = index;
  int collisionCount = 0;

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
    index = (index + (i * i)) % this->tableSize;

    collisionCount++;
    i++; // increase i and continue

    /* continue until reach colUplimit or index != startPointIndex, 
     * index == startPointIndex mean we are in index-loop */
  } while(startPointIndex != index && collisionCount < this->colUplimit); 

  // if reach here all table checked and not found
  return this->tableSize; // return unvalid index
}

/*------------------------------------------------------------------------------*/
bool
HashTable::insertStep(string key, void *ptr){
  int index = this->hash(key);
  int i = 1, startPointIndex = index;
  int collisionCount = 0;

  // find empty index
  while(this->bitmap->isUsed(index)){
    LOG_DBG("Collision: for key \"%s\" index %d\n", key.c_str(), index);
    index = (index + (i * i)) % this->tableSize;

    // increase collision count before check
    collisionCount++;

    /* continue until reach colUplimit or index != startPointIndex, 
     * index == startPointIndex mean we are in index-loop */
    if(collisionCount >= this->colUplimit){
      LOG_DBG("CollisionCount exceeded. Trying to remap!\n");
      return false;
    } else if(index == startPointIndex){
      LOG_DBG("Index-loop. Trying to remap!\n");
      return false;
    }

    i++; // increase i and continue
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
        // insert old item to new hashTable
        if(!hashTable->insertStep(this->table[i].key(), this->table[i].value())){
          // failed to insert set flag for retry
          succceed = false;
          break;
        }
      }
    }

    if(succceed){
      break; // remapping succeed
    } else{
      delete hashTable; // remapping failed try again
      remappingSizeMultiplier++;
    }
  }

  // clean up this table
  if(this->table != NULL) delete [] this->table;

  // reallocate table
  this->tableSize = hashTable->tableSize;
  this->table = new KeyValue[this->tableSize];
  if(this->table == NULL){
    LOG_ERR("HashTable allocation failed!\n");
    exit(-1);
  }

  // copy new table to this
  for(int i = 0; i < hashTable->tableSize; i++){
    this->table[i].set(hashTable->table[i].key(), hashTable->table[i].value());
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
