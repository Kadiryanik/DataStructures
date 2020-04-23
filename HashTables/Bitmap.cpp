/*
 * Data Structures - Simple bitmap implementation
 *
 * Copyright (C) Kadir Yanık - <kdrynkk@gmail.com>, 2020
 */
#include <cstdlib>
#include "Bitmap.h"

/*------------------------------------------------------------------------------*/
#include "Log.h"

#undef LOG_LEVEL
#ifndef LOG_LEVEL_CONF_BITMAP
#define LOG_LEVEL LOG_LEVEL_INFO
#else /* LOG_LEVEL_CONF_BITMAP */
#define LOG_LEVEL LOG_LEVEL_CONF_BITMAP
#endif /* LOG_LEVEL_CONF_BITMAP */

/*------------------------------------------------------------------------------*/
Bitmap::Bitmap(int count){
  this->bitmapSize = (count / 8) + (((count % 8) > 0) ? 1 : 0);
  this->totalBits = count;

  this->bitmap = new uint8_t[this->bitmapSize];
  if(this->bitmap == NULL){
    LOG_ERR("Bitmap allocation failed!\n");
    exit(-1);
  }
  // clear the bitmap
  this->clear();

  LOG_DBG("Bitmap initialized %d bit with %d map size\n", this->totalBits, 
                                                           this->bitmapSize);
}

/*------------------------------------------------------------------------------*/
Bitmap::~Bitmap(){
  if(bitmap != NULL){
    delete [] bitmap;
  }
}

/*------------------------------------------------------------------------------*/
bool
Bitmap::isUsed(int index){
  if(index < this->totalBits){
    int bitmapIndex = index / 8;
    uint8_t mask = 0x80 >> (index % 8); // set the bit point 1 and others 0
  
    if(this->bitmap[bitmapIndex] & mask){
      return true;  // used
    } else{
      return false; // not used
    }
  }

  // index not valid, returning true mean this bit is used, forcing the pass
  return true;
}

/*------------------------------------------------------------------------------*/
bool
Bitmap::set(int index){
  if(index < this->totalBits){
    int bitmapIndex = index / 8;
    uint8_t mask = 0x80 >> (index % 8); // set the bit point 1 and others 0
  
    this->bitmap[bitmapIndex] |= mask;
    return true;
  }

  return false;
}

/*------------------------------------------------------------------------------*/
bool
Bitmap::reset(int index){
  if(index < this->totalBits){
    int bitmapIndex = index / 8;
    uint8_t mask = ~(0x80 >> (index % 8)); // set the bit point 0 and others 1
  
    this->bitmap[bitmapIndex] &= mask;
    return true;
  }

  return false;
}

/*------------------------------------------------------------------------------*/
void
Bitmap::clear(){
  for(int i = 0; i < this->bitmapSize; i++){
    bitmap[i] = 0;    
  }
}


/*------------------------------------------------------------------------------*/
bool 
Bitmap::isFull(){
  for(int i = 0; i < this->bitmapSize - 1; i++){
    if(this->bitmap[i] != 0xFF){
      return false; // not full
    }
  }

  // if reach here check last byte
  uint8_t mask = 0;
  for(int i = 0; i < (this->totalBits % 8); i++){
    mask |= (0x80 >> (i % 8));
  }
  if(this->bitmap[this->bitmapSize - 1] != mask){
    return false; // not full
  }

  // if reach here mean bitmap full
  return true;
}

/*------------------------------------------------------------------------------*/
Bitmap& 
Bitmap::operator=(const Bitmap &other){
  // if allocated before clean up memory
  if(this->bitmap != NULL) delete [] this->bitmap;

  // copy the variables
  this->bitmapSize = other.bitmapSize;
  this->totalBits = other.totalBits;

  // try to allocate
  this->bitmap = new uint8_t[this->bitmapSize];
  if(this->bitmap == NULL){
    LOG_ERR("Bitmap allocation failed! (operaor=)\n");
    exit(-1);
  }

  // copy the bitmap array
  for(int i = 0; i < this->bitmapSize; i++){
    this->bitmap[i] = other.bitmap[i];
  }

  // returning itself
  return *this;
}
