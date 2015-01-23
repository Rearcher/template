#include <stdio.h>
#include "utility.h"

typedef int Node_entry;
typedef int Queue_entry;

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

//==============================//
//==============================//
/* class Queue starts from here */
//==============================//
//==============================//

class Queue
{
public:
	Queue();
	bool empty()const;
	Error_code append(const Queue_entry &item);
	Error_code serve();
	Error_code retrieve(Queue_entry &item)const;
	~Queue();
	Queue(const Queue &origin);
	void operator = (const Queue &origin);
protected:
	Node *front, *rear;
};

Queue::Queue()
{
	front = rear = NULL;
}

bool Queue::empty()const
{
	return rear==NULL;
}

Error_code Queue::append(const Queue_entry &item)
{
	Node *new_rear = new Node(item);
	if(new_rear == NULL) return overflow;
	if(rear == NULL) front = rear = new_rear;
	else
	{
		rear->next = new_rear;
		rear = new_rear;
	}
	return success;
}

Error_code Queue::serve()
{
	if(front == NULL) return underflow;
	Node *old_front = front;
	front = old_front->next;
	if(front == NULL) rear = NULL;
	delete old_front;
	return success;
}

Error_code Queue::retrieve(Queue_entry &item)const
{
	if(front == NULL) return underflow;
	item = front->entry;
	return success;
}

Queue::Queue(const Queue &origin)
{
	Node *origin_node = origin.front;
	if(origin_node == NULL)
		front = rear = NULL;
	else
	{
		Node *new_copy;
		front = new_copy = new Node(origin_node->entry);
		while(origin_node->next != NULL)
		{
			origin_node = origin_node->next;
			new_copy->next = new Node(origin_node->entry);
			new_copy = new_copy->next;
		}
		rear = new_copy;
	}
}

void Queue::operator = (const Queue &origin)
{
	while(!empty())
		serve();
	
	Node *new_front, *new_rear;
	Node *origin_node = origin.front;
	if(origin.empty())
		new_front = new_rear = NULL;
	else
	{
		Node *new_copy;
		new_copy = new_front = new Node(origin_node->entry);
		while(origin_node->next != NULL)
		{
			origin_node = origin_node->next;
			new_copy->next = new Node(origin_node->entry);
			new_copy = new_copy->next;
		}
		new_rear = new_copy;
	}
	front = new_front;
	rear = new_rear;
}

Queue::~Queue()
{
	while(!empty())
		serve();
}

//=======================================//
//=======================================//
/* class Extended_queue starts from here */
//=======================================//
//=======================================//
class Extended_queue : public Queue
{
public:
	bool full()const;
	int size()const;
	void clear();
	Error_code serve_and_retrieve(Queue_entry &x);
};

bool Extended_queue::full()const
{
	return false;
}

int Extended_queue::size()const
{
	Node *head = front;
	int count = 0;
	while(head != NULL)
	{
		head = head->next;
		count++;
	}
	return count;
}

void Extended_queue::clear()
{
	while(!empty())
		serve();
}

Error_code Extended_queue::serve_and_retrieve(Queue_entry &x)
{
	if(front == NULL) return underflow;
	Node *old_front = front;
	front = old_front->next;
	x = old_front->entry;
	if(front == NULL) rear = NULL;
	delete old_front;
	return success;
}
