#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>

int lev(std::string, std::string);

int lev_impl(std::string, int, std::string, int, std::vector<std::vector<int> > &);

int levSlow(std::string, std::string);

void trace_cache(const std::vector<std::vector<int> > &);

int main() {
    // Initialize a vector to hold all test cases
    std::vector<std::pair<std::string, std::string>> testCases;

    // Add some test cases
    //testCases.emplace_back("cats", "dogs");
//    testCases.emplace_back("apple", "dapple");
    testCases.emplace_back("foo", "bar");
//    testCases.emplace_back("nirvana", "nirvana");
//    testCases.emplace_back("", "hello");
//    testCases.emplace_back("dogsarecoolyestheyare", "dogsarelityestheyare");
//    testCases.emplace_back("goodbye", "hello");
//    testCases.emplace_back("fjdkafjdafjdkajfdkafjkl", "fdafdjalfjdsalfjdsfjslfdsafdsafdas");


    for (auto test: testCases) {
        //std::cout << levSlow(test.first, test.second) << " ";
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
int lev(std::string s1, std::string s2) {
    int n1 = s1.size();
    int n2 = s2.size();
    std::vector<std::vector<int> > cache(n1 + 1, std::vector<int>(n2 + 1, -1));
    return lev_impl(s1, n1, s2, n2, cache);
}

int lev_impl(std::string s1, int n1, std::string s2, int n2, std::vector<std::vector<int> > &cache) {
    // If there's something in the cache, return that
    if (cache[n1][n2] != -1) return cache[n1][n2];

    // If s1 is empty, we have to add as many characters as there are in s2 to s1 for them to match
    if (n1 == 0) {
        cache[n1][n2] = n2;
        trace_cache(cache);
        return cache[n1][n2];
    }
        // If s2 is empty, we have to delete as many characters as there are in s1 to get s2 for them to match
    else if (n2 == 0) {
        cache[n1][n2] = n1;
        trace_cache(cache);
        return cache[n1][n2];
    }
        // If the two strings have the same final character, we can somewhat ignore them and move on.
    else if (s1[n1 - 1] == s2[n2 - 1]) {
        cache[n1][n2] = lev_impl(s1, n1 - 1, s2, n2 - 1, cache);
        trace_cache(cache);
        return cache[n1][n2];
    } else {
        cache[n1][n2] = 1 + std::min(
                {
                        lev_impl(s1, n1 - 1, s2, n2, cache), // Removing a character
                        lev_impl(s1, n1, s2, n2 - 1, cache), // Adding a character
                        lev_impl(s1, n1 - 1, s2, n2 - 1, cache) // Replacing a character
                }
        );
        trace_cache(cache);
        return cache[n1][n2];
    }
}

void trace_cache(const std::vector<std::vector<int> > &cache){
    int n1 = cache.size();
    int n2 = cache[0].size();
    for (int i = 0; i < n1; i++){
        for (int j = 0; j < n2; j++){
            if (cache[i][j] == -1){
                std::cout << "- ";
            }
            else{
                std::cout << cache[i][j] << " ";
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}
