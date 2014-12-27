#include <stdio.h>
#include <stdlib.h>
#define random(x) (rand()%x)

void Merge_array(int array[], int first, int mid, int last, int temp[])
{
	int i=first, j=mid+1;
	int m=mid, n=last;
	int k=0;

	while(i<=m && j<= n)
	{
		if(array[i] < array[j])
			temp[k++] = array[i++];
		else
			temp[k++] = array[j++];
	}
	while(i <= m)
		temp[k++] = array[i++];
	while(j <= n)
		temp[k++] = array[j++];

	for(i = 0; i < k; i++)
		array[first+i] = temp[i];
}

void Merge_sort(int array[], int first, int last, int temp[])
{
	if(first < last)
	{
		int mid = (first+last)/2;
		Merge_sort(array, first, mid, temp);
		Merge_sort(array, mid+1, last, temp);
		Merge_array(array, first, mid, last, temp);
	}
}

int main()
{
	int a[100],b[100];
	for(int i = 0; i < 100; i++)
		a[i] = random(997);
	Merge_sort(a, 0, 99, b);
	for(int i = 0; i < 100; i++)
		printf("%d ", a[i]);
	return 0;
}
