class Solution {
public:
    bool isPalindrome(int x) {
        if (x == 0) {
            return true;
        }
        if (x < 0 || x % 10 == 0) {
            return false;
        }

        int xcopy = x;
        long long rev = 0;
        while (xcopy > 0) {
            int digit = xcopy % 10;
            rev = rev * 10 + digit;
            xcopy /= 10;
        }
        return (x == rev);
    }
};