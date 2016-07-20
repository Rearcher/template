#ifndef _MERGE_SORT_
#define _MERGE_SORT_

#include <vector>

template <class T>
void merge(std::vector<T> &nums, int low, int mid, int high) {
	std::vector<T> aux(nums.begin(), nums.end());
	int i = low, j = mid+1;

	for (int k = low; k <= high; ++k) {
		if (i > mid) nums[k] = aux[j++];
		else if (j > high) nums[k] = aux[i++];
		else if (aux[i] < aux[j]) nums[k] = aux[i++];
		else nums[k] = aux[j++];
	}
}

// stable average O(nlogn)
template <class T>
void mergeSort_recursive(std::vector<T> &nums, int low, int high) {
	if (low >= high) return;

	int mid = low + (high-low)/2;
	mergeSort_recursive(nums, low, mid);
	mergeSort_recursive(nums, mid+1, high);

	merge(nums, low, mid, high);
	return;
}

// stable average O(nlogn)
template <class T>
void mergeSort_iterative(std::vector<T> &nums) {
	int n = nums.size();
	for (int size = 1; size <= n; size += size) {
		for (int i = 0; i < n - size; i += size*2) 
			merge(nums, i, i+size-1, std::min(i+size*2-1, n-1));
	}
	return;
}

#endif
