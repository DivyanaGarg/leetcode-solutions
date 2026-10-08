class Solution {
public:
    int searchmatrix(int mid, vector<vector<int>>& matrix, int n) {
        int row = 0;
        int col = n - 1;
        int count = 0;

        while (row <= n - 1 && col >= 0) {
            if (matrix[row][col] <= mid) {
                count += col + 1;
                row++;
            } else {
                col--;
            }
        }
        return count;
    }

    int kthSmallest(vector<vector<int>>& matrix, int k) {
        int n = matrix.size();
        int low = matrix[0][0];
        int high = matrix[n - 1][n - 1];

        while (high > low) {
            int mid = low + (high - low) / 2;
            int val = searchmatrix(mid, matrix, n);
            if (val < k) {
                low = mid + 1;
            } else {
                high = mid;
            }
        }
        return low;
    }
};