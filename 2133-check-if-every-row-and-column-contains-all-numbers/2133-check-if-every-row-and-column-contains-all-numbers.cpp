class Solution {
public:
    bool checkValid(vector<vector<int>>& matrix) {
        int n = matrix.size();
        for (int i = 0; i < n; i++) {
            unordered_set<int> rows;
            unordered_set<int> cols;
            for (int j = 0; j < n; j++) {
                if (matrix[i][j] > n || matrix[i][j] < 1 ||
                    rows.contains(matrix[i][j])) {
                    return false;
                }
                rows.insert(matrix[i][j]);

                if (matrix[j][i] > n || matrix[j][i] < 1 ||
                    cols.contains(matrix[j][i])) {
                    return false;
                }
                cols.insert(matrix[j][i]);
            }
        }
        return true;
    }
};