#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define random(x) (rand()%x)
void quick_sort(int array[], int left, int right)
{
	int i=left, j=right;
	int temp=array[i];
	if(left < right)
	{
		while(i < j)
		{
			while(i<j && array[j]>=temp)
				j--;
			if(i < j)
				array[i++] = array[j];
			while(i<j && array[i]<=temp)
				i++;
			if(i < j)
				array[j--] = array[i];
		}
		array[i] = temp;
		quick_sort(array, left, i-1);
		quick_sort(array, i+1, right);
	}
}

int main()
{
	int a[100];
	for(int i = 0; i < 100; i++)
		a[i] = random(997);
	quick_sort(a,0,99);
	for(int i = 0; i < 100; i++)
		printf("%d ",a[i]);
	return 0;
}
