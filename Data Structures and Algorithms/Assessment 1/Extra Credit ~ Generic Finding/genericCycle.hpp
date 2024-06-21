#ifndef GENERIC_CYCLE_HPP_
#define GENERIC_CYCLE_HPP_

// Idea / rules
// Tortoise = 1 step into sequence
// hare = 2 step into sequence
// Locate intersection point of cycle - Continual iteration should work going t -> h -> t -> till they meet
// Locating cycle length once cycle is confirmed
// Start the cycle with 1 Node
// move h 1 step away from t
// count the steps that occur


template <typename T, typename F>
int findCycleLength(const T& start, const F& f) {

  T tortoise = f(start);
  T hare = f(tortoise);

  while (tortoise != hare) {
    tortoise = f(tortoise);
    hare = f(f(hare));
  }
  int cycle_length = 1;
  hare = f(tortoise);
  while (tortoise != hare) {
    hare = f(hare);
    cycle_length++;
  }
  return cycle_length;
}

#endif    // GENERIC_CYCLE_HPP_
