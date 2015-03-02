#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include"Node.h"
#include <cstdlib>
#include <iostream>
using std::cout;
using std::endl;

template <typename E>
class LinkedList
{
public:
	LinkedList();
	~LinkedList();

    void createList(const E& e);
	const E& getFront() const;
	void addToFront(const E& e);
	void removeFromFront();
	bool isEmpty() const;
	void resetToFront();
	void resetToEnd();
	bool hasNextItem();
	const E& getNode() const;
	void advItrFor();
	void advItrBack();
	void printListForward();
	void printListBackward();
	Node<E>* insertionSort(Node<E>* head);
	Node<E>* getHead();
	Node<E>* retrieve(int index);

private:
	Node<E>* head;
	Node<E>* itr;
};

template <typename E>
LinkedList<E>::LinkedList()
{
	head = NULL;
	itr = head;
}

template <typename E>
LinkedList<E>::~LinkedList()
{
	while (!isEmpty()) {
		removeFromFront();
	}
}

template <typename E>
void LinkedList<E>::createList(const E& e) {
    Node<E>* node = new Node<E>;
    node->elem = e;
    node->next = NULL;
    if (head == NULL) {
        node->prev = NULL;
        head = node;
    }
}

template <typename E>
const E& LinkedList<E>::getFront() const {
	return head->elem;
}

template <typename E>
void LinkedList<E>::addToFront(const E& e) {
	Node<E>* node = new Node <E> ;
	node->elem = e;
	node->prev = NULL;
	node->next = head;
	head->prev = node;
	head = node;
	if (itr == NULL) {
		itr = head;
	}
}

template <typename E>
void LinkedList<E>::removeFromFront() {
	Node<E>* old = head;
	if (!isEmpty()) {
		head = old->next;
		if (itr == old) {
			itr = head;
		}
		delete old;
	}
}

template <typename E>
bool LinkedList<E>::isEmpty() const {
	return head == NULL;
}

template <typename E>
void LinkedList<E>::resetToFront() {
	itr = head;
}

template <typename E>
void LinkedList<E>::resetToEnd() {
    while (itr->next != NULL) {
        advItrFor();
    }
}

template <typename E>
bool LinkedList<E>::hasNextItem() {
	return (itr != NULL ? true : false);
}

template <typename E>
const E& LinkedList<E>::getNode() const {
	if (itr != NULL) {
		return itr->elem;
	}
	else {
        //return;// NULL;
	}
}

template <typename E>
void LinkedList<E>::advItrFor() {
	if (itr != NULL) {
		itr = itr->next;
	}
}

template <typename E>
void LinkedList<E>::advItrBack() {
	if (itr != NULL) {
		itr = itr->prev;
	}
}

template <typename E>
void LinkedList<E>::printListForward() {
    if (!isEmpty()) {
        while (hasNextItem()) {
            cout << "Element: " << getNode() << endl;
            advItrFor();
        }
	}
}

template <typename E>
void LinkedList<E>::printListBackward() {
    if (!isEmpty()) {
        while (hasNextItem()) {
            cout << "Element: " << getNode() << endl;
            advItrBack();
        }
	}
}

template <typename E>
Node<E>* LinkedList<E>::insertionSort(Node<E>* head) {

    if (head == NULL) {
        return head;
    }

    Node<E> *unsorted = head;

    while (unsorted != NULL) {
        Node<E> *prev = NULL;
        Node<E> *itr = head;
        Node<E> *key = unsorted;

        while (itr != NULL) {
            if (itr->elem < key->elem) {
                prev = itr;
                itr = itr->next;
            }
            else {
                break;
            }
        }
        unsorted = unsorted->next;

        if (itr == key) {
            continue;
        }

        Node<E> *place = itr;

        while (itr->next != key) {
            itr = itr->next;
        }
        itr->next = unsorted;

        if (prev == NULL) {
            head = key;
        }
        else {
            prev->next = key;
        }
        key->next = place;
    }
    //return head;


}

template <typename E>
Node<E>* LinkedList<E>::getHead() {
    return head;
}

template <typename E>
Node<E>* LinkedList<E>::retrieve(int index) {
    resetToFront();
    for (int i = 0; i < index; i++) {
        advItrFor();
    }
    return itr;
}

#endif // LINKEDLIST_H
