#include <iostream>
#include <string>
#include <vector>

class MyLinkedList {
	private:
	struct SingleNode {
			int value;
			SingleNode* next;
	};

	SingleNode* head;

	public:
	MyLinkedList(int data) {
			head = createNode(data);
	}

	~MyLinkedList() {
			SingleNode* current = head;
			while(current != nullptr) {
				SingleNode* tmp = current;
					current = current->next;
					delete tmp;
				
			}
			
	}

	SingleNode* createNode(int data) {
			SingleNode* new_node = new SingleNode;
		 	new_node->value = data;
			new_node->next = nullptr;
			return new_node;
	}

	void push_back(int data) {
			SingleNode* newNode = createNode(data);
			SingleNode* current = head;

			while(current->next != nullptr) {
					current = current->next;
			}

			current->next = newNode;
	}	

	void pop_back() {
			SingleNode* current = head;
			if (current->next == nullptr) {
					delete head;
					head = nullptr;
					return;	
			}
			while(current->next->next != nullptr) {
				current = current->next;
			}

			SingleNode* tmp = current->next;
			delete tmp;
			current->next = nullptr;
			
	}

	void insert(int position, int data) {
			if (position < 0) {
					std::cout << "negative position\n";
					return;
			}

			if (position == 0) {
				SingleNode* newNode = createNode(data);
				newNode->next = head;
				head = newNode;
				return;
			}
			
			SingleNode* current = head;
			for(int i = 0; i < position - 1; ++i) {
					if(current->next == nullptr) {
								push_back(data);
								return;
					}
					current = current->next;
			}

			SingleNode* newNode = createNode(data);
			newNode->next = current->next;
			current->next = newNode;	

	}

	void erase(int position) {
			if (position < 0) {
				std::cout << "negative position\n";
				return;
			}
			SingleNode* current = head;
			if (position == 0) {
					head = head->next;
					delete current;
					return;
			}
			
			for(int i = 0; i < position - 1 && current->next != nullptr; ++i) {
								current = current->next;
				}	
					if (current->next == nullptr) {
							pop_back();
							return;
					}
					SingleNode* tmp = current->next;
					current->next = current->next->next;
					delete tmp;	
					
	}
	void printList() {
			SingleNode* current = head;				
			while (current != nullptr) {
					std::cout << current->value << "  ";
					current = current->next;
			}
			std::cout << "\n";
	}

};
int main()
{
	MyLinkedList list(12);
	list.push_back(3);
	list.push_back(32);
	list.push_back(5);
	list.pop_back();
	list.insert(13, 100);
	list.insert(3, 40);
	list.insert(0, 20);
	list.insert(0, -54);
	list.insert(101, -100);
	list.erase(2);
	list.pop_back();
	list.printList();	

}