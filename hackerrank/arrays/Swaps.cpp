int minimumSwaps(vector<int> arr) {
     bool flag;
    int swap_count = 0;
    int i = 0;

        while (i < arr.size()) {
            flag = false;    
            if(arr[i] != arr[arr[i] - 1]) {
                    int value = arr[i];
                    arr[i] = arr[value - 1];
                    arr[value - 1] = value;
                    ++swap_count;
                    flag = true;
            }

            if (flag == false) {
                    i++;
            }    
        }
        return swap_count;
}
