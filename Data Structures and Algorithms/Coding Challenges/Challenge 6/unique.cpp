#include <algorithm>
#include <string>
#include <unordered_map>
#include "unique.hpp"
// Rules:
// Indexes (3 rules)
// "3483499rdl[]l!d[23r82aq!" = 11 (Index of ])
// abA = 0 (Index of a)
// acabcd = 3 (index of b)

// Size of String (2 rules)
// "lk?e[j!lw[kds]jkds]!lew?" = 24 (size of string)
// z&##z& = 6 (size of string)

std::size_t firstUniqueChar(const std::string& inputString) {
  
  std::unordered_map<char, int> frequencyMap;

  for (char ch : inputString) {
    frequencyMap[ch]++;
  }

  for (std::size_t i = 0; i < inputString.length(); i++) {
    if (frequencyMap[inputString[i]] == 1) {
      return i;
    }
  } 

  return inputString.length();
}
