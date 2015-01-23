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
	Node<Node_entry> *back;

	Node();
	Node(Node_entry, Node<Node_entry> *link_back = NULL, 
					 Node<Node_entry> *link_next = NULL);
};

template <class Node_entry>
Node<Node_entry>::Node()
{
	next = back = NULL;
}

template <class Node_entry>
Node<Node_entry>::Node(Node_entry x, Node<Node_entry> *l_back, Node<Node_entry> *l_next)
{
	entry = x;
	next = l_next;
	back = l_back;
}

//=======================================//
//=======================================//
/* class DoubleLinklist starts from here */
//=======================================//
//=======================================//

template <class List_entry>
class DoubleLinklist
{
public:
	DoubleLinklist();
	void clear();
	int size()const;
	bool empty()const;
	bool full()const;
	void traverse(void (*visit)(List_entry &));
	Error_code insert(int position, const List_entry &x);
	Error_code remove(int position, List_entry &x);
	Error_code retrieve(int position, List_entry &x)const;
	Error_code replace(int position, const List_entry &x);
	~DoubleLinklist();
	DoubleLinklist(const DoubleLinklist<List_entry> &copy);
	void operator = (const DoubleLinklist<List_entry> &copy);
protected:
	int count;
	mutable int current_position;
	mutable Node<List_entry> *current;
	void set_position(int position)const;
};

template <class List_entry>
void DoubleLinklist<List_entry>::set_position(int position)const
{
	if(current_position <= position)
		for(; current_position != position; current_position++)
			current = current->next;
	else
		for(; current_position != position; current_position--)
			current = current->back;
}

template <class List_entry>
DoubleLinklist<List_entry>::DoubleLinklist()
{
	count = 0;
	current = NULL;
	current_position = -1;
}

template <class List_entry>
void DoubleLinklist<List_entry>::clear()
{
	for(; current->back != NULL; current = current->back);
	for(int i = 0; i < count; i++)
	{
		Node<List_entry> *p = current;
		current = current->next;
		delete p;
	}
	count = 0;
	current = NULL;
	current_position = -1;
}

template <class List_entry>
int DoubleLinklist<List_entry>::size()const
{
	return count;
}

template <class List_entry>
bool DoubleLinklist<List_entry>::empty()const
{
	return count == 0;
}

template <class List_entry>
bool DoubleLinklist<List_entry>::full()const
{
	return false;
}

template <class List_entry>
void DoubleLinklist<List_entry>::traverse(void (*visit)(List_entry &))
{
	if(current != NULL)
	{
		for(; current->back != NULL; current = current->back);
		Node<List_entry> *p = current;
		while(p!=NULL)
		{
			(*visit)(p->entry);
			p = p->next;
		}
	}
}

template <class List_entry>
Error_code DoubleLinklist<List_entry>::insert(int position, const List_entry &x)
{
	Node<List_entry> *new_node, *following, *preceding;
	if(position < 0 || position > count) return range_error;
	if(position == 0)	
	{
		if(count == 0) following = NULL;
		else						
		{
			set_position(0);
			following = current;
		}
		preceding = NULL;
	}
	else			
	{
		set_position(position-1);
		preceding = current;
		following = preceding->next;
	}
	new_node = new Node<List_entry>(x,preceding,following);

	if(new_node == NULL) return overflow;
	if(preceding != NULL) preceding->next = new_node;
	if(following != NULL) following->back = new_node;
	current = new_node;
	current_position = position;
	count++;
	return success;
}

template <class List_entry>
Error_code DoubleLinklist<List_entry>::remove(int position, List_entry &x)
{
	Node<List_entry> *old_node, *neighbor;
	if(count == 0) return fail;
	if(position < 0 || position >= count) return range_error;
	set_position(position);
	old_node = current;
	if(neighbor = current->back) neighbor->next = current->next;
	if(neighbor = current->next)
	{
		neighbor->back = current->back;
		current = neighbor;
	}
	else
	{
		current = current->back;
		current_position--;
	}

	x = old_node->entry;
	delete old_node;
	count--;
	return success;
}

template <class List_entry>
Error_code DoubleLinklist<List_entry>::retrieve(int position, List_entry &x)const
{
	if(position < 0 || position >= count) return range_error;

	set_position(position);
	x = current->entry;

	return success;
}

template <class List_entry>
Error_code DoubleLinklist<List_entry>::replace(int position, const List_entry &x)
{
	if(position < 0 || position >= count) return range_error;

	set_position(position);
	current->entry = x;

	return success;
}

template <class List_entry>
DoubleLinklist<List_entry>::~DoubleLinklist()
{
	if(current != NULL)
	{
		for(; current->back != NULL; current = current->back);
		while(current->next!=NULL)
		{
			Node<List_entry> *p = current;
			current = current->next;
			delete p;
		}
	}
}

template <class List_entry>
DoubleLinklist<List_entry>::DoubleLinklist(const DoubleLinklist<List_entry> &copy)
{
	count = 0;
	current = NULL;
	current_position = -1;

	for(; copy.current->back != NULL; copy.current = copy.current->back);
	Node<List_entry> *p = copy.current;
	for(int i = 0; i < copy.count; i++)
	{
		insert(i,p->entry);
		p = p->next;
	}
}

template <class List_entry>
void DoubleLinklist<List_entry>::operator= (const DoubleLinklist<List_entry> &copy)
{
	clear();
	copy.set_position(0);
	Node<List_entry> *p = copy.current;
	for(int i = 0; i < copy.count; i++)
	{
		insert(i,p->entry);
		p = p->next;
	}
}

