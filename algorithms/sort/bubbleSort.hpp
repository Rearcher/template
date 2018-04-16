#ifndef _BUBBLE_SORT_HPP_
#define _BUBBLE_SORT_HPP_

#include <vector>

/* bubble sort, 3 kinds of implementation */
// best O(n^2)
template <class T>
void bubbleSort(std::vector<T> &nums) {
	int n = nums.size();
	for (int i = 0; i < n; ++i) {
		for (int j = 1; j < n-i; ++j) {
			if (nums[j-1] > nums[j]) 
				std::swap(nums[j-1], nums[j]);
		}
	}
}

// best O(n)
template <class T>
void bubbleSortEx_1(std::vector<T> &nums) {
	int n = nums.size();
	int k = n;
	bool flag = true;
	// use flag to record whether this turn has exchanged
	// two numbers, if not, the array is sorted

	while (flag) {
		flag = false;
		for (int j = 1; j < k; ++j) {
			if (nums[j] < nums[j-1]) {
				std::swap(nums[j], nums[j-1]);
				flag = true;
			}
		}
		k--;
	}
}

// best O(n)
template <class T>
void bubbleSortEx_2(std::vector<T> &nums) {
	int n = nums.size();
	int flag = n;
	// use flag to record the last modefied position i,
	// the nums behind i are sorted

	while (flag > 0) {
		int k = flag;
		flag = 0;
		for (int j = 1; j < k; ++j) {
			if (nums[j-1] > nums[j]) {
				std::swap(nums[j-1], nums[j]);
				flag = j;
			}
		}
	}
}

#endif //_BUBBLE_SORT_HPP_
