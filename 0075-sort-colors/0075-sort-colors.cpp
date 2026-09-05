class Solution {
public:
    void sortColors(vector<int>& nums) {
        int p0 = 0;
        int p1 = 0;
        int p2 = nums.size() - 1;
        while (p2>=p1){
            if (nums[p1] == 1){
                p1++;
            }
            else if (nums[p1] == 0){
                swap(nums[p1], nums[p0]);
                p1++;
                p0++;
            }
            else {
                swap(nums[p1], nums[p2]);
                p2--;
            }
        }
    }
};