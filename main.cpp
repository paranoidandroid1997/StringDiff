#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>

// Function that returns the Levenshtein distance of the first string from the second
int lev(std::string s1, std::string s2) {
    // If s1 is empty, we have to add as many characters as there are in s2 to s1 for them to match
    if (s1.size() == 0) return s2.size();
        // If s2 is empty, we have to delete as many characters as there are in s1 to get s2 for them to match
    else if (s2.size() == 0) return s1.size();
        // If the two strings have the same final character, we can somewhat ignore them and move on.
    else if (s1.back() == s2.back()) {
        return lev(s1.substr(0, s1.size() - 1),
                   s2.substr(0, s2.size() - 1));
    } else {
        return 1 + std::min(
                {
                        lev(s1.substr(0, s1.size() - 1), s2), // Removing a character
                        lev(s1, s2.substr(0, s2.size() - 1)), // Adding a character
                        lev(s1.substr(0, s1.size() - 1), s2.substr(0, s2.size() - 1)) // Replacing a character
                }
        );
    }

    return -1;
}

int main() {
    // Initialize a vector to hold all test cases
    std::vector<std::pair<std::string, std::string>> testCases;

    // Add some test cases
    testCases.emplace_back("cats", "dogs");
    testCases.emplace_back("apple", "dapple");
    testCases.emplace_back("nirvana", "nirvana");
    testCases.emplace_back("", "hello");
    testCases.emplace_back("dogsarecoolyestheyare", "dogsarelityestheyare");
    testCases.emplace_back("goodbye", "hello");


    for (auto test: testCases) {
        std::cout << lev(test.first, test.second) << std::endl;
    }


    return 0;
}
