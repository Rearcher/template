#ifndef _SHELL_SORT_
#define _SHELL_SORT_

#include <vector>

// derived from insertion sort
// best O(n)
// average time depends on gap
template <class T>
void shellSort(std::vector<T> &nums) {
	int n = nums.size();
	for (int gap = n>>1; gap > 0; gap >>= 1) {
		for (int j = gap; j < n; j++) {
			//if (a[j] < a[j-gap]) {
			T temp = nums[j];
			int k = j-gap;
			while (k >= 0 && nums[k] > temp) {
				nums[k+gap] = nums[k];
				k -= gap;
			}
			nums[k+gap] = temp;
			//}
		}
	}
}

#endif //_SHELL_SORT_
