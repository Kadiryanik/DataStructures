#ifndef PERSON_H_
#define PERSON_H_

#include <string>
using namespace std;

/*------------------------------------------------------------------------------*/
class Person{
  string email;
  string firstName;
  string lastName;
  string companyName;
  string address;
  string city;
  string county;
  string postal;
  string phone1;
  string phone2;
  string web;
public:
  Person(string email = "", string firstName = "", string lastName = "", string companyName = "", \
    string address = "", string city = "", string county = "", string postal = "", \
    string phone1 = "", string phone2 = "", string web = "");
  ~Person();

  string key();
  string getEmail();
  void print();

  bool operator==(const Person &other);
};

#endif /* PERSON_H_ */
