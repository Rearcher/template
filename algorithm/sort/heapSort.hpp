#ifndef _HEAP_SORT_
#define _HEAP_SORT_

#include <vector>

template <class T>
void maxHeapify(std::vector<T> &nums, int start, int end) {
	int father = start;
	int son = father*2+1;

	while (son < end) {
		// to find the max son
		if (son+1 < end && nums[son+1] > nums[son])
			son++;
		// compare the max son with father
		if (nums[father] >= nums[son]) {
			return;
		} else {
			std::swap(nums[father], nums[son]);
			father = son;
			son = father*2+1;
		}
	}
}

template <class T>
void heapSort(std::vector<T> &nums) {
	int n = nums.size();
	
	// init, start from the last father node
	for (int i = n/2; i >= 0; --i)
		maxHeapify(nums, i, n);
	
	// nums[0] means the max number in current heap,
	// exchange nums[0] to the position behind the current heap,
	// heap size decrease, and adjust the heap
	for (int i = n-1; i > 0; --i) {
		std::swap(nums[0], nums[i]);
		maxHeapify(nums, 0, i);
	}
}

#endif
