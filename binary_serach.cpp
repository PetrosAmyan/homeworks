#include <iostream>
#include <cstdlib>


int binary_search(int *arr, int left, int right, int target)
{
	if (left > right) {
			return -1;
	}

	int middle = (left + right) / 2;
	if (arr[middle] == target) {
			return middle;
	}
	else if (arr[middle] > target) {
			return binary_search(arr, left , middle - 1, target);
	}
	else {
			return binary_search(arr, middle + 1, right, target);
	}

}

int main()
{
	const int size = 8;
	int arr[size] = {3, 5, 12, 23, 27, 32, 64, 83};
	int target;
	std::cout << "input the number for searching: ";
	std::cin >> target;
	
	int result_index = binary_search(arr, 0, size - 1, target);	
	
	std::cout << "the index of target is  " << result_index << "\n";
	return 0;


}
