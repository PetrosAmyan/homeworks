vector<int> rotLeft(vector<int> a, int d) {
       while ( d > 0) {
        int key = a[0];
        for(int i = 0; i < a.size() - 1; ++i) {
                a[i] = a[i + 1];
        }    
        a[a.size() - 1] = key;
        d--;
       } 
       return a;
}
