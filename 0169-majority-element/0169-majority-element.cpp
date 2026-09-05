class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int count = 0;
        int ele;
        for (int i = 0; i < nums.size(); i++) {
            if (count == 0) {
                ele = nums[i];
                count++;
            } else if (ele == nums[i]) {
                count++;
            } else {
                count--;
            }
        }

        int cnt;
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] == ele) {
                cnt++;
            }
        }
        if (cnt > nums.size()) {
            return ele;
        }
        return -1;
    }
};