class Solution {
public:
    vector<int> arrayRankTransform(vector<int>& arr) {
        vector<int> sorted = arr;
        sort(sorted.begin(), sorted.end());
        unordered_map<int, int> mpp;
        int r = 1;
        for (int num : sorted) {
            if (!mpp.contains(num)) {
                mpp[num] = r++;
            }
        }
        for (int i = 0; i < arr.size(); i++) {
            arr[i] = mpp[arr[i]];
        }
        return arr;
    }
};