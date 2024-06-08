#include <cstdint>

int64_t recursiveFibonacci(int n) {
	if (n == 0 || n == 1) {
		return n;
	}
	return recursiveFibonacci(n-1) + recursiveFibonacci(n-2);
}

int64_t iterativeFibonacci(int n) {
	if (n == 0) return 0;
	int64_t previous {0}; 
  int64_t current {1};	
	for (int i {1}; i < n; ++i) {
		current = current + previous;
    // put the old value of current into previous
    previous = current - previous;
	}
	return current;
}
