#include "utility.h"
#include <stdio.h>
//=============================//
//=============================//
/* class Node starts from here */
//=============================//
//=============================//
template <class Node_entry>
struct Node
{
	Node_entry entry;
	Node<Node_entry> *next;

	Node();
	Node(Node_entry, Node<Node_entry> *link = NULL);
};

template <class Node_entry>
Node<Node_entry>::Node()
{
	next = NULL;
}

template <class Node_entry>
Node<Node_entry>::Node(Node_entry x, Node<Node_entry> *link)
{
	entry = x;
	next = link;
}

//=================================//
//=================================//
/* class linklist starts from here */
//=================================//
//=================================//

template <class List_entry>
class Linklist
{
public:
	Linklist();
	void clear();
	bool empty()const;
	bool full()const;
	int size()const;
	void traverse(void (*visit)(List_entry &));
	Error_code insert(int position, const List_entry &x);
	Error_code remove(int position, List_entry &x);
	Error_code retrieve(int position, List_entry &x)const;
	Error_code replace(int position, const List_entry &x);
	~Linklist();
	Linklist(const Linklist<List_entry> &copy);
	void operator = (const Linklist<List_entry> &copy);
protected:
	int count;
	Node<List_entry> *head;
	Node<List_entry> *set_position(int position)const;
};

template <class List_entry>
Node<List_entry> *Linklist<List_entry>::set_position(int position)const
{
	Node<List_entry> *q = head;
	for(int i = 0; i < position; i++) q = q->next;
	return q;
}

template <class List_entry>
Linklist<List_entry>::Linklist()
{
	count = 0;
	head = NULL;
}

template <class List_entry>
void Linklist<List_entry>::clear()
{
	Node<List_entry> *p = head;
	while(p != NULL)
	{
		Node<List_entry> *q = p;
		p = p->next;
		delete q;
	}
	head = NULL;
	count = 0;
}

template <class List_entry>
bool Linklist<List_entry>::empty()const
{
	return count == 0;
}

template <class List_entry>
bool Linklist<List_entry>::full()const
{
	return false;
}

template <class List_entry>
int Linklist<List_entry>::size()const
{
	return count;
}

template <class List_entry>
void Linklist<List_entry>::traverse(void (*visit)(List_entry &))
{
	Node<List_entry> *p = head;
	while(p != NULL)
	{
		(*visit)(p->entry);
		p = p->next;
	}
}

template <class List_entry>
Error_code Linklist<List_entry>::retrieve(int position, List_entry &x)const
{
	if(position < 0 || position >= count) return range_error;
	else
	{
		Node<List_entry> *p;
		p = set_position(position);
		x = p->entry;
		return success;
	}
}

template <class List_entry>
Error_code Linklist<List_entry>::replace(int position, const List_entry &x)
{
	if(position < 0 || position >= count) return range_error;
	else
	{
		Node<List_entry> *p;
		p = set_position(position);
		p->entry = x;
		return success;
	}
}

template <class List_entry>
Error_code Linklist<List_entry>::remove(int position, List_entry &x)
{
	if(empty()) return underflow;
	if(position < 0 || position >= count) return range_error;
	else if(position == 0)		
	{
		if(count == 1)		
		{
			Node<List_entry> *p = set_position(0);
			x = p->entry;
			delete p;
			count = 0;
			head = NULL;
		}
		else		
		{
			Node<List_entry> *p = set_position(0);
			x = p->entry;
			head = p->next;
			delete p;
			count--;
		}
	}
	else		
	{
		Node<List_entry> *p;
		p = set_position(position-1);	
		Node<List_entry> *q = p->next;
		x = q->entry;
		p->next = q->next;
		delete q;
		count--;
	}
	return success;
}

template <class List_entry>
Error_code Linklist<List_entry>::insert(int position, const List_entry &x)
{
	if(position < 0 || position > count) return range_error;
	Node<List_entry> *new_node , *previous, *following;
	if(position > 0)
	{
		previous = set_position(position-1);
		following = previous->next;
	}
	else following = head;
	new_node = new Node<List_entry>(x,following);
	if(new_node == NULL) return overflow;
	
	if(position == 0) head = new_node;
	else previous->next = new_node;
	
	count++;
	
	return success;
}

template <class List_entry>
Linklist<List_entry>::~Linklist()
{
	Node<List_entry> *p;
	while(head != NULL)
	{
		p = head;
		head = head->next;
		delete p;
	}
	head = NULL;
	count = 0;
}

template <class List_entry>
Linklist<List_entry>::Linklist(const Linklist<List_entry> &copy)
{
	count = 0;
	head = NULL;

	Node<List_entry> *p;
	for(int i = 0; i < copy.size(); i++)
	{
		p = copy.set_position(i);
		insert(i,p->entry);
	}
}

template <class List_entry>
void Linklist<List_entry>::operator= (const Linklist<List_entry> &copy)
{
	clear();
	Node<List_entry> *p;
	for(int i = 0; i < copy.size(); i++)
	{
		p = copy.set_position(i);
		insert(i,p->entry);
	}
}
