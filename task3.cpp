#include <iostream>
#include <string>

int main()
{
	const int size = 8;
	int arr[size] = {4, 10, 4, -2, 10, -2, 5, 20};
	int  result = 0;
	for(int i = 0; i < size; ++i) {
			result ^= arr[i];
	}

	int rigth_bit = result & (-result);
	int num1, num2;
	num1 = num2 = 0;
	for(int i = 0; i < size; ++i) {
			if (rigth_bit & arr[i]) {
					num1 ^= arr[i];
			}
			else {
					num2 ^= arr[i];
			}
	}

	std::cout << num1 << "  " << num2 << "\n";

}