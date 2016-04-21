#ifndef _QUICK_SORT_
#define _QUICK_SORT_

#include <vector>

template <class T>
int partition(std::vector<T> &nums, int low, int high) {
	int i = low, j = high+1;
	while (i < j) {
		while (++i < high && nums[i] <= nums[low]);
		while (--j > low && nums[j] >= nums[low]);
		if (i >= j) break;
		std::swap(nums[i], nums[j]);
	}
	std::swap(nums[low], nums[j]);
	return j;
}

// best O(nlogn)
// worst O(n^2)
template <class T>
void quickSort(std::vector<T> &nums, int low, int high) {
	if (low >= high) return;

	int pivot = partition(nums, low, high);
	quickSort(nums, low, pivot-1);
	quickSort(nums, pivot+1, high);
}

#endif //_QUICK_SORT_
