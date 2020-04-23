/*
 * Data Structures - Key-value data type implementation
 *
 * Copyright (C) Kadir Yanık - <kdrynkk@gmail.com>, 2020
 */
#ifndef KEY_VALUE_H_
#define KEY_VALUE_H_

#include <string>
using namespace std;

/*------------------------------------------------------------------------------*/
class KeyValue{
  string keyVar;
  void *valuePtr; // Points to any kind of data.
public:
  KeyValue(string key = "", void *value = NULL);
  ~KeyValue();

  void set(string key, void *value);
  string key();
  void* value();

  bool operator==(const KeyValue &other);
  /* overload operator for deep copy */
  KeyValue& operator=(const KeyValue &other);
};

#endif /* KEY_VALUE_H_ */
