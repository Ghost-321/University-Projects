#ifndef MERGESORT_HPP_
#define MERGESORT_HPP_

#include <vector>
#include <algorithm>

template <typename Iter>
void merge(Iter low, Iter mid, Iter high) {
  // we can get the type of element the iterator points to like this
  using T = std::iter_value_t<Iter>;
  // now T stands for this type

  // We suggest that you create a new vector
  // std::vector<T> mergedVec(high - low);
  // to hold the results of the merge as you work
  std::vector<T> mergedVec(high - low);

  // At the end of the function you can copy
  // mergedVec into the original vector with
  // std::copy(mergedVec.begin(), mergedVec.end(), low);
  Iter lowerIt = low;
  Iter upperIt = mid;
  for (Iter it = mergedVec.begin(); it != mergedVec.end(); ++it) {
    if (upperIt == high) {
      *it = *lowerIt;
      ++lowerIt;
    } else if (lowerIt == mid) {
      *it = *upperIt;
      ++upperIt;
    } else if (*lowerIt <= *upperIt) {
      *it = *lowerIt;
      ++lowerIt;
    } else {
      *it = *upperIt;
      ++upperIt;
    }
  }
  std::copy(mergedVec.begin(), mergedVec.end(), low);
}

// mergesort takes as inputs two iterators into a
// vector low and high, and sorts the entries
// of the vector in the half-open interval [low, high).
template <typename Iter>
void mergesort(Iter low, Iter high) {
  // Base case: if the size of portion to be sorted
  // high - low < 2 then return
  if (high - low < 2) {
    return;
  }

  // Compute the midpoint "mid" of the interval to be sorted
  // and call merge_sort on the first half mergesort(low, mid)
  // and second half merge_sort(mid, high)
  // Finally, merge the two halves.
  Iter mid = low + (high - low)/2;
  mergesort(low, mid);
  mergesort(mid, high);
  merge(low, mid, high);
}

#endif      // MERGESORT_HPP_
