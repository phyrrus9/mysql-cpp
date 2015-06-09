/*
	dynamic linked list
*/

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

template <class T>
struct linkedListNode
{
	T data;
	linkedListNode<T> *next;
};

template <class T>
class linkedList
{
private:
	linkedListNode<T> *head, *tail;
	linkedListNode<T> *getNodeReference(unsigned int index)
	{
		linkedListNode<T> *n = head;
		for (unsigned int i = 0; i < index; i++, n = n->next)
			if (n == (linkedListNode<T> *)NULL) return n;
		return n;
	}
public:
	linkedList()
	{ head = tail = (linkedListNode<T> *)NULL; }
	~linkedList()
	{ while (head != (linkedListNode<T> *) NULL) remove(0); };
	void insert(T data)
	{
		linkedListNode<T> *node = new linkedListNode<T>;
		node->data = data;
		node->next = (linkedListNode<T> *)NULL;
		if (head != (linkedListNode<T> *)NULL) //list not empty
		{
			tail->next = node;
			tail = node;
		}
		else
			head = tail = node;
	}
	T *getReference(unsigned int index)
	{ return &getNodeReference(index)->data; }
	T get(unsigned int index)
	{ return *getReference(index); }
	void remove(unsigned int index)
	{
		linkedListNode<T> *parent, *node, *child;
		if (index == 0) //head node
		{
			node   = getNodeReference(index + 0),
			child  = getNodeReference(index + 1);
			head = child;
		}
		else
		{
			parent = getNodeReference(index - 1),
			node   = getNodeReference(index + 0),
			child  = getNodeReference(index + 1);
			parent->next = child; //update link
		}
		delete node; //remove data
	}
};

#endif

