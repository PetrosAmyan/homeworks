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
