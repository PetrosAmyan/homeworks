int makeAnagram(string a, string b) {
    int arr1[26] = {0};
    int arr2[26] = {0};
    int characterDeleted = 0;
    for(int i = 0; i < a.size(); ++i) {
        arr1[a[i] - 'a']++;
    }
        
     for(int i = 0; i < b.size(); ++i) {
            arr2[b[i] - 'a']++;
     }   
        
     for(int i = 0; i < 26; ++i) {
            if (arr1[i] != arr2[i]) {
                    characterDeleted += abs(arr1[i] - arr2[i]);
            }
     }
      return characterDeleted;     
}
