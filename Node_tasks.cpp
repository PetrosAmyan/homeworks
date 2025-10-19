
 // For your reference:

 //1
struct  SinglyLinkedListNode {
     int data;
     SinglyLinkedListNode* next;
  };


 bool findNode(const std::vector<SinglyLinkedListNode*>& arr, SinglyLinkedListNode* h) {
    for(int i = 0; i < arr.size(); ++i) {
        if (h == arr[i]) {
                return true;
        }
    }

    return false;
    

 }
int findMergeNode(SinglyLinkedListNode* head1, SinglyLinkedListNode* head2) {

    if (head1 == head2) {
            return head1->data;
    }
    
    std::vector<SinglyLinkedListNode*> arr;
    while(head1 != nullptr) {
            arr.push_back(head1);
            head1 = head1->next;
    }
    
    while(head2 != nullptr) {
         if (findNode(arr, head2)) {
            return head2->data;      
         }
         head2 = head2->next;   
    }
    return  -1;
    
}


// 2
DoublyLinkedListNode* reverse(DoublyLinkedListNode* llist) {
    if (llist == nullptr) {
            return nullptr;
    }
    
   DoublyLinkedListNode* current = llist;
   
   while(llist != nullptr) {
        current = current->next;
        llist->next = llist->prev;
        llist->prev = current;
        
        if (current == nullptr) {
            return llist;
        }
            
        llist = llist->prev;
   }
   return llist;
 
}

// 3
bool has_cycle(Node* head) {
    // Complete this function
   // Do not write the main method
   
    if (head == nullptr || head->next == nullptr) {
            return false;
    }
   
    Node* fast = head->next;
    while(true) {
        if (head == fast) {
            return true;
        }
        if (fast == nullptr || fast->next == nullptr) {
            return false;
        }
        head = head->next;
        fast = fast->next->next;    
    }
}

// 4
DoublyLinkedListNode* sortedInsert(DoublyLinkedListNode* llist, int data) {
     DoublyLinkedListNode* new_node = new DoublyLinkedListNode(data);


    if (llist == nullptr) {
        return new_node;
    }

    DoublyLinkedListNode* current = llist;

    if (data < current->data) {
        new_node->next = current;
        current->prev = new_node;
        return new_node;
    }

    while (current->next != nullptr && current->next->data < data) {
        current = current->next;
    }


    if (current->next != nullptr) {
        new_node->next = current->next;
        new_node->prev = current;
        current->next->prev = new_node;  
        current->next = new_node;
    }
    else {
        current->next = new_node;
        new_node->prev = current;
    }

    return llist;
}

// 5
SinglyLinkedListNode* insertNodeAtPosition(SinglyLinkedListNode* llist, int data, int position) {
        
        if (position == 0) {
            return llist;
        }
        
        SinglyLinkedListNode* new_node = new SinglyLinkedListNode(data);  
        SinglyLinkedListNode* current = llist;
        
        for(int i = 0; i < position - 1; ++i) {
                current = current->next;
        }    
        
        new_node->next = current->next;
        current->next = new_node;
        
        return llist;
}