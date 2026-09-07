class Solution {
public:
    vector<int> sortedSquares(vector<int>& nums) {
        int left = 0;
        int right = nums.size() - 1;
        vector<int> ans(nums.size(), 0);
        int p = nums.size() - 1;
        while (right >= left) {
            if (abs(nums[right]) >= abs(nums[left])) {
                ans[p] = nums[right] * nums[right];
                right--;
            } else {
                ans[p] = nums[left] * nums[left];
                left++;
            }
            p--;
        }
        return ans;
    }
};