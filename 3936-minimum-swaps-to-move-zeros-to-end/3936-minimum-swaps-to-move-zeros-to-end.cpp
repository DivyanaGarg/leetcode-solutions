class Solution {
public:
    int minimumSwaps(vector<int>& nums) {
        int p1 = 0;
        int p2 = nums.size() - 1;
        int count = 0;
        while (p2 > p1) {
            while (nums[p2] == 0 && p2>p1) {
                p2--;
            }
            while (nums[p1] != 0 && p2>p1) {
                p1++;
            }
            if (nums[p1] == 0 && p2>p1) {
                swap(nums[p1], nums[p2]);
                p2--;
                p1++;
                count++;
            }
        }
        return count;
    }
};