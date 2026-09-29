class Solution {
public:
    bool checkDigits(int n) {
        int count = 0;
        while (n > 0) {
            n /= 10;
            count++;
        }
        return count % 2 == 0;
    }

    int findNumbers(vector<int>& nums) {
        int ans = 0;
        for (int i = 0; i < nums.size(); i++) {
            if (checkDigits(nums[i])) {
                ans++;
            }
        }
        return ans;
    }
};