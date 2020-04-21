#ifndef NODE_H_
#define NODE_H_

/*------------------------------------------------------------------------------*/
template <class T>
class Node{
  T value;
public:
  Node *next;
  Node *prev;

  Node(T = 0);
  ~Node();
  T val();
};

#endif /* NODE_H_ */
