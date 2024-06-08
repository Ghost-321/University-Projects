#include <iostream>

// Write a function that takes two ints as 
// arguments and returns their sum
int add(int a, int b) {
    return a + b;
}

int main() {
    // Prompt the user to enter an integer.
    std::cout << "Enter an integer\n";
    int firstInput {};
    std::cin >> firstInput;
    // Prompt the user to enter another integer.
    std::cout << "Enter another integer\n";
    int secondInput {};
    std::cin >> secondInput;
    // Use your add function to sum the integers.
    // Print out the result!
    std::cout << "The sum is ";
    std::cout << add(firstInput, secondInput) << '\n';
    return 0;
}
