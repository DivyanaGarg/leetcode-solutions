class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        vector<int> freq(256, 0);
        int l = 0;
        int longest = 0;
        for (int i = 0; i < s.size(); i++) {
            freq[s[i]]++;
            while (freq[s[i]] > 1) {
                freq[s[l]]--;
                l++;
            }
            longest = max(longest, i - l + 1);
        }
        return longest;
    }
};