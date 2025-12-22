long substrCount(int n, string s) {
      vector<pair<char, int>> groups;

    
    for (int i = 0; i < n; ) {
        int j = i;
        while (j < n && s[j] == s[i]) j++;
        groups.push_back({s[i], j - i});
        i = j;
    }

    long count = 0;

    // Step 2: Count type 1 substrings
    for (auto &g : groups) {
        long k = g.second;
        count += k * (k + 1) / 2;
    }

    // Step 3: Count type 2 substrings
    for (int i = 1; i + 1 < groups.size(); i++) {
        if (groups[i].second == 1 &&
            groups[i - 1].first == groups[i + 1].first) {
            count += min(groups[i - 1].second,
                         groups[i + 1].second);
        }
    }

    return count;