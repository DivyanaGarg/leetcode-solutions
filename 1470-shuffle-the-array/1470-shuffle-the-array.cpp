class Solution {
public:
    vector<int> shuffle(vector<int>& nums, int n) {
        vector<int> ans(2 * n, 0);
        int x = 0;
        for (int i = 0; i < 2 * n; i += 2) {
            ans[i] = nums[x];
            ans[i + 1] = nums[n + x];
            x++;
        }
        return ans;
    }
};