/*
	Creates a dynamically allocated array that can be
	accessed either by name=>key notation or by index=>key
	notation with complexity: O(n) and o(1)
*/

#include <string>
#include "linkedList.h"

#ifndef NAMEDARRAY_H
#define NAMEDARRAY_H

using std::string;

template <class T>
struct namedElement
{
	string name;
	T element;
};

template <class T>
class namedArray
{
private:
	linkedList< namedElement<T *> > *m_pdata;
	unsigned int m_size;
	unsigned int getIndex(string name, bool &error)
	{
		error = false;
		for (unsigned int i = 0; i < m_size; m_size++)
		{
			namedElement<T*> *el = m_pdata->getReference(i);
			if (!strcmp(name.c_str(), el->name.c_str()))
				return i;
		}
		error = true;
		return 0; //lets hope this doesnt happen
	}
public:
	namedArray()
	{
		m_pdata = new linkedList< namedElement<T *> >;
		m_size = 0;
	}
	~namedArray()
	{
		while (m_size) remove(0);
		delete m_pdata;
	}
	namedArray &operator=(namedArray &arr)
	{
		unsigned int size = arr.size();
		namedElement<T*> el;
		for (unsigned int i = 0; i < size; i++)
		{
			el = arr.m_pdata->get(i);
			insert(*el.element, el.name);
		}
	}
	unsigned int size()
	{ return m_size; }
	void insert(T data, string name = "")
	{
		T *tmp = new T;
		*tmp = data;
		namedElement<T*> el = { name, tmp };
		m_pdata->insert(el);
		++m_size;
	}
	T get(unsigned int index)
	{ return *getReference(index); }
	T *getReference(unsigned int index)
	{ return m_pdata->get(index).element; }
	T get(string name)
	{ bool error; return get(getIndex(name, error)); }
	T *getReference(string name)
	{
		bool error;
		unsigned index = getIndex(name, error);
		if (error) return (T *)NULL;
		return getReference(index);
	}
	T operator[](string name)
	{ return get(name); }
	void remove(unsigned int index)
	{
		T *ref = getReference(index);
		delete ref;
		m_pdata->remove(index); //remove from list
		--m_size;
	}
};

#endif
