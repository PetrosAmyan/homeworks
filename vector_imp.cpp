#include <iostream>

class MyVector {
	private:
	int cap;
	int size;
	int *arr;
	public:
	
	MyVector(int _cap) {
			cap = _cap;
			size = 0;
			arr = new int[cap];	
	}

	~MyVector() {
			delete[] arr;
	}

	int& operator [](int index) {
			if (index < 0 || index >= size) {
					throw std::out_of_range("out of range \n");
			}
			else {
					return arr[index];
			}

	}
	

	int Size() {
			return size; 
	}

	void push_back(int element) {
				if (size == cap) {
						cap *= 1.7;
						int *new_arr = new int[cap];
	
				for(int i = 0; i < size; ++i) {
						new_arr[i] = arr[i];
				}		

					delete[] arr;
					arr = new_arr;
				}

				arr[size] = element;
				size++;		
				
	}

	void pop_back() {
			if (size == 0) {
					std::cout << "vector is empty: \n";
					return;
			}

			arr[size - 1] = 0;
			size--;
	}

};

int main()
{
	MyVector vec(1);	

	vec.push_back(2);
	vec.push_back(12);
	vec.push_back(20);
	vec[2] = 100;
	std::cout << vec[2] << "\n";
	std::cout << vec.Size();
	std::cout << vec[0];
}