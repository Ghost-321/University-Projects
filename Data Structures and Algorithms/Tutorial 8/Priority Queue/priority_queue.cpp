#include <iostream>
#include <vector>
#include <queue>
#include <compare>

class MyInteger {
 private:
  int val = 0;
 public:
  explicit MyInteger(int initialiser = 0)
      : val {initialiser} {}
  // spaceship operator!
  // define 6 comparisons in one!
  auto operator<=>(const MyInteger& other) const = default;
  friend std::ostream& operator<<(std::ostream& out,
                                  const MyInteger& myInt) {
    out << myInt.val;
    return out;
  }
};

int main() {
  // Does this define a min priority queue
  // or a max priority queue?
  // push some elements into it with "push" and then use
  // "top" to find out
  std::priority_queue<int> q1;
  q1.push(5);
  q1.push(3);
  std::cout << "top of q1 is " << q1.top() << '\n';

  // A priority queue can accept 3 template arguments.
  // 1) The first is the type of objects in the queue.
  // Here we will again construct a priority queue of ints.
  // 2) The second argument specifies what kind of
  // underlying container to use for the priority queue.
  // We will use a std::vector<int>.
  // 3) The third argument is a comparison function.
  // The default here is less than.  By instead using
  // greater than we can switch from a max priority queue
  // to a min priority queue.
  // Test that this is indeed a min priority queue now.
  std::priority_queue<int, std::vector<int>,
                      std::greater<int> > q2;
  q2.push(5);
  q2.push(3);
  std::cout << "top of q2 is " << q2.top() << '\n';

  // We can also have a queue of a user defined type
  std::priority_queue<MyInteger> q3;
  q3.push(MyInteger {3});
  q3.push(MyInteger {5});
  std::cout << q3.top() << '\n';

  // This uses the > comparison of the MyInteger class
  std::priority_queue<MyInteger, std::vector<MyInteger>,
                      std::greater<MyInteger> > q4;
  q4.push(MyInteger {3});
  q4.push(MyInteger {5});
  std::cout << q4.top() << '\n';
  return 0;
}
