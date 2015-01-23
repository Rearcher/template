#include <stdio.h>

const int MAXN = 10;
int entry[MAXN]={1,3,6,7,2,3,4,5,9,0};

void insert_heap(const int &current, int low, int high)
{
	int large;
	large = low*2+1;
	while(large <= high)
	{
		if(large < high && entry[large] < entry[large+1])
			large++;
		if(current >= entry[large])
			break;
		else
		{
			entry[low] = entry[large];
			low = large;
			large = 2*low+1;
		}
	}
	entry[low] = current;
}

void build_heap()
{
	int low;
	for(low = MAXN/2-1; low >= 0; low--)
	{
		int current = entry[low];
		insert_heap(current, low, MAXN-1);
	}
}

void heap_sort()
{
	int current;
	int last_unsorted;
	build_heap();
	for(last_unsorted = MAXN-1; last_unsorted > 0; last_unsorted--)
	{
		current = entry[last_unsorted];
		entry[last_unsorted] = entry[0];
		insert_heap(current, 0, last_unsorted-1);
	}
}

int main()
{
	heap_sort();
	for(int i = 0; i < MAXN; i++)
		printf("%d\n",entry[i]);
}
