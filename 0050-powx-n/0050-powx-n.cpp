class Solution {
public:
    double myPow(double x, int n) {
        double ans = 1;
        long long m = labs(n);

        while (m > 0) {
            if (m % 2 == 1) {
                ans *= x;
                m--;
            } else {
                x = x * x;
                m /= 2;
            }
        }
        if (n < 0) {
            ans = 1.0 / ans;
        }

        return ans;
    }
};