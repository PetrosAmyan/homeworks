#include <iostream>
#include <ctime>
#include <cstdlib>

void Merge(int *arr, int p, int q, int r)
{
	int n1 = q - p + 1 ;
	int n2 = r - q;
	int Left[n1];
	int Right[n2];

	for(int i = 0; i < n1; ++i) {
			Left[i] = arr[p + i];
	}

	for(int j = 0; j < n2; ++j) {
			Right[j] = arr[j + q + 1];
	}	
	

 int i = 0, j = 0, k = p;
    while (i < n1 && j < n2) {
        if (Left[i] <= Right[j]) {
            arr[k] = Left[i];
            i++;
        } else {
            arr[k] = Right[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = Left[i];
        i++; 
				k++;
    }
    while (j < n2) {
        arr[k] = Right[j];
        j++;
				 k++;
    }


}

void Merge_sort(int *arr, int p, int r)
{
	if (p < r) {
				int q = (p + r) / 2;
				Merge_sort(arr, p, q);
				Merge_sort(arr, q + 1, r);
				Merge(arr, p, q, r);
	}

}

void generate_array(int *arr, int size)
{
	
	std::srand(std::time(0));
	for(int i = 0; i < size; ++i) {
			arr[i] = std::rand() % 100;
	}

}
int main()
{
	const int size = 4;
	int arr[size];
	generate_array(arr, size);

	Merge_sort(arr, 0, size - 1);

	for(int i = 0; i < size; ++i) {
			std::cout << arr[i] << " " ;
	}

	std::cout << "\n";

}