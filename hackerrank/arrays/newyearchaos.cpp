void minimumBribes(vector<int> q) {
     int minimum_bribes = 0;

    for (int i = 0; i < q.size(); ++i) {
        if (q[i] - (i + 1) > 2) {
            std::cout << "Too chaotic\n";
            return;
        }

        for (int j = std::max(0, q[i] - 2); j < i; ++j) {
            if (q[j] > q[i]) {
                ++minimumBribes;
            }
        }
    }

    std::cout << minimumBribes << "\n";   
	}		