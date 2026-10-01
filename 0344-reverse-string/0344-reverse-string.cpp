class Solution {
public:
    void reverseString(vector<char>& s) {
        int p1 = 0;
        int p2 = s.size() - 1;
        while (p2 > p1) {
            swap(s[p1], s[p2]);
            p1++;
            p2--;
        }
    }
};