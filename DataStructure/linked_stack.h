#include <stdio.h>
#include "utility.h"

typedef int Node_entry;
typedef int Stack_entry;

//=============================//
//=============================//
/* class Node starts from here */
//=============================//
//=============================//

struct Node
{
	Node_entry entry;
	Node *next;

	Node();
	Node(Node_entry item, Node *add_on = NULL);
};

Node::Node()
{
	next = NULL;
}

Node::Node(Node_entry item, Node *add_on)
{
	entry = item;
	next = add_on;
}

//===============================//
//===============================//
/* linked stack starts from here */
//===============================//
//===============================//

class Stack
{
public:
	Stack();
	bool empty()const;
	Error_code push(const Stack_entry &item);
	Error_code pop();
	Error_code top(Stack_entry &item)const;
	~Stack();
	Stack(const Stack &origin);
	void operator = (const Stack &origin);
protected:
	Node *top_node;
};

Stack::Stack()
{
	top_node = NULL;			
}

bool Stack::empty()const
{
	return top_node == NULL;
}

Error_code Stack::push(const Stack_entry &item)
{
	Node *new_top = new Node(item, top_node);
	if(new_top == NULL) return overflow;
	top_node = new_top;
	return success;
}

Error_code Stack::pop()
{
	Node *old_top = top_node;
	if(top_node == NULL) return underflow;
	top_node = old_top->next;
	delete old_top;
	return success;
}

Error_code Stack::top(Stack_entry &item)const
{
	if(top_node == NULL) return underflow;
	item = top_node->entry;
	return success;
}

Stack::~Stack()
{
	while(!empty())
		pop();
}

Stack::Stack(const Stack &origin)
{
	Node *new_copy, *origin_node = origin.top_node;
	if(origin_node == NULL) 
		top_node = NULL;
	else
	{
		top_node = new_copy = new Node(origin_node->entry);
		while(origin_node->next != NULL)
		{
			origin_node = origin_node->next;
			new_copy->next = new Node(origin_node->entry);
			new_copy = new_copy->next;
		}
	}
}

void Stack::operator = (const Stack &origin)
{
	//first clean out old stack entries
	while(!empty())
		pop();

	Node *new_top, *new_copy, *origin_node = origin.top_node;
	if(origin_node == NULL)
		new_top = NULL;
	else
	{
		new_copy = new_top = new Node(origin_node->entry);
		while(origin_node->next != NULL)
		{
			origin_node = origin_node->next;
			new_copy->next = new Node(origin_node->entry);
			new_copy = new_copy->next;
		}
	}

	top_node = new_top;
}

