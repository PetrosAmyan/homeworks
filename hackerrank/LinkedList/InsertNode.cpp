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