#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <iostream>
#include <vector>
#include <stack>
#include <set>

using namespace std;

/**
 * Find the longest repeating, non-overlapping substring
 */


/**
 * Length of longest substring where the characters in that substring appear an EVEN number of times
 * ex. 324425 --> 44 or 2442 because characters repeat twice = length of 4
 * ex. 233015150 --> 33 or or 1515 or 015150 because all charcters repeat twice = length of 6
 */

/**
 * Helper Method for Length of longest substring
 * Note: Use sets over hashmap when you just want to submit the value not a key-value pair
 */
bool is_unique(string str, int left, int right) {
    set<char> char_table;                   // keeps track of all chars we've used in this string
    for(int i = left; i < right; i++) {
        // if nothing in set, add this char
        if(char_table.empty()) {
            char_table.insert(str[i]);
        // otherwise check if we already have this char, if so then it's repeating so return false
        } else if(char_table.find(str[i]) != char_table.end()) {
            return false;
        } else {
            char_table.insert(str[i]);
        }
    }
    return true;
}
/**
 * BRUTE FORCE: Length of longest substring without repeating characters
 * Time complexity: O(n^3)
 */
int length_LongestSubstring(string str) {
    int length = 0;                         // length of longest substring
    for(int i = 0; i < str.length(); i++) {
        // look at substrings from position i to current pos of j (possible substrings from i)
        for(int j = i + 1; j <= str.length(); j++) {
            if(is_unique(str, i, j)) {
                cout << "unique: " << str.substr(i,j) << endl;
                if( (str.substr(i,j)).length() > length ) {
                    length = (str.substr(i,j)).length();
                    cout << "new length " << length << endl;
                }
            } else {
                cout << "not unique: " << str.substr(i,j) << endl;
            }
        }
    }
        
    return length;
}

/**
 * OPTIMIZED: Length of longest substring without repeating characters
 * Time complexity: O(n)
 */


int main() {
    length_LongestSubstring("catca");
    return EXIT_SUCCESS;
}