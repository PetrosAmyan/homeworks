#include <iostream>

class My_String
{
	private:
	union Storage
	{
		struct HeapStorage {
			int size;
			int cap;
			char* ptr;
		} heap;

		struct StackStorage {
				int8_t size;
				char store[23];
		} stack;

	} storage;
	
	
	public:
	My_String(const char* str)
	{
		std::cout << "constructor was called\n";
		int size = 0;
		for(int i = 0; str[i] != '\0'; ++i) {
					++size;
		}
		if (size > 23) {
			//std::cout << "string was stored in heap\n";
			storage.heap.size = size;
			storage.heap.cap = size * 1.7;
			storage.heap.ptr = new char[storage.heap.cap];
			int i = 0;
			for (i = 0; i < size; ++i) {
					storage.heap.ptr[i] = str[i];
			}
			storage.heap.ptr[i] = '\0';	
			storage.heap.size |= (1 << 31);
			std::cout << "cap is " << storage.heap.cap << "\n";
		}
		else {
			std::cout << "string was stored in stack\n";
			int i = 0;
			for(i = 0; i < size; ++i) {
					storage.stack.store[i] = str[i];
			}		
			storage.stack.store[i] = '\0';
			storage.stack.size = size;	
		}

	}

	~My_String() {
		if (Inheap()) {
			delete[] storage.heap.ptr;
		}
	}

	bool Inheap() {
			return storage.heap.size >> 31; 
	}
	int Size() {
		if (Inheap()) {
				return (storage.heap.size ^ (1 << 31));
		}	
		else {
				return storage.stack.size;
		}
	}

	void append(const char* str) {
		int str_len = 0;
		for(int i = 0; str[i] != '\0'; ++i) {
				str_len++;
		}
		if (Inheap()) {
			std::cout << "more than cap\n";
			//std::cout << storage.heap.size + str_len << "\n"; 
			int real_size = (storage.heap.size) ^ (1 << 31);
			if (real_size + str_len >= storage.heap.cap) {
				char* tmp = storage.heap.ptr;
				storage.heap.cap = 1.7 * (real_size + str_len);
				storage.heap.ptr = new char[storage.heap.cap];
				for(int i = 0; i < (real_size + str_len); ++i) {
					storage.heap.ptr[i] = tmp[i];
				}
				delete[] tmp;
				std::cout << "begin to copy in new place\n";
			}
						
						int i;
						for(i = real_size; i < (real_size + str_len); ++i) {
									storage.heap.ptr[i] = str[i];
						}
						storage.heap.ptr[i] = '\0';
						storage.heap.size += str_len;
						std::cout << "the new size is " << Size() << "\n";
						std::cout << "the new cap is " << storage.heap.cap << "\n";
		}			
		else {
								
			
		}		
}	
	
		
 };

int main()
{
	My_String obj("hello world from me and you ");
	std::cout << "the length of string is " << obj.Size() << "\n";	
	obj.append("the world most powerfull army has USA IRAN CHINA RUSSIAN");	

}