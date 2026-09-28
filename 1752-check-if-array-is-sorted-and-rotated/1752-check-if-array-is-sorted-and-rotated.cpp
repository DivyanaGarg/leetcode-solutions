class Solution {
public:
    bool check(vector<int>& nums) {
        int count = 0;
        int n = nums.size();
        for (int i = 0; i < n - 1; i++) {
            if (nums[i] > nums[i + 1]) {
                count++;
            }
        }
        if (count > 1 || (count == 1 && nums[n - 1] > nums[0])) {
            return false;
        }
        return true;
    }
};