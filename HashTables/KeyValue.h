#ifndef KEY_VALUE_H_
#define KEY_VALUE_H_

#include <string>
using namespace std;

/*------------------------------------------------------------------------------*/
class KeyValue{
  // TODO: may char array usable.
  string keyVar;
  void *valuePtr; // Points to any kind of data.
public:
  KeyValue();
  KeyValue(string key, void *value);
  ~KeyValue();

  void set(string key, void *value);
  string key();
  void* value();
};

#endif /* KEY_VALUE_H_ */
