class Solution {
public:
    string reverseWords(string s) {
        string ans = "";
        int i = s.size() - 1;
        while (i >= 0) {
            if (s[i] == ' ') {
                i--;
                continue;
            }
            string word = "";
            while (i >= 0 && s[i] != ' ') {
                word += s[i];
                i--;
            }
            reverse(word.begin(), word.end());
            if (!ans.empty()) {
                ans += ' ';
            }
            ans += word;
        }
        return ans;
    }
};