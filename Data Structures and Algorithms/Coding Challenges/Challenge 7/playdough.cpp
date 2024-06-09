#include <vector>
#include <queue>
#include <algorithm>
#include "playdough.hpp"
#include <iostream>

// Create max-heap priority queue 
// Use it to sort weights
// Take 2 heaviest balls
//    if un-equal, add difference to queue
//    if equal, pair them up
//Future note to always account for empty 

int lastBallWeight(const std::vector<int>& weights) {
  if (weights.empty()) {
    return 0;
  }
  std::priority_queue<int> maxHeap(weights.begin(), weights.end());

  while (maxHeap.size() > 1) {
    int heaviest = maxHeap.top();
    maxHeap.pop();

    int second_Heaviest = maxHeap.top();
    maxHeap.pop();

    if (heaviest != second_Heaviest) {
      int difference = heaviest - second_Heaviest;
      maxHeap.push(difference);
    }
  }
  if (!maxHeap.empty()) {
    return maxHeap.top();
  }
  return 0;
}
