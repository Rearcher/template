#include "utility.h"

const int maxqueue = 10;
typedef int Queue_entry;

class Queue
{
public:
	Queue();
	bool empty()const;
	Error_code append(const Queue_entry &x);
	Error_code serve();
	Error_code retrieve(Queue_entry &x)const;
protected:
	int count;
	int front, rear;
	Queue_entry entry[maxqueue];
};

Queue::Queue()
{
	count = 0;
	front = 0;
	rear = maxqueue-1;
}

bool Queue::empty()const
{
	return count==0;
}

Error_code Queue::append(const Queue_entry &x)
{
	if(count >= maxqueue) return overflow;
	count++;
	rear = ((rear+1)==maxqueue)?0:(rear+1);
	entry[rear] = x;
	return success;
}

Error_code Queue::serve()
{
	if(count <= 0) return underflow;
	count--;
	front = ((front+1)==maxqueue)?0:(front+1);
	return success;
}

Error_code Queue::retrieve(Queue_entry &x)const
{
	if(count <= 0) return underflow;
	x = entry[front];
	return success;
}
//=================================//
//=================================//
//=================================//
/* Extended_queue starts from here */
//=================================//
//=================================//
//=================================//
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
	return count==maxqueue;
}

int Extended_queue::size()const
{
	return count;
}

void Extended_queue::clear()
{
	while(!empty())
	{
		serve();
	}
}

Error_code Extended_queue::serve_and_retrieve(Queue_entry &x)
{
	if(count <= 0) return underflow;
	count--;
	x = entry[front];
	front = ((front+1)==maxqueue)?0:maxqueue;
	return success;
}
