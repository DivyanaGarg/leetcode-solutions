class Solution {
public:
    int countPairs(vector<int>& nums, int target) {
        sort(begin(nums), end(nums));
        int left = 0;
        int right = nums.size() - 1;
        int count = 0;
        while (right > left) {
            if (nums[left] + nums[right] < target) {
                count += right - left;
                left++;
            } else {
                right--;
            }
        }
        return count;
    }
};