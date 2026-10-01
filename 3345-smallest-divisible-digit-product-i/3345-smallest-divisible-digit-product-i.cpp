class Solution {
public:
    int productOfDigits(int n) {
        int prod = 1;
        while (n > 0) {
            prod *= (n % 10);
            n /= 10;
        }
        return prod;
    }
    int smallestNumber(int n, int t) {
        while (true) {
            if (productOfDigits(n) % t == 0) {
                return n;
            }
            n++;
        }
    }
};