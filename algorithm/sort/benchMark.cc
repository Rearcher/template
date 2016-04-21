#include "sort.hpp"
#include <iostream>

void print(std::vector<int> &nums) {
	for (auto num : nums)
		std::cout << num << " ";
	std::cout << "\n";
}

int main() {
	std::vector<int> a{4, 3, 2, 1, 0, 4, 5, 7, 6};
	int n = a.size();
	
	bubbleSort(a);
	print(a);

	insertionSort(a);
	print(a);

	mergeSort_iterative(a);
	print(a);

	heapSort(a);
	print(a);

	selectionSort(a);
	print(a);

	shellSort(a);
	print(a);

	quickSort(a, 0, n-1);
	print(a);
}
