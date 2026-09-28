class Solution {
public:
    int countPrimes(int n) {
        if (n <= 2) {
            return 0;
        }

        vector<char> space(n, 1);
        int noOfPrimes = n - 2;
        for (int i = 2; i * i < n; i++) {
            if (space[i]) {
                for (int j = i * i; j < n; j += i) {
                    if (space[j]) {
                        space[j] = 0;
                        noOfPrimes--;
                    }
                }
            }
        }
        return noOfPrimes;
    }
};