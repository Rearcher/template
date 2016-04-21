#ifndef _INSERTION_SORT_
#define _INSERTION_SORT_

#include <vector>

// best O(n), average O(n^2), stable
template <class T>
void insertionSort(std::vector<T> &nums) {
	int n = nums.size();
	for (int i = 1; i < n; ++i) {
	//	if (nums[i] < nums[i-1]) {
		T temp = nums[i];
		int j = i-1;
		for (; j >= 0 && nums[j] > temp; --j)
			nums[j+1] = nums[j];
		nums[j+1] = temp;
	//	}
	}
}

#endif //_INSERTION_SORT_
