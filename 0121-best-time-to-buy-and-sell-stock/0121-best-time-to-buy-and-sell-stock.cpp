class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int minm = prices[0];
        int profit = 0;
        for (int i = 0; i < prices.size(); i++) {
            minm = min(minm, prices[i]);
            profit = max(profit, prices[i] - minm);
        }
        return profit;
    }
};