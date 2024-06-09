#include <vector>
#include "stock.hpp"

int maxProfit(const std::vector<int>& prices) {
  if (prices.empty()) {
    return 0;
  }
  auto it = prices.begin();
  int minimumSoFar = *it;
  int bestProfit = 0;
  for (; it != prices.end(); ++it) {
    int profit = *it - minimumSoFar;
    if (profit > bestProfit) {
      bestProfit = profit;  
    }
    if (*it < minimumSoFar) {
      minimumSoFar = *it;
    }
  }
  return bestProfit;
}
