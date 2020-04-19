#include <iostream>
#include "Person.h"

/*------------------------------------------------------------------------------*/
#include "Log.h"

#undef LOG_LEVEL
#ifndef LOG_LEVEL_CONF_PERSON
#define LOG_LEVEL LOG_LEVEL_INFO
#else /* LOG_LEVEL_CONF_PERSON */
#define LOG_LEVEL LOG_LEVEL_CONF_PERSON
#endif /* LOG_LEVEL_CONF_PERSON */

/*------------------------------------------------------------------------------*/
Person::Person(string name, string surname, int age){
  this->name = name;
  this->surname = surname;
  this->age = age;
}

/*------------------------------------------------------------------------------*/
Person::~Person(){
  // do nothing
}

/*------------------------------------------------------------------------------*/
string 
Person::key(){
  string key(this->name + this->surname + to_string(this->age));
  return key;
}

/*------------------------------------------------------------------------------*/
void 
Person::print(){
  LOG_INFO("PersonInfo\n");
  LOG_INFO_("  Ptr     : %p\n", this);
  LOG_INFO_("  Name    : %s\n", this->name.c_str());
  LOG_INFO_("  Surname : %s\n", this->surname.c_str());
  LOG_INFO_("  Age     : %d\n", this->age);
}
