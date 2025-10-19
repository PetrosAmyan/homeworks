
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
