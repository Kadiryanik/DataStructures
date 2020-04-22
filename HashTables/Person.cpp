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
Person::Person(string email, string firstName, string lastName, \
    string companyName, string address, string city, string county, \
    string postal, string phone1, string phone2, string web){
  this->email = email;
  this->firstName = firstName;
  this->lastName = lastName;
  this->companyName = companyName;
  this->address = address;
  this->city = city;
  this->county = county;
  this->postal = postal;
  this->phone1 = phone1;
  this->phone2 = phone2;
  this->web = web;
}

/*------------------------------------------------------------------------------*/
Person::~Person(){
  // do nothing
}

/*------------------------------------------------------------------------------*/
string 
Person::key(){
  // email must be unique, could be add any other field too
  return this->email;
}

/*------------------------------------------------------------------------------*/
string 
Person::getEmail(){
  return this->email;
}

/*------------------------------------------------------------------------------*/
void 
Person::print(){
  LOG_INFO("PersonInfo\n");
  LOG_DBG(" Ptr      : %p\n", this);
  LOG_INFO(" FirstName: %s\n", this->firstName.c_str());
  LOG_INFO(" LastName : %s\n", this->lastName.c_str());
  LOG_INFO(" Company  : %s\n", this->companyName.c_str());
  LOG_INFO(" Address  : %s\n", this->address.c_str());
  LOG_INFO(" City     : %s\n", this->city.c_str());
  LOG_INFO(" County   : %s\n", this->county.c_str());
  LOG_INFO(" Postal   : %s\n", this->postal.c_str());
  LOG_INFO(" Phone1   : %s\n", this->phone1.c_str());
  LOG_INFO(" Phone2   : %s\n", this->phone2.c_str());
  LOG_INFO(" Email    : %s\n", this->email.c_str());
  LOG_INFO(" Web      : %s\n", this->web.c_str());
}

/*------------------------------------------------------------------------------*/
bool 
Person::operator==(const Person &other){
  // email must be unique
  if(this->email.compare(other.email) == 0){
    return true;
  }

  return false;
}