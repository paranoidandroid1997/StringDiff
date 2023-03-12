#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>

int lev(std::string, std::string);
int lev_impl(std::string, int, std::string, int);
int levSlow(std::string, std::string);

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
        std::cout << levSlow(test.first, test.second) << " ";
        std::cout << lev(test.first, test.second) << std::endl;
    }


    return 0;
}

// Function that returns the Levenshtein distance of the first string from the second
int levSlow(std::string s1, std::string s2) {
    // If s1 is empty, we have to add as many characters as there are in s2 to s1 for them to match
    if (s1.size() == 0) return s2.size();
        // If s2 is empty, we have to delete as many characters as there are in s1 to get s2 for them to match
    else if (s2.size() == 0) return s1.size();
        // If the two strings have the same final character, we can somewhat ignore them and move on.
    else if (s1.back() == s2.back()) {
        return levSlow(s1.substr(0, s1.size() - 1),
                       s2.substr(0, s2.size() - 1));
    } else {
        return 1 + std::min(
                {
                        levSlow(s1.substr(0, s1.size() - 1), s2), // Removing a character
                        levSlow(s1, s2.substr(0, s2.size() - 1)), // Adding a character
                        levSlow(s1.substr(0, s1.size() - 1), s2.substr(0, s2.size() - 1)) // Replacing a character
                }
        );
    }
}

// Wrapper to avoid having to pass the length of the string
int lev(std::string s1, std::string s2){
    return lev_impl(s1, s1.size(), s2,s2.size());
}

int lev_impl(std::string s1, int n1, std::string s2, int n2) {
    // If s1 is empty, we have to add as many characters as there are in s2 to s1 for them to match
    if (n1 == 0) return n2;
        // If s2 is empty, we have to delete as many characters as there are in s1 to get s2 for them to match
    else if (n2 == 0) return n1;
        // If the two strings have the same final character, we can somewhat ignore them and move on.
    else if (s1[n1-1] == s2[n2 - 1]) {
        return lev_impl(s1, n1 - 1, s2, n2 - 1);
    } else {
        return 1 + std::min(
                {
                        lev_impl(s1, n1 - 1, s2, n2), // Removing a character
                        lev_impl(s1, n1, s2, n2 - 1), // Adding a character
                        lev_impl(s1, n1 -1, s2, n2 - 1) // Replacing a character
                }
        );
    }
}
