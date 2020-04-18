#ifndef QUEUE_H_
#define QUEUE_H_

#define DEFAULT_QUEUE_SIZE 10

/*------------------------------------------------------------------------------*/
template <class T>
class Queue{
  T *queue;
  int queueSize;
  int queueEnqOffset;
  int queueDeqOffset;
  bool isFullVar;
public:
  Queue(int size = DEFAULT_QUEUE_SIZE);
  ~Queue();

  bool enqueue(T val);
  bool dequeue(T *ret);
  bool isEmpty();
  bool isFull();
  void clear();
  int getFreeNum();
};

#endif /* QUEUE_H_ */
