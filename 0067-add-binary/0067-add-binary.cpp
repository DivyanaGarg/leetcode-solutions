class Solution {
public:
    string addBinary(string a, string b) {
        string ans = "";
        int n = a.length() - 1;
        int m = b.length() - 1;
        int carry = 0;

        while (n >= 0 || m >= 0 || carry == 1) {
            int sum = carry;
            if (n >= 0) {
                sum += a[n] - '0';
                n--;
            }
            if (m >= 0) {
                sum += b[m] - '0';
                m--;
            }
            ans += (sum % 2) + '0';
            carry = sum / 2;
        }
        
        reverse(ans.begin(), ans.end());
        return ans;
    }
};