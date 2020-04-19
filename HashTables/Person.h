#ifndef PERSON_H_
#define PERSON_H_

#include <string>
using namespace std;

/*------------------------------------------------------------------------------*/
class Person{
  string name;
  string surname;
  int age;
public:
  Person(string name, string surname, int age);
  ~Person();

  string key();
  void print();
};

#endif /* PERSON_H_ */
