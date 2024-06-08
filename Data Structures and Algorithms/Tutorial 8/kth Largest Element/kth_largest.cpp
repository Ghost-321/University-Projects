#include <vector>
#include <queue>
#include <functional>
#include "kth_largest.hpp"

int kthLargest(const std::vector<int>& vec, int k) {
  std::priority_queue<int, std::vector<int>,
                      std::greater<int> > pq {};
  for (int x : vec) {
    pq.push(x);
    if (static_cast<int>(pq.size()) > k) {
      pq.pop();
    }
  }
  return pq.top();
}
