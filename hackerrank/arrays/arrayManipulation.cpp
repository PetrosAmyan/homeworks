long arrayManipulation(int n, vector<vector<int>> queries) {
   
      vector<long> arr(n + 1, 0);
      int a = 0;
      int b = 0;
      for(int i = 0; i < queries.size(); ++i) {
              a = queries[i][0];
              b = queries[i][1];
              arr[a-1] += queries[i][2];
              if (b < n) {
                    arr[b] -= queries[i][2];
              }        
        }
       
       long current = 0;
       long max_value = 0;
       for(int i = 0; i < arr.size(); ++i) {
              current += arr[i];
              if (max_value < current) {
                    max_value = current;
              }  
       }
       
       return max_value;
       
       
}