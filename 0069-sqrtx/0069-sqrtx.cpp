class Solution {
public:
    int mySqrt(int x) {
        if (x <= 1) {
            return x;
        }
        int low = 1;
        int high = x / 2;
        while (high >= low) {
            int mid = low + (high - low) / 2;
            if ((long long)mid * mid == x) {
                return mid;
            } else if ((long long)mid * mid < x) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
        return high;
    }
};