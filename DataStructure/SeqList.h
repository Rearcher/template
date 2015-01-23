#include "utility.h"

#define max_list 100

template <class List_entry>
class SeqList
{
public:
	SeqList();
	int size()const;
	bool full()const;
	bool empty()const;
	void clear();
	void traverse(void (*visit)(List_entry &));
	Error_code retrieve(int position, List_entry &x)const;
	Error_code replace(int position, const List_entry &x);
	Error_code remove(int position, List_entry &x);
	Error_code insert(int position, const List_entry &x);
protected:
	int count;
	List_entry entry[max_list];
};

template <class List_entry>
SeqList<List_entry>::SeqList()
{
	count = 0;
}

template <class List_entry>
int SeqList<List_entry>::size()const
{
	return count;
}

template <class List_entry>
bool SeqList<List_entry>::full()const
{
	if(count >= max_list) return true;
	else return false;
}

template <class List_entry>
bool SeqList<List_entry>::empty()const
{
	return count==0;
}

template <class List_entry>
void SeqList<List_entry>::clear()
{
	count = 0;
}

template <class List_entry>
void SeqList<List_entry>::traverse(void (*visit)(List_entry &))
{
	for(int i = 0; i < count; i++)
		(*visit)(entry[i]);
}

template <class List_entry>
Error_code SeqList<List_entry>::retrieve(int position, List_entry &x)const
{
	if(position >= count || position < 0) return range_error;
	else
		x = entry[position];
	return success;
}

template <class List_entry>
Error_code SeqList<List_entry>::replace(int position, const List_entry &x)
{
	if(position >= count || position < 0) return range_error;
	else
		entry[position] = x;
	return success;
}

template <class List_entry>
Error_code SeqList<List_entry>::remove(int position, List_entry &x)
{
	if(empty()) return underflow;
	if(position >= count || position < 0) return range_error;
	x = entry[position];
	for(int i = position; i < count-1; i++)
			entry[i] = entry[i+1];
	count--;
	return success;
}

template <class List_entry>
Error_code SeqList<List_entry>::insert(int position, const List_entry &x)
{
	if(full()) return overflow;
	if(position > count || position < 0) return range_error;
	for(int i = count-1; i >= position; i--)
			entry[i+1] = entry[i];
	count++;
	entry[position] = x;
	return success;
}
