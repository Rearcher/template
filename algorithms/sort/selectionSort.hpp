#ifndef _SELECTION_SORT_
#define _SELECTION_SORT_

#include <vector>

// 何为排序算法的稳定性？
// 即对于相同的元素，排序算法不能改变其相对的位置
// 而选择排序会导致相同元素相对位置发生改变
// O(n^2), unstable
template <class T>
void selectionSort(std::vector<T> &nums) {
	int n = nums.size();
	for (int i = 0; i < n-1; ++i) {
		int index = i;
		for (int j = i+1; j < n; ++j) {
			if (nums[j] < nums[index])
				index = j;
		}
		std::swap(nums[index], nums[i]);
	}
}

#endif //_SELECTION_SORT_
