#ifndef BITMAP_H_
#define BITMAP_H_

#include <stdint.h>

/*------------------------------------------------------------------------------*/
class Bitmap{
  uint8_t *bitmap;
  int bitmapSize;
  int totalBits;
public:
  Bitmap(int count);
  ~Bitmap();

  bool isUsed(int index);
  bool set(int index);
  bool reset(int index);
  void clear();
  bool isFull();

  /* overload operator for deep copy */
  Bitmap& operator=(const Bitmap &other);
};

#endif /* BITMAP_H_ */
