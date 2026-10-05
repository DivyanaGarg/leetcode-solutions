class Solution {
public:
    vector<vector<int>> generateMatrix(int n) {
        vector<vector<int>> spiral(n, vector<int>(n, 0));
        int top = 0;
        int bottom = n - 1;
        int left = 0;
        int right = n - 1;
        int num = 1;
        while (bottom >= top && right >= left) {
            for (int i = left; i <= right; i++) {
                spiral[top][i] = num;
                num++;
            }
            top++;
            for (int i = top; i <= bottom; i++) {
                spiral[i][right] = num;
                num++;
            }
            right--;
            for (int i = right; i >= left; i--) {
                spiral[bottom][i] = num;
                num++;
            }
            bottom--;
            for (int i = bottom; i >= top; i--) {
                spiral[i][left] = num;
                num++;
            }
            left++;
        }
        return spiral;
    }
};