#ifndef NODE_H
#define NODE_H
#include "LinkedList.h"

template <typename E>
class Node
{
private:
	E elem;
	Node<E>* next;
	Node<E>* prev;

template <typename E1> friend class LinkedList;
};

#endif // NODE_H
