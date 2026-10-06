class Solution {
public:
    vector<int> findPeakGrid(vector<vector<int>>& mat) {
        int row = 0;
        int col = mat[0].size() - 1;

        int n = mat.size();
        int m = mat[0].size();

        while (row < n && col >= 0) {
            if (row + 1 < n && mat[row][col] < mat[row + 1][col]) {
                row++;
            } else if (row - 1 >= 0 && mat[row][col] < mat[row - 1][col]) {
                row--;
            } else if (col + 1 < m && mat[row][col] < mat[row][col + 1]) {
                col++;
            } else if (col - 1 >= 0 && mat[row][col] < mat[row][col - 1]) {
                col--;
            } else {
                return {row, col};
            }
        }
        return {-1, -1};
    }
};