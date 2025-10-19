
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
