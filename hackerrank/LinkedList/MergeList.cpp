
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
