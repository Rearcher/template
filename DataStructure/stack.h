#include "utility.h"

typedef int Stack_entry;
const int maxstack = 10;

class Stack{
public:
	Stack();
	bool empty()const;
	Error_code pop();
	Error_code push(const Stack_entry &item);
	Error_code top(Stack_entry &item)const;
private:
	int count;
	Stack_entry entry[maxstack];
};

Stack::Stack()
{
	count = 0;
}

bool Stack::empty()const
{
	if(count == 0) return true;
	return false;
}

Error_code Stack::pop()
{
	if(count <= 0) return underflow;
	else count--;
	return success;
}

Error_code Stack::push(const Stack_entry &item)
{
	if(count >= maxstack) return overflow;
	else entry[count++] = item;
	return success;
}

Error_code Stack::top(Stack_entry &item)const
{
	if(count <= 0) return underflow;
	else item = entry[count-1];
	return success;
}
