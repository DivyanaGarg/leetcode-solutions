class Solution {
public:
    int calc(int n, int k) {
        int m = n / k;
        return k * m * (m + 1) / 2;
    }

    int sumOfMultiples(int n) {
        return calc(n, 3) + calc(n, 5) + calc(n, 7) - calc(n, 15) -
               calc(n, 21) - calc(n, 35) + calc(n, 105);
    }
};