#include "KeyValue.h"

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

/*------------------------------------------------------------------------------*/
bool 
KeyValue::operator==(const KeyValue &other){
  if(this->keyVar.compare(other.keyVar) == 0){
    return true;
  }

  return false;
}

/*------------------------------------------------------------------------------*/
KeyValue& 
KeyValue::operator=(const KeyValue &other){
  this->keyVar = other.keyVar;
  this->valuePtr = other.valuePtr;

  // returning itself
  return *this;
}
