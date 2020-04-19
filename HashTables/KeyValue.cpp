#include "KeyValue.h"

/*------------------------------------------------------------------------------*/
KeyValue::KeyValue(){
  this->keyVar = "";
  this->valuePtr = NULL;
}

/*------------------------------------------------------------------------------*/
KeyValue::KeyValue(string key, void *value){
  this->keyVar = key;
  this->valuePtr = value;
}

/*------------------------------------------------------------------------------*/
KeyValue::~KeyValue(){
  // do nothing
}

/*------------------------------------------------------------------------------*/
void
KeyValue::set(string key, void *value){
  this->keyVar = key;
  this->valuePtr = value;  
}

/*------------------------------------------------------------------------------*/
string 
KeyValue::key(){
  return this->keyVar;
}

/*------------------------------------------------------------------------------*/
void *
KeyValue::value(){
  return this->valuePtr;
}
