#include <string>
#include <algorithm>
#include "same_letters.hpp"

// given two strings, return true if and only if they contain 
// exactly the same letters including repetition.

//"abc" and "cab" return true
//"aaa" and "aaaa" return false
//"aabbc" and "bacab" return true
// "cab" aand "bab" return false
//Rules: Equal amount of letters || Same Characters Used
bool sameLetters( const std::string& firstString, 
                  const std::string& secondString) {
  if (firstString.length() != secondString.length()) {
    return false;
  }
  
  std::string sortedFirst = firstString;
  std::string sortedSecond = secondString;

  std::sort(sortedFirst.begin(), sortedFirst.end());
  std::sort(sortedSecond.begin(), sortedSecond.end());

  return sortedFirst == sortedSecond;
}
