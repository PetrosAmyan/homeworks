#include <iostream>
#include <string>

int main()
{

	const int size = 7;
	int arr[size] = {10, 12, 12, 14, 10, -2, 14};
	int uniq_number = 0;
	for(int i = 0; i < size; ++i) {
			uniq_number ^= arr[i];
	}

	std::cout << uniq_number << "\n";

}